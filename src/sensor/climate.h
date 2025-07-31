#pragma once

#include <DHT.h>
#include <discovery.h>

#include "state/state_mgr.h"

class StreetClimateSensor
{
public:
    StreetClimateSensor(EDHA::DiscoveryMgr* discoveryMgr, StateMgr* stateMgr) : _discoveryMgr(discoveryMgr), _stateMgr(stateMgr) {}
    void init(EDHA::Device* device, std::string stateTopic, int dht22Pin);
    void loop();

private:
    EDHA::DiscoveryMgr* _discoveryMgr = NULL;
    StateMgr* _stateMgr = NULL;

    DHT* _dht22 = NULL;

    uint64_t _lastUpdateTime = 0;
};
