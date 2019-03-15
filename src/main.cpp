#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

#include <./mySecrets.h>

const char* ssid = SSID;
const char* psk =  PSK;
const char* mqttServer = MQTTSERVER;
const int mqttPort = MQTTPORT;
const char* mqttUser = MQTTUSER;
const char* mqttPassword = MQTTPASSWORD;

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length) {

  Serial.print("Message arrived in topic: ");
  Serial.println(topic);

  String topicX = String(topic);
  String payloadX = "";

  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    payloadX += (char)payload[i];
  }

  Serial.println();
  Serial.println("-----------------------");

  if (topicX == "schalter" && payloadX == "0"){
    Serial.println("schalter wurde gedrückt");
    digitalWrite(15, HIGH);
    sleep(1);
    digitalWrite(15, LOW);
    client.publish("schalter", "1");
  }

}

void setup() {

  Serial.begin(115200);
  sleep(5);
  Serial.println("Booting ...");

  if (psk == ""){
      WiFi.begin(ssid);
  }else {
    WiFi.begin(ssid, psk);
  }


  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");

  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");

    if (client.connect("ESP32Client", mqttUser, mqttPassword )) {

      Serial.println("connected");

    } else {

      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);

    }

  }

  client.subscribe("esp/test");
  client.subscribe("schalter");

  //set watch for pin
  pinMode(4, INPUT_PULLUP);
  pinMode(15, OUTPUT);

}

//https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/

void loop() {
  client.loop();
  //read pin4
  bool tor = digitalRead(4);
  client.publish("tor", !tor ? "zu" : "offen");
  Serial.print("TOR:");
  Serial.println(!tor ? "zu" : "offen");
  sleep(5);
}
