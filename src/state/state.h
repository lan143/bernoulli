#pragma once

#include <Arduino.h>

class State
{
public:
    std::string marshalJSON();

    void setIsBackHomeLightEnabled(bool isBackHomeLightEnabled)
    {
        _isBackHomeLightEnabled = isBackHomeLightEnabled;
    }

    void setIsRainActive(bool isRainActive)
    {
        _isRainActive = isRainActive;
    }

    void setTemperature(float_t temperature)
    {
        _temperature = temperature;
    }

    void setHumidity(float_t humidity)
    {
        _humidity = humidity;
    }

    bool operator==(State& other);
    bool operator!=(State& other)
    {
        return !(*this == other);
    }

private:
    bool _isBackHomeLightEnabled = false;
    bool _isRainActive = false;
    float_t _temperature = 0.0f;
    float_t _humidity = 0.0f;
};
