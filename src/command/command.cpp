#include <ArduinoJson.h>
#include <Json.h>
#include <ExtStrings.h>
#include "defines.h"
#include "command.h"

bool Command::unmarshalJSON(const char* data)
{
    return EDUtils::parseJson(data, [this](JsonObject root) {
        if (root.containsKey(F("backHomeLightRelay"))) {
            _hasEnableBackHomeLight = true;
            _enableBackHomeLight = root[F("backHomeLightRelay")].as<std::string>() == "true";
        }

        return true;
    });
}
