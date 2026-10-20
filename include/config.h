#pragma once

#include <Arduino.h>
#include <cstdint>
#include "sensor.h"
void print_F(SensorReading);


namespace Config {
    constexpr unsigned long kSerialBeginBaud = 115200;

    constexpr u_int8_t kLdrGpio = 4;
    constexpr u_int8_t kLedGpio = 7;

    constexpr uint32_t kSamplePeriodMs = 100;
    constexpr size_t kAverageWindow = 10;

    constexpr uint16_t kLedOnBelow = 1600;
    constexpr uint16_t kLedOffAbove = 2200;

    static_assert(kLedOnBelow < kLedOffAbove, "Invalid hysteresis thresholds");
    static_assert(kAverageWindow > 0, "Window cannot be empty");

    constexpr float kVref = 3.3f;
    constexpr uint8_t kAnalogResolutionBits = 12; 
    constexpr uint16_t kAnalogResolutionMaxValue = (1 << kAnalogResolutionBits) - 1;
}

