#include <Arduino.h>
#include <ArduinoOTA.h>
#include <SPIFFS.h>
#include <ConfigMgr.h>
#include <esp_log.h>
#include <discovery.h>
#include <healthcheck.h>
#include <mqtt.h>

#include "defines.h"
#include "config.h"
#include "command/command_consumer.h"
#include "network/network.h"
#include "sensor/climate.h"
#include "sensor/rain.h"
#include "state/producer.h"
#include "state/state_mgr.h"
#include "relay/relay.h"
#include "web/handler.h"

EDConfig::ConfigMgr<Config> configMgr(EEPROM_SIZE);
NetworkMgr networkMgr(configMgr.getConfig(), true);
EDHealthCheck::HealthCheck healthCheck;
EDMQTT::MQTT mqtt(configMgr.getConfig().mqtt);
EDHA::DiscoveryMgr discoveryMgr;
Relay backHomeLightRelay(&discoveryMgr);
StateProducer stateProducer(&mqtt);
StateMgr stateMgr(&stateProducer);
StreetClimateSensor streetClimateSensor(&discoveryMgr, &stateMgr);
RainSensor rainSensor(&discoveryMgr, &stateMgr);
CommandConsumer commandConsumer(&backHomeLightRelay);
Handler handler(&configMgr, &networkMgr, &healthCheck);

void setup()
{
    randomSeed(micros());

    Serial.begin(SERIAL_SPEED);

    ESP_LOGI("setup", "Bernoulli");
    ESP_LOGI("setup", "start");

    SPIFFS.begin(true);

    configMgr.setDefault([](Config& config) {
        snprintf(config.wifiAPSSID, WIFI_SSID_LEN, "Bernoulli_%s", EDUtils::getMacAddress().c_str());
        snprintf(config.mqttStateTopic, MQTT_TOPIC_LEN, "bernoulli/%s/state", EDUtils::getChipID());
        snprintf(config.mqttCommandTopic, MQTT_TOPIC_LEN, "bernoulli/%s/set", EDUtils::getChipID());
        snprintf(config.mqttHADiscoveryPrefix, MQTT_TOPIC_LEN, "homeassistant");
    });
    configMgr.load();

    networkMgr.init();

    ArduinoOTA.setPassword("somestrongpassword");
    ArduinoOTA.begin();

    commandConsumer.init(configMgr.getConfig().mqttCommandTopic);
    stateProducer.init(configMgr.getConfig().mqttStateTopic);

    mqtt.init();
    networkMgr.OnConnect([&](bool isConnected) {
        if (isConnected) {
            mqtt.connect();
        }
    });
    mqtt.subscribe(&commandConsumer);
    healthCheck.registerService(&mqtt);

    handler.init();

    discoveryMgr.init(
        configMgr.getConfig().mqttHADiscoveryPrefix,
        configMgr.getConfig().mqttIsHADiscovery,
        [](std::string topicName, std::string payload) {
            return mqtt.publish(topicName.c_str(), payload.c_str(), true);
        }
    );

    EDHA::Device* device = discoveryMgr.addDevice();
    device->setHWVersion(deviceHWVersion)
        ->setSWVersion(deviceFWVersion)
        ->setModel(deviceModel)
        ->setName(deviceName)
        ->setManufacturer(deviceManufacturer);

    backHomeLightRelay.init(device, "Back home light", "backHomeLight", RELAY_BACK_HOME_LIGHT, false, configMgr.getConfig().mqttStateTopic, configMgr.getConfig().mqttCommandTopic);
    backHomeLightRelay.onActivate([](bool isOn) {
        stateMgr.setIsBackHomeLightEnabled(isOn);
    });

    rainSensor.init(device, configMgr.getConfig().mqttStateTopic, RAIN_SENSOR_PIN, true);
    streetClimateSensor.init(device, configMgr.getConfig().mqttStateTopic, DHT22_PIN);

    ESP_LOGI("setup", "complete");
}

void loop()
{
    networkMgr.loop();
    discoveryMgr.loop();
    ArduinoOTA.handle();
    stateMgr.loop();
    healthCheck.loop();
    rainSensor.loop();
    streetClimateSensor.loop();
}
