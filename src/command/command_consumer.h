#pragma once

#include <Arduino.h>
#include <consumer.h>

#include "relay/relay.h"

class CommandConsumer : public EDMQTT::Consumer
{
public:
    CommandConsumer(Relay* backHomeLightRelay, Relay* atticLightRelay) : _backHomeLightRelay(backHomeLightRelay), _atticLightRelay(atticLightRelay) {}
    void consume(std::string payload);

private:
    Relay* _backHomeLightRelay = NULL;
    Relay* _atticLightRelay = NULL;
};
