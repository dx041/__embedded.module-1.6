#include "config.h"
#include "smart_light.h"

namespace {
    bool ledState = false;
}

namespace SmartLight {
    void begin() {
        pinMode(Config::kLedGpio, OUTPUT);
        digitalWrite(Config::kLedGpio, LOW);
    }

    void updateLedState(uint16_t avgADC) {
        if (!ledState && avgADC < Config::kLedOnBelow) {
            ledState = true;
            digitalWrite(Config::kLedGpio, ledState);
        } else if (ledState && avgADC > Config::kLedOffAbove) {
            ledState = false;
            digitalWrite(Config::kLedGpio, ledState);
        }
    }

    bool isLedOn() { return ledState; }
}
