# Intro

This is a simple mqtt Example App I created for experimenting with mqtt on ESP32 and Android [play.google.com](https://play.google.com/store/apps/details?id=net.routix.mqttdash)

This Project is meant to be build with [PlatformIO](https://platformio.org/install/ide?install=atom)!

## Preview

[![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/FOfncYHcuVw/0.jpg)](https://www.youtube.com/watch?v=FOfncYHcuVw)


## Clone Repo
```bash
git clone https://github.com/werty1st/esp32-simple-mqtt.git
```

## Setup Project
```bash
 cp src/dist-mySecrets.h src/mySecrets.h
 ```

## Prepate mqtt Service

If you don't want to host your own mqtt server, you can use a free service at: [customer.cloudmqtt.com](https://customer.cloudmqtt.com)


## Add Credentials

* modify src/mySecrets.h

```cpp
#define SSID "WIFI-Name"
#define PSK "wifipassword"
#define MQTTSERVER "m2x.cloudmqtt.com"
#define MQTTPORT 12345
#define MQTTUSER "aaaaaa"
#define MQTTPASSWORD "bbbbbb"
```

## Compile and Run
:)
