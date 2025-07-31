#include "rain.h"

void RainSensor::init(EDHA::Device* device, std::string stateTopic, int pin, bool nc)
{
    const char* chipID = EDUtils::getChipID();
    pinMode(pin, INPUT);
    _pin = pin;
    _nc = nc;

    _discoveryMgr->addBinarySensor(
        device,
        "Is rain active",
        "rain_active",
        EDUtils::formatString("rain_active_bernoulli_%s", chipID)
    )
        ->setStateTopic(stateTopic)
        ->setValueTemplate("{{ value_json.isRainActive }}")
        ->setPayloadOn("true")
        ->setPayloadOff("false")
        ->setDeviceClass("moisture");
}

void RainSensor::loop()
{
    if ((_lastUpdateTime + 60000) < millis()) {
        int pinValue = readPinValue();
        if (_nc) {
            _stateMgr->setIsRainActive(pinValue == 1);
        } else {
            _stateMgr->setIsRainActive(pinValue == 0);
        }

        _lastUpdateTime = millis();
    }
}

int RainSensor::readPinValue()
{
    int pinValues = 0;

    for (int i = 0; i < 10; i++) {
        pinValues += digitalRead(_pin);
        delayMicroseconds(20);
    }

    return pinValues > 5 ? 1 : 0;
}
