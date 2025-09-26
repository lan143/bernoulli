#pragma once

#include <Arduino.h>

class Command
{
public:
    bool unmarshalJSON(const char* data);

    bool hasEnableBackHomeLight() { return _hasEnableBackHomeLight; }
    bool getEnableBackHomeLight() { return _enableBackHomeLight;}

    bool hasEnableAtticLight() { return _hasEnableAtticLight; }
    bool getEnableAtticLight() { return _enableAtticLight;}

private:
    bool _hasEnableBackHomeLight = false;
    bool _enableBackHomeLight = false;

    bool _hasEnableAtticLight = false;
    bool _enableAtticLight = false;
};
