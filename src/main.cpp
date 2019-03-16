#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

#include <./mySecrets.h>

#define DEBUG false

const char* ssid = SSID;
const char* psk =  PSK;
const char* mqttServer = MQTTSERVER;
const int mqttPort = MQTTPORT;
const char* mqttUser = MQTTUSER;
const char* mqttPassword = MQTTPASSWORD;

#define MAGNET 4
#define PUSH_BUTTON 15

bool first_run = true;
bool magnet_state = false;
unsigned long last_update;


WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length) {

  String topicX = String(topic);
  String payloadX = "";

  for (int i = 0; i < length; i++) {
    payloadX += (char)payload[i];
  }

  if(DEBUG){
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);
    Serial.print("Message:");
    Serial.print(payloadX);
    Serial.println();
    Serial.println("-----------------------");
  }

  if (topicX == "push_button"){
    //mqtt app trigger
    //empty message would be possible but is not userfriendly in mqtt UI ()
    if(payloadX == "0"){
      digitalWrite(PUSH_BUTTON, LOW);
      sleep(1);
      digitalWrite(PUSH_BUTTON, HIGH);
      client.publish("push_button", "1"); //set switch UI back to previous state
    }
  } //elseif()...


}

void setup() {

  if(DEBUG){
    Serial.begin(115200);
    sleep(3);
    Serial.println("Booting ...");
  }

  //define PSK as empty string for public/open wifi
  if (String(psk) == ""){
      WiFi.begin(ssid);
  }else {
      WiFi.begin(ssid, psk);
  }

  //loop until wifi connected
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    if (DEBUG) Serial.println("Connecting to WiFi..");
  }
  if (DEBUG) Serial.println("Connected to the WiFi network");

  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  //loop until mqtt connected
  while (!client.connected()) {
    if (DEBUG) Serial.println("Connecting to MQTT...");
    if (client.connect("ESP32Client", mqttUser, mqttPassword )) {
      if (DEBUG) Serial.println("connected");
    } else {
      if (DEBUG) Serial.print("failed with state ");
      if (DEBUG) Serial.print(client.state());
      delay(2000);
    }
  }

  client.subscribe("push_button");

  //set watch for pin
  pinMode(MAGNET, INPUT_PULLUP);
  pinMode(PUSH_BUTTON, OUTPUT);
  digitalWrite(PUSH_BUTTON, HIGH);

}

//https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/

void loop() {

  client.loop(); //process mqtt

  //read Magnet Switch
  // false => closed; switch connects input to ground
  // true => open; pullup raises input to high
  bool magnet = digitalRead(MAGNET);

  //store last state to
  if (first_run){
    first_run = false;
    magnet_state = magnet;
    last_update = millis();
    client.publish("magnet", !magnet ? "closed" : "open");

    if (DEBUG){
      Serial.print("Magnet:");
      Serial.println(!magnet ? "closed" : "open");
    }
  } else {
    //broadcast if last update is older than 5 sec. or state has changed
    if ( magnet != magnet_state || last_update + 5000  < millis()) {
      client.publish("magnet", !magnet ? "closed" : "open");
      last_update = millis();
      magnet_state = magnet;

      if (DEBUG){
        Serial.print("Magnet:");
        Serial.println(!magnet ? "closed" : "open");
      }
    }
  }


  //sleep(1);

  //reconnect after wifi/mqtt has been connected
  if(WiFi.status() != WL_CONNECTED || !client.connected()){
    //reboot?
    ESP.restart();
  }

}
