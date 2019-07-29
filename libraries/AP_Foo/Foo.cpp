#include <AP_Foo/Foo.h>

extern const AP_HAL::HAL &hal;

Foo::Foo()
{
}

void Foo::init()
{
	_loop_timer=AP_HAL::millis();
	gcs().send_text(MAV_SEVERITY_INFO, "G'DAY MATE");
	hal.scheduler->register_timer_process(FUNCTOR_BIND(this, &Foo::loop, void));
}

void Foo::loop()
{
	if(AP_HAL::millis() - _loop_timer >= 1000)
	{
		gcs().send_text(MAV_SEVERITY_INFO, "Loop Time: %d",AP_HAL::millis()-_loop_timer);
		print_gps();
		//gcs().send_text(MAV_SEVERITY_INFO, "It fit many loop brother");
		_loop_timer = AP_HAL::millis();
	}
}

void Foo::print_gps()
{
	//_gps.update();
	//loc = &_gps.location();
	AP_GPS::GPS_Status _status = gps.status();
	float alt = baro.get_altitude();
	gcs().send_text(MAV_SEVERITY_INFO, "GPS_STATUS: %d", _status);
	gcs().send_text(MAV_SEVERITY_INFO, "ALTITUDE: %2.3f", alt);
}