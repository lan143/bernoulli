#pragma once

#include <Arduino.h>
#include <consumer.h>

#include "relay/relay.h"

class CommandConsumer : public EDMQTT::Consumer
{
public:
    CommandConsumer(Relay* backHomeLightRelay) : _backHomeLightRelay(backHomeLightRelay) {}
    void consume(std::string payload);

private:
    Relay* _backHomeLightRelay = NULL;
};
