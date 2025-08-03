#include <Json.h>
#include <ExtStrings.h>
#include "defines.h"
#include "state.h"

std::string State::marshalJSON()
{
    std::string payload = EDUtils::buildJson([this](JsonObject entity) {
        if (_isBackHomeLightEnabled) {
            entity[F("backHomeLightRelay")] = "true";
        } else {
            entity[F("backHomeLightRelay")] = "false";
        }

        if (_isRainActive) {
            entity[F("isRainActive")] = "true";
        } else {
            entity[F("isRainActive")] = "false";
        }

        entity[F("temperature")] = _temperature;
        entity[F("humidity")] = _humidity;
    });

    return payload;
}

bool State::operator==(State& other)
{
    return (*this)._isBackHomeLightEnabled == other._isBackHomeLightEnabled
        && (*this)._isRainActive == other._isRainActive
        && (*this)._temperature == other._temperature
        && (*this)._humidity == other._humidity;
}
