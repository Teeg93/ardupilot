#pragma once

#include <AP_Common/AP_Common.h>
#include <AP_HAL/AP_HAL.h>
#include <GCS_MAVLink/GCS.h>
#include <AP_GPS/AP_GPS.h>


class Foo
{
public:
	Foo();
	void init();
	void loop();
	void print_gps();

private:

	uint32_t _loop_timer;
	AP_GPS *_gps;
};



