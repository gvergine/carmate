#include "gps_reader.h"
//#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "minmea.h"

void process_nmea_string(char* buf) {


	static struct gps_info info;
	info.device_available = true;

	switch (minmea_sentence_id(buf, false)) {
	case MINMEA_SENTENCE_RMC: {
		struct minmea_sentence_rmc frame;
		if (minmea_parse_rmc(&frame, buf)) {
			info.fix.latitude = minmea_tocoord(&frame.latitude);
			info.fix.longitude = minmea_tocoord(&frame.longitude);
			info.fix.speed = minmea_tofloat(&frame.speed) * 1.852;
			info.fix.time.seconds = frame.time.seconds;
			info.fix.time.minutes = frame.time.minutes;
			info.fix.time.hours = frame.time.hours;
			info.fix.time.day = frame.date.day;
			info.fix.time.month = frame.date.month;
			info.fix.time.year = frame.date.year;
			info.fix_available = frame.valid;
		} else {
			info.fix_available = false;
		}
		queue_push(queue_gps_reader_gps_update,0,&info);

	} break;


	}


}

void loop_gps_reader()
{

	struct gps_info info;
	info.device_available = false;

	while(true) {

		int fd = open("/dev/ttyACM0",O_RDONLY);

		if (fd == -1) {
			queue_push(queue_gps_reader_gps_update, 0, &info);
			usleep(1000000); continue;
		}

		uint8_t buf[128] = {0};
		int ret = read(fd, buf, 128);

		while (ret > 0) {

			char* pch = NULL;
			pch = strtok(buf, "\r\n");
			while (pch != NULL)
			{
				process_nmea_string(pch);
				//printf("%s\n",pch);
				pch = strtok(NULL, "\r\n");
			}

			bzero(buf,128);
			ret = read(fd, buf, 128);


		}

		queue_push(queue_gps_reader_gps_update, 0, &info);

	}
}
