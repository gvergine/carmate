#pragma once
#include <stdbool.h>
#include <stdint.h>

struct time {
	uint8_t seconds;
	uint8_t minutes;
	uint8_t hours;
	uint8_t day;
	uint8_t month;
	uint16_t year;
};

struct gps_fix {
	float latitude;
	float longitude;
	float speed;
	struct time time;
};
struct gps_info {
	bool device_available;
	bool fix_available;
	struct gps_fix fix;
};
