#include <AP_Foo/foo.h>

const AP_HAL::HAL& hal = AP_HAL::get_HAL();

void loop(){
	hal.console->printf("foo");
}

void init(){
	hal.console->printf("Initializing Foo");
}

