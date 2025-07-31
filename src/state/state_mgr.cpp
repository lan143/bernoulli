#include "state_mgr.h"

State StateMgr::buildState()
{
    return State(
        _isBackHomeLightEnabled,
        _isRainActive,
        _temperature,
        _humidity
    );
}

void StateMgr::publishState()
{
    State state = buildState();
    _producer->publish(&state);
}

void StateMgr::loop()
{
    if ((_lastUpdateStateTime + 20000) < millis()) {
        publishState();
        _lastUpdateStateTime = millis();
    }
}