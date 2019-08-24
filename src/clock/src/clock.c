#include "clock.h"
#include <unistd.h>

void loop_clock()
{
	uint8_t current_second = 0;
    while(true) {
    	uint8_t minute;
    	//uint8_t second;
    	current_second++;
    	if (current_second == 60) {
    		queue_push(queue_clock_minute_signal, 1, &minute);
    		current_second = 0;
    	}
		//queue_push(queue_clock_second_signal, 1, &second);
    	usleep(1000000);
    }
}
