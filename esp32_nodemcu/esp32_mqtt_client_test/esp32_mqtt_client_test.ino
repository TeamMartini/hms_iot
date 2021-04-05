#include <WiFi.h>
#include <PubSubClient.h>
#include <sstream>

const char *ssid = "iptime";
const char *password = "89652097";
const char *mqtt_server = "192.168.0.26";
const int mqttPort = 1883;
const char *mqtt_user = "martini";
const char *mqtt_password = "martini";

const char *topic_pub = "/mac_address";

byte mac[6];

#define UPDATE_INTERVAL 50000L

WiFiClient espClient;

PubSubClient mqttClient(espClient);

void setup() {
  // put your setup code here, to run once:
  WiFi.macAddress(mac);
  Serial.begin(115200);
  WiFi.begin(ssid, password);

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

  mqttClient.publish(topic_pub, mac, 6);
}

void loop() {
  // put your main code here, to run repeatedly:
  mqttClient.loop();

  mqttClient.publish(topic_pub, mac, 6);
  

}
