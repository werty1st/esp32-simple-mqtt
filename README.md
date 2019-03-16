# Intro

This Project is meant to be build with https://platformio.org/install/ide?install=atom

If your on MacOS/Windows your may need to install EPS32 drivers.
https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers


## Preview

[![Video Preview](https://img.youtube.com/vi/FOfncYHcuVw/0.jpg)](https://www.youtube.com/watch?v=FOfncYHcuVw)


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

After having PlatformIO install the Firmware on the ESP32 you are ready to setup the Android App.

* Install Android App https://play.google.com/store/apps/details?id=net.routix.mqttdash

* Open MQTTDash and add your server

* Screenshots

home view:

<img src="./screens/Screenshot_20190316-032649_MQTT Dash.jpg" width="256">

adding server:

<img src="./screens/Screenshot_20190316-032847_MQTT Dash.jpg" width="256">

setup push button widget:

<img src="./screens/Screenshot_20190316-032927_MQTT Dash.jpg" width="256">

setup push button widget:

<img src="./screens/Screenshot_20190316-033000_MQTT Dash.jpg" width="256">

setup magnet switch state widget:

<img src="./screens/Screenshot_20190316-033015_MQTT Dash.jpg" width="256">
