#pragma once

#include <AP_Common/AP_Common.h>
#include <AP_HAL/AP_HAL.h>
#include <GCS_MAVLink/GCS.h>
#include <AP_GPS/AP_GPS.h>
#include <AP_Baro/AP_Baro.h>
#include <SITL/SITL.h>

class Foo
{
public:
	Foo();
	void init();
	void loop();
	void print_gps();
	void update_loc(Location &loc);
	void update_loc_smooth(Location &loc);
	void update_home(Location &loc);
	void update_pos(Vector3f &pos);
	void update_vel(Vector3f &vel);
	void update_vel_smooth(Vector3f &vel);
	void update_gyro(Vector3f &gyro);
	void update_accel(Vector3f &accel);
	void update_accel_smooth(Vector3f &accel);

	Vector3f _accel;
	Location _loc;
	Vector3f _vel;
	float _posx;
	float _posy;
	float _heading;

private:

	uint32_t _loop_timer;

	SITL::SITL *sitl = AP::sitl();
	SITL::sitl_fdm rnd_state;

	float l1;
	float l2;
	float _ysign;
	/*
	const AP_GPS &gps = AP::gps();
	const AP_Baro &baro = AP::baro();
	const Location *loc;
	*/

};



