
#pragma once

#include <AP_HAL/AP_HAL.h>
#if CONFIG_HAL_BOARD == HAL_BOARD_SITL
#define SITL_RC_INPUT_CHANNELS 16
#include "AP_HAL_SITL.h"
#include <SITL/SITL.h>

class HALSITL::RCInput : public AP_HAL::RCInput {
public:
    explicit RCInput(SITL_State *sitlState): _sitlState(sitlState) {}
    void init() override;
    bool new_input() override;
    uint8_t num_channels() override;
    uint16_t read(uint8_t ch) override;
    uint8_t read(uint16_t* periods, uint8_t len) override;
    int16_t get_rssi(void) override;
    const char *protocol() const override { return "SITL"; }

private:
    SITL_State *_sitlState;

    float _Gamma = 0.9;
    float _s1;
    float _s2;
    float _Pt = 0.1;
    float _Pr;
    float _Gt = 1.41;
    float _Gr = 1.41;
    float _c = 3.0e8;
    float _f = 433000000;
    float _lambda = _c/_f;
    float _ht;
    float _hr = 20;
    float _d;
    float _delta_alpha;
    float _delta_phi;
    float _deltax, _deltay;
    float PI = 3.141596;
    float _PdB;

    int16_t _buff;
    int16_t _RSSI;
};

#endif

