//#include <stdio.h>
#include "carmate.h"

int main(int argc, char* argv[]) {
	pthread_create(&syncer_thread, NULL, loop_syncer, NULL);
	pthread_create(&clock_thread, NULL, loop_clock, NULL);
	pthread_create(&tracker_thread, NULL, loop_tracker, NULL);
	pthread_create(&gps_reader_thread, NULL, loop_gps_reader, NULL);
	pthread_join(syncer_thread, NULL);
	pthread_join(clock_thread, NULL);
	pthread_join(tracker_thread, NULL);
	pthread_join(gps_reader_thread, NULL);
	return 0;
}
