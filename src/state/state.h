#pragma once

#include <Arduino.h>

class State
{
public:
    State(
        bool isBackHomeLightEnabled,
        bool isRainActive,
        float_t temperature,
        float_t humidity
    ) : _isBackHomeLightEnabled(isBackHomeLightEnabled),
        _isRainActive(isRainActive),
        _temperature(temperature),
        _humidity(humidity) {}

    std::string marshalJSON();

private:
    bool _isBackHomeLightEnabled = false;
    bool _isRainActive = false;
    float_t _temperature = 0.0f;
    float_t _humidity = 0.0f;
};
