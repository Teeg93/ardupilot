#include <AP_Foo/Foo.h>
#include <ctime>

extern const AP_HAL::HAL &hal;

Foo::Foo()
{
	_loc.lat = -34.8108693*1.0e7;
	_loc.lng = 138.6383568*1.0e7;
	_loc.alt = 50;
	srand(time(NULL));
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
	int _sign = rand()%2;
	if(_sign == 0)
	{
		_sign = -1;
	}
	l1 = rand()%3000;
	l2 = rand()%3000;

	l1 = -34.8037053+_sign*(l1*1e-7);
	l2 = 138.6306810+_sign*(l2*1e-7);
	_loc.lat = l1*1.0e7;
	_loc.lng = l2*1.0e7;
	loc.lat = _loc.lat;
	loc.lng = _loc.lng;
}

void Foo::update_loc_smooth(Location &loc)
{
	loc.lat = _loc.lat;
	loc.lng = _loc.lng;
}

void Foo::update_home(Location &loc)
{
	loc.lat = _loc.lat;
	loc.lng = _loc.lng;
}

void Foo::update_pos(Vector3f &pos)
{
	float _range = 1; // rand()%10001; //0 to 10000m range
	float _theta = rand()%360;  //0 to 359 degrees theta

	_theta = _theta * (3.14159265359/180.0); //convert to radians
	_posx = _range*cos(_theta);
	_posy = _range*sin(_theta);

	pos.x = _posx;
	pos.y = _posy;

}

void Foo::update_vel(Vector3f &vel)
{
	//Set a random speed in x direction, set y so that the total speed is 22m/s
	_vel.x = 11 - rand()%23; //Speed ranges from -11m/s to + 11m/s

	//Randomly make y +ve or -ve
	if(rand()%10 > 4)
	{
		_ysign = 1.0;
	}
	else
	{
		_ysign = -1.0;
	}

	_vel.y = _ysign * sqrtf(11.0*11.0 - _vel.x*_vel.x);
	_vel.z = 0.0;
	_heading = degrees(atan2(_vel.y, _vel.x));
	//gcs().send_text(MAV_SEVERITY_INFO, "HEADING %.2f", _heading);


	vel.x = _vel.x;
	vel.y = _vel.y;
	vel.z = _vel.z;

}

void Foo::update_vel_smooth(Vector3f &vel)
{
	vel.x = _vel.x;
	vel.y = _vel.y;
	vel.z = _vel.z;
}

void Foo::update_gyro(Vector3f &gyro)
{
	gyro.x = 0.0;
	gyro.y = 0.0;
	gyro.z = 0.0;
}

void Foo::update_accel(Vector3f &accel)
{
	_accel.x = 0;
	_accel.y = 0;
	_accel.z = 9.8;

	accel.x = _accel.x;
	accel.y = _accel.y;
	accel.z = _accel.z;
}

void Foo::update_accel_smooth(Vector3f &accel)
{
	accel.x = _accel.x;
	accel.y = _accel.y;
	accel.z = _accel.z;

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