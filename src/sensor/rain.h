#pragma once

#include <discovery.h>

#include "state/state_mgr.h"

class RainSensor
{
public:
    RainSensor(EDHA::DiscoveryMgr* discoveryMgr, StateMgr* stateMgr) : _discoveryMgr(discoveryMgr), _stateMgr(stateMgr) {}
    void init(EDHA::Device* device, std::string stateTopic, int pin, bool nc);
    void loop();

private:
    int readPinValue();

private:
    EDHA::DiscoveryMgr* _discoveryMgr = NULL;
    StateMgr* _stateMgr = NULL;

    int _pin = 0;
    int _nc = false;

    uint64_t _lastUpdateTime = 0;
};
