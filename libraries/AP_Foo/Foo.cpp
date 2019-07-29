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
void Foo::update_loc(Location &loc)
{
	loc.lat = -34.8108693*1.0e7;
	loc.lng = 138.6383568*1.0e7;
}

void Foo::update_home(Location &loc)
{
	loc.lat = -34.8108693*1.0e7;
	loc.lng = 138.6383568*1.0e7;
}
void Foo::update_pos(Vector3f &pos)
{
	pos.x = 0;
	pos.y = 0;
}
void Foo::print_gps()
{
	//_gps.update();
	//loc = &_gps.location();
	/*
	AP_GPS::GPS_Status _status = gps.status();
	float alt = baro.get_altitude();
	gcs().send_text(MAV_SEVERITY_INFO, "GPS_STATUS: %d", _status);
	gcs().send_text(MAV_SEVERITY_INFO, "ALTITUDE: %2.3f", alt);
	*/


	gcs().send_text(MAV_SEVERITY_INFO, "RESETTING SITL POSITION");


	//sitl->state.altitude = sitl->state.altitude;
	/*
	rnd_state.home		   	= sitl->state.home;
	rnd_state.latitude 		= -34.8108693;
	rnd_state.longitude 	= 138.6383568;
	rnd_state.altitude   	= 50;
	rnd_state.heading    	= 0;
	rnd_state.speedN     	= 10;
	rnd_state.speedE     	= 0;
	rnd_state.speedD     	= 20;
	rnd_state.xAccel     	= 0;
	rnd_state.yAccel     	= 0;
	rnd_state.zAccel     	= 0;
	rnd_state.rollRate   	= 0;
	rnd_state.pitchRate   	= 0;
	rnd_state.yawRate     	= 0;
	rnd_state.rollDeg     	= 0;
	rnd_state.pitchDeg    	= 5;
	rnd_state.yawDeg      	= 0;
	rnd_state.quaternion  	= sitl->state.quaternion;
	rnd_state.airspeed    	= 10;
	rnd_state.battery_voltage = 12;
	rnd_state.battery_current = 20;
	rnd_state.rpm1         	= 1200;
	rnd_state.rpm2        	= 0;
	rnd_state.rcin_chan_count = sitl->state.rcin_chan_count;
	for(int i=0; i<8; i++){
		rnd_state.rcin[i] = sitl->state.rcin[i];
	}

	rnd_state.range        	= 50;
	rnd_state.bodyMagField 	= sitl->state.bodyMagField;
	rnd_state.angAccel    	= sitl->state.angAccel;
	rnd_state.timestamp_us 	= sitl->state.timestamp_us;
	//sitl->state = rnd_state;
	*/
}