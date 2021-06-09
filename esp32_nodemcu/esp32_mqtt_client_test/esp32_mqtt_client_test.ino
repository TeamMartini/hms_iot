#include <WiFi.h>
#include <PubSubClient.h>
#include <sstream>
#include <Wire.h>

#define sensorPin1 34
#define sensorPin2 22

//////////////////////////////////////
///////network and mqtt setup/////////
const char *ssid = "hms_iot";
const char *password = "89652097";
const char *mqtt_server = "nw.esllo.com";
const int mqttPort = 1883;
const char *mqtt_user = "martini";
const char *mqtt_password = "martini";

byte mac[7] = { '\0', };
#define UPDATE_INTERVAL 50000L
///////////////////////////////////////
//////////IR sensor setup//////////////
int count = 0;

boolean sensor1Triggered = false;
unsigned long sensor1Time;
byte currState1;
byte prevState1 = HIGH;

boolean sensor2Triggered = false;
unsigned long sensor2Time;
byte currState2;
byte prevState2 = HIGH;
byte message[10] = { '\0', };
//////////////////////////////////////
bool check;


WiFiClient espClient;
PubSubClient mqttClient(espClient);

void setup() {
  // put your setup code here, to run once:
  WiFi.macAddress(mac);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  pinMode(sensorPin1, INPUT);
  pinMode(sensorPin2, INPUT);

  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to the WiFi network");

  mqttClient.setServer(mqtt_server, mqttPort);

  while(!mqttClient.connected()) {
    Serial.println("connecting to MQTT ... ");

    if(mqttClient.connect("ESP32_01", mqtt_user, mqtt_password)) {
      Serial.println("connected");
    } else {
      Serial.print("failed with the state ");
      Serial.print(mqttClient.state());
      delay(1000);
    }
  }

  mqttClient.publish("/init", mac, 7);
  mqttClient.publish("/create_all", mac, 7);
}

void loop() {
  // put your main code here, to run repeatedly:
  currState1 = digitalRead(sensorPin1);
  if(currState1 != prevState1) {
    if(currState1 == LOW) {
      sensor1Triggered = true;
      sensor1Time = millis();
      Serial.println("sensor 1 triggered");
    }
  }

  currState2 = digitalRead(sensorPin2);
  if(currState2 != prevState2) {
    if(currState2 == LOW) {
      sensor2Triggered = true;
      sensor2Time = millis();
      Serial.println("sensor 2 triggered");
    }
  }

  if(sensor2Triggered && sensor1Triggered) {
    if(sensor1Time > sensor2Time) {
      count++;
      Serial.print("Count : ");
      Serial.println(count);
      memset(message, '\0', 10);
      memcpy(message, mac, 6);
      
      message[8] = (byte)count;
      check = mqttClient.publish("/room_all_add", message, 10);
      Serial.print("/room_all_add published: ");
      Serial.println(check);
      memset(message, '\0', 10);
      delay(200);
      sensor1Time = 0;
      sensor2Time = 0;
      currState1 = HIGH;
      currState2 = HIGH;
//      mqttClient.loop();
    }
    if(sensor2Time > sensor1Time) {
      count--;
      if(count <= 0) count = 0;
      Serial.print("Count : ");
      Serial.println(count);
      memset(message, '\0', 10);
      memcpy(message, mac, 6);
      
      message[8] = (byte)count;
      check = mqttClient.publish("/room_all_sub", message, 10);
      Serial.print("/room_all_sub published: ");
      Serial.println(check);
      memset(message, '\0', 10);
      delay(200);
      sensor1Time = 0;
      sensor2Time = 0;
      currState1 = HIGH;
      currState2 = HIGH;
//      mqttClient.loop();
    }
    sensor1Triggered = false;
    sensor2Triggered = false;
  }
  mqttClient.loop();
//
//  mqttClient.publish(topic_pub, mac, 6);
  

}
