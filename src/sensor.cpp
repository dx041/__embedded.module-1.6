#include "sensor.h"
#include "config.h"
#include "esp32-hal-adc.h"

#include <Arduino.h>
#include <cstdint>

namespace {
    uint16_t samples[Config::kAverageWindow] = {};
    uint32_t sum = 0;
    size_t writeToIndex  = 0;
    size_t count = 0;
}

namespace Sensor {
    void begin() {
        analogReadResolution(Config::kAnalogResolutionBits);
        analogSetPinAttenuation(Config::kLdrGpio, ADC_11db);
    }

    SensorReading sample() {
        SensorReading reading;
        
        reading.raw = static_cast<uint16_t>(analogRead(Config::kLdrGpio));
        reading.millivoltsByESP = analogReadMilliVolts(Config::kLdrGpio);
        calculateDeviation(reading);

        if (count == Config::kAverageWindow) {
            sum -= samples[writeToIndex];
        } else {
            ++count;
        }

        samples[writeToIndex] = reading.raw;
        sum += reading.raw;
        writeToIndex = (writeToIndex + 1) % Config::kAverageWindow;
        reading.average = static_cast<uint16_t>(sum / count);

        return reading;
    }

    void calculateDeviation(SensorReading& reading) {
        reading.millivoltsByFormula = static_cast<uint16_t>(
            round(((static_cast<float>(reading.raw) / Config::kAnalogResolutionMaxValue) * Config::kVref) * 1000)
        );
        reading.absoluteError = fabs(static_cast<float>(reading.millivoltsByESP) - reading.millivoltsByFormula);
        reading.relativeErrorPercent = (reading.absoluteError / static_cast<float>(reading.millivoltsByESP)) * 100.0f;
    }
}