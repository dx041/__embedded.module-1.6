#include "esp32-hal.h"
#include <Arduino.h>
#include <cstdint>
#include <sys/types.h>

#include "config.h"
#include "sensor.h"
#include "smart_light.h"


void setup() {
    Serial.begin(Config::kSerialBeginBaud);
    Sensor::begin();
    SmartLight::begin();
}

void loop() {
    const uint32_t nowMs = millis();
    static uint32_t lastSampleMs = 0;

    if (nowMs - lastSampleMs < Config::kSamplePeriodMs) {
        return;
    }

    lastSampleMs = nowMs;

    const SensorReading reading = Sensor::sample();
    SmartLight::updateLedState(reading.average);

    print_F(reading);
}

void print_F(SensorReading reading) {
        Serial.printf("| \tRaw: %u\t | \tmV_byESP: %u\t | \tmV_byFormula: %u\t | \tΔ: %.1f mV\t | \terr: %.2f%%\t|\n",
            static_cast<uint32_t>(reading.raw),
            static_cast<uint16_t>(reading.millivoltsByESP),
            static_cast<uint16_t>(reading.millivoltsByFormula),
            static_cast<float>(reading.absoluteError),
            static_cast<float>(reading.relativeErrorPercent)
    );
}