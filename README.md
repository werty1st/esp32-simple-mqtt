# Clone Repo
```bash
git clone https://github.com/werty1st/esp32-simple-mqtt.git
```

# Setup Project
```bash
 cp src/dist-mySecrets.h src/mySecrets.h
 ```

# Add Credentials

* modify src/mySecrets.h

```cpp
#define SSID "WIFI-Name"
#define PSK "wifipassword"
#define MQTTSERVER "m2x.cloudmqtt.com"
#define MQTTPORT 12345
#define MQTTUSER "aaaaaa"
#define MQTTPASSWORD "bbbbbb"
```

# Compile and Run
