#pragma once

#include <Arduino.h>

class Command
{
public:
    bool unmarshalJSON(const char* data);

    bool hasEnableBackHomeLight() { return _hasEnableBackHomeLight; }
    bool getEnableBackHomeLight() { return _enableBackHomeLight;}

private:
    bool _hasEnableBackHomeLight = false;
    bool _enableBackHomeLight = false;
};
