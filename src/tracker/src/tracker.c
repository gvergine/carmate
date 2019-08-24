#include "tracker.h"
//#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void loop_tracker()
{
	uint32_t datatype;
	struct gps_info info;

	int fd = -1;
	int n_written_fixes = 0;

	while(true) {

		queue_pop(&queue_tracker, &datatype, &info);
		if(datatype == 0)
		{
			if (info.device_available)
			{
				if(info.fix_available)
				{
//					printf("%d/%d/%d %d:%d:%d (%f,%f) %f\n",
//							info.fix.time.day, info.fix.time.month, info.fix.time.year,
//							info.fix.time.hours, info.fix.time.minutes, info.fix.time.seconds,
//							info.fix.latitude, info.fix.longitude, info.fix.speed
//					);

					if (fd == -1)
					{
						char filename[64] = {0};
						sprintf(filename,"/opt/gps/tracking/%d%d%d%d%d%d.log",
								info.fix.time.year,info.fix.time.month,info.fix.time.day,
								info.fix.time.hours, info.fix.time.minutes, info.fix.time.seconds
								);
						fd = open(filename,O_CREAT | O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO);
						n_written_fixes = 0;

//						if (fd == -1) {
//							perror(filename);
//						}
					}


					if (fd > 0)
					{
						write(fd,&info,sizeof(info));
						n_written_fixes++;
						if (n_written_fixes == 40) {
							n_written_fixes = 0;
							uint8_t smallfd = (uint8_t)fd;
//							printf("send sync req %d\n",smallfd);
							queue_push(queue_tracker_sync_signal,3,&smallfd);
						}
					}

				}
//				else
//				{
//					printf("tracker: fix not available\n");
//				}

			}
//			else
//			{
//				printf("tracker: device not available\n");
//			}
		}

	}
}
