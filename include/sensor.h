#pragma once
#include <Arduino.h>

struct SensorReading {
    uint16_t raw = 0;
    uint16_t average = 0;
    uint16_t millivoltsByESP = 0;
    uint16_t millivoltsByFormula = 0;
    float absoluteError;
    float relativeErrorPercent;
};

namespace Sensor {
    void begin();
    SensorReading sample();
    void calculateDeviation(SensorReading&);
}
