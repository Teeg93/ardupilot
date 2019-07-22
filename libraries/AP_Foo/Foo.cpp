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
	if(AP_HAL::millis() - _loop_timer > 1000)
	{
		print_gps();
		gcs().send_text(MAV_SEVERITY_INFO, "It fit many loop brother");
		_loop_timer = AP_HAL::millis();
	}
}

void Foo::print_gps()
{
	gcs().send_text(MAV_SEVERITY_INFO, "PRINTING GPS");
}