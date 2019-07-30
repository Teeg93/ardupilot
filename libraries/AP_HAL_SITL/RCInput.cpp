#include <AP_HAL/AP_HAL.h>
#if CONFIG_HAL_BOARD == HAL_BOARD_SITL

#include "RCInput.h"
#include <SITL/SITL.h>

using namespace HALSITL;

extern const AP_HAL::HAL& hal;

void RCInput::init()
{
}

bool RCInput::new_input()
{
    if (_sitlState->new_rc_input) {
        _sitlState->new_rc_input = false;
        return true;
    }
    return false;
}

uint16_t RCInput::read(uint8_t ch)
{
    if (ch >= num_channels()) {
        return 0;
    }
    return _sitlState->pwm_input[ch];
}

uint8_t RCInput::read(uint16_t* periods, uint8_t len)
{
    if (len > num_channels()) {
        len = num_channels();
    }
    for (uint8_t i=0; i < len; i++) {
        periods[i] = read(i);
    }
    return len;
}

uint8_t RCInput::num_channels()
{
    SITL::SITL *_sitl = AP::sitl();
    if (_sitl) {
        return MIN(_sitl->rc_chancount.get(), SITL_RC_INPUT_CHANNELS);
    }
    return SITL_RC_INPUT_CHANNELS;
}

int16_t RCInput::get_rssi(void)
{
    SITL::SITL *_state = AP::sitl();

    _delta_alpha = (radians(_state->state.home.lat*1.0e-7- _state->state.latitude));
    _delta_phi   = (radians(_state->state.home.lng*1.0e-7- _state->state.longitude));
    _deltax      = 6.371e6 * _delta_phi;
    _deltay      = 6.371e6 * _delta_alpha;
    _d = sqrt(_deltay*_deltay + _deltax*_deltax) + 0.00001;
    _ht          = _state->height_agl;

    _Pr = 4*((_Pt*_Gt*_Gr*_lambda*_lambda)/((4*PI*_d)*(4*PI*_d)))*sin((2*PI*_ht*_hr)/(_d*_lambda))*sin((2*PI*_ht*_hr)/(_d*_lambda));
    _PdB = 10*log10(_Pr)+30;

    _buff = (100+_PdB)*2;
    if(_buff > 255)
    {
        _RSSI = 255;
    }
    if(_buff < 0)
    {
        _RSSI = 0;
    }
    else
    {
        _RSSI = _buff;
    }



    //gcs().send_text(MAV_SEVERITY_INFO, "ALT: %f",_ht);
    return _RSSI;
}

#endif
