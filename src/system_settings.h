#ifndef __SYSTEM_SETTINGS__
#define __SYSTEM_SETTINGS__

//general
#define EEPROM_SIZE 64
#define SERIAL_SPEED 115200
#define EEPROM_CONFIG_LEN_MAX 2000

// Client
#define CLIENT_NAME_LEN_MAX 30

// gadget-Command-Mapping
#define MAPPING_MAX_COMMANDS 15
#define MAPPING_MAX_CODES 10
#define MAPPING_MAX_COMMAND_NAME_LEN 25
#define MAIN_MAX_GADGETS 20
#define GADGET_NAME_LEN_MAX 25

//WIFI
#define WIFI_SSID_LEN_MAX 50
#define WIFI_PASSWORD_LEN_MAX 100

// MQTT
#define MQTT_USERNAME_MAX_LEN 40
#define MQTT_PW_MAX_LEN 40

// Reguests
#define REQUEST_PATH_LEN_MAX 40
#define REQUEST_BODY_LEN_MAX 2000
#define REQUEST_TYPE_LEN_MAX 20
#define REQUEST_QUEUE_LEN 5

// CodeCommands
#define CODE_BUFFER_SIZE 15
#define CODE_TIME_GAP 150
#define CODE_TYPE_NAME_LEN 30
#define CODE_STR_LEN_MAX 300

// Homebridge
#define HOMEBRIDGE_REGISTER_STR_MAX_LEN 240
#define HOMEBRIDGE_UNREGISTER_STR_MAX_LEN 50
#define HOMEBRIDGE_UPDATE_STR_LEN_MAX 240
#define HOMEBRIDGE_SERVICE_TYPE_LEN_MAX 25

// Logger
#define LOGGER_MAX_BUFFER_LEN 4000
#define LOGGER_T_BUFFER_LEN 30
#define LOGGER_MAX_NAME 50

const char json_str[] = R"(
{
  "id" : "TestClientESP32",
  "gadgets": [
    {
      "type": "sh_lamp_neopixel_basic",
      "name": "Testlampe NP",
      "lamp_type": 0,
      "pin": 33,
      "length": "24",
      "mapping": {
        "toggleStatus": [1, 16],
        "turnOn": [2, 17],
        "turnOff": [3, 18]
      }
    }
  ],
  "network": {
    "type": "mqtt",
    "config": {
      "wifi_ssid": "testwlan",
      "wifi_password": "testpw",
      "ip": "192.168.178.111",
      "port": "1883",
      "mqtt_username": null,
      "mqtt_password": null
    }
  },
  "connectors": {
  },
  "connector-mapping": {
  },
  "gadget-remote": {
    "type": "smarthome",
    "gadgets": [
      "Testlampe NP"
    ]
  },
  "code-remote": {
    "type": "smarthome",
    "gadgets": [
      "Testlampe NP"
    ]
  },
  "event-remote": {
    "type": "smarthome",
    "gadgets": [
      "TestFan",
      "Testlampe 2"
    ]
  }
}
)";

const char default_config[] = R"(
{"gadgets": [],"network": {},"connectors": {},"connector-mapping": {},"remote-mapping": {}}
)";

#endif //__SYSTEM_SETTINGS__
