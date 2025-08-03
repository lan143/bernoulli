#pragma once

#include <DHT.h>
#include <discovery.h>
#include <state/state_mgr.h>

#include "state/state.h"

class StreetClimateSensor
{
public:
    StreetClimateSensor(EDHA::DiscoveryMgr* discoveryMgr, EDUtils::StateMgr<State>* stateMgr) : _discoveryMgr(discoveryMgr), _stateMgr(stateMgr) {}
    void init(EDHA::Device* device, std::string stateTopic, int dht22Pin);
    void loop();

private:
    EDHA::DiscoveryMgr* _discoveryMgr = NULL;
    EDUtils::StateMgr<State>* _stateMgr = NULL;

    DHT* _dht22 = NULL;

    uint64_t _lastUpdateTime = 0;
};
