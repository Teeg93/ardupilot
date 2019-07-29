#pragma once

#include <AP_Common/AP_Common.h>
#include <AP_HAL/AP_HAL.h>
#include <GCS_MAVLink/GCS.h>
#include <AP_GPS/AP_GPS.h>
#include <AP_Baro/AP_Baro.h>


class Foo
{
public:
	Foo();
	void init();
	void loop();
	void print_gps();

private:

	uint32_t _loop_timer;
	const AP_GPS &gps = AP::gps();
	const AP_Baro &baro = AP::baro();
	const Location *loc;
};



