#pragma once
#include <Arduino.h>

namespace SmartLight {
    void begin();
    void updateLedState(uint16_t averagedAdc);
    bool isLedOn();
}