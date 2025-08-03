#include <Utils.h>
#include "climate.h"

void StreetClimateSensor::init(EDHA::Device* device, std::string stateTopic, int dht22Pin)
{
    const char* chipID = EDUtils::getChipID();
    _dht22 = new DHT(dht22Pin, DHT22);
    _dht22->begin();

    _discoveryMgr->addSensor(
        device,
        "Street temperature",
        "temperature",
        EDUtils::formatString("street_temperature_bernoulli_%s", chipID)
    )
        ->setStateTopic(stateTopic)
        ->setValueTemplate("{{ value_json.temperature }}")
        ->setUnitOfMeasurement("°C")
        ->setDeviceClass(EDHA::deviceClassSensorTemperature);

    _discoveryMgr->addSensor(
        device,
        "Street humidity",
        "humidity",
        EDUtils::formatString("street_humidity_bernoulli_%s", chipID)
    )
        ->setStateTopic(stateTopic)
        ->setValueTemplate("{{ value_json.humidity }}")
        ->setUnitOfMeasurement("%")
        ->setDeviceClass(EDHA::deviceClassSensorHumidity);   
}

void StreetClimateSensor::loop()
{
    if ((_lastUpdateTime + 60000) < millis()) {
        _stateMgr->getState().setTemperature(_dht22->readTemperature());
        _stateMgr->getState().setHumidity(_dht22->readHumidity());

        _lastUpdateTime = millis();
    }
}
