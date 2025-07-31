#pragma once

#include "state.h"
#include "producer.h"

class StateMgr
{
public:
    StateMgr(StateProducer* producer) : _producer(producer) {}

    void setIsBackHomeLightEnabled(bool isBackHomeLightEnabled)
    {
        _isBackHomeLightEnabled = isBackHomeLightEnabled;
        publishState();
    }

    void setIsRainActive(bool isRainActive)
    {
        _isRainActive = isRainActive;
        publishState();
    }

    void setTemperature(float_t temperature)
    {
        _temperature = temperature;
        publishState();
    }

    void setHumidity(float_t humidity)
    {
        _humidity = humidity;
        publishState();
    }

    void loop();

private:
    bool _isBackHomeLightEnabled = false;
    bool _isRainActive = false;
    float_t _temperature = 0.0f;
    float_t _humidity = 0.0f;

    uint64_t _lastUpdateStateTime = 0;

private:
    State buildState();
    void publishState();

private:
    StateProducer* _producer;
};
