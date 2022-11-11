#include <PubSubClient.h>
#include <WiFiClient.h>
#include <WiFi.h>
#include <ThingSpeak.h>

char ssid[] = "Arnav";
char password[] = "pranjal13";

const char* server = "mqtt3.thingspeak.com";
char mqttUserName[] = "mwa0000026745613";
char mqttPass[] = "THZAMM30249U49OK"; //Change to your MQTT API key from Account > MyProfile on Thingspeak.
int writeChannelID = 1925729;
char writeAPIKey[] = "OLVQ0WA9GL4CLREE";
char readAPIKey[] = "M5SLOVSH2YRWMURX";

WiFiClient client; // Instantiating WiFiClient object
PubSubClient mqttClient(server, 1883, client); // Instantiating Publisher Sub-Client Object

int Sensor_pin = 32; // the analog pin connected to the sensor
int value;

void setup()
{
  WiFi.begin(ssid, password);
  Serial.begin(9600);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("Not connected to WiFi.");
  }
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
void loop()
{
  while(mqttClient.connected() == NULL)
  {
    Serial.println("MQTT not connected");
    Serial.println(mqttClient.connect("KSYxFSI0BicuKikKEyYaEjU","KSYxFSI0BicuKikKEyYaEjU","Na4N9kkuVLSjuO1xucSvUd60"));
  }
  Serial.println("MQTT connected");
  mqttClient.loop(); // maintain connection

  value = analogRead(Sensor_pin);  // function to read analog voltage from sensor
  Serial.print("sensor value is: ");
  Serial.println(value);
  mqttPublish(writeChannelID, value);
  delay(500); 
}

void mqttPublish(long pubChannelID, int force) {
  String topic, dataString;
  topic = "channels/" + String(pubChannelID) + "/publish";
  dataString = "field3=" + String(force);
  Serial.println(data);
  mqttClient.publish(topic.c_str(), dataString.c_str());
}