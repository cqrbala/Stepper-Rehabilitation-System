#include <PubSubClient.h>
#include <WiFiClient.h>
#include <WiFi.h>
#include <ThingSpeak.h>
#include <ArduinoJson.h>
#include "HTTPClient.h"

#define trigger_pin 33
#define echo_pin 32
#define sound_speed 343
int Sensor_pin = 23;

char ssid[] = "Arnav";
char password[] = "pranjal13";

const char* server = "mqtt3.thingspeak.com";
char mqttUserName[] = "mwa0000026745613";
char mqttPass[] = "THZAMM30249U49OK"; //Change to your MQTT API key from Account > MyProfile on Thingspeak.
int writeChannelID = 1925729;
char writeAPIKey[] = "OLVQ0WA9GL4CLREE";
char readAPIKey[] = "M5SLOVSH2YRWMURX";

String cse_ip = "192.168.91.166"; // YOUR IP from ipconfig/ifconfig
String cse_port = "8080";
String server = "http://" + cse_ip + ":" + cse_port + "/~/in-cse/in-name/";
String ae1 = "Number-Of-Steps";
String cnt1 = "node1";
String ae2 = "EMG";
String cnt2 = "node1";

WiFiClient client; // Instantiating WiFiClient object
PubSubClient mqttClient(server, 1883, client); // Instantiating Publisher Sub-Client Object

// inital positon of the step which we will use as a point of reference
double origin;

// Used to set the origin at the genesis of the program
int origin_flag = 0;

// Step counter
int num_steps = 0; 

// Keeps track of which side of the origin the step is present (Prevents a single step being counted more than once)
int sign_origin = 0;

// Sets the sign_flag on the first step, this allows the flexibility to account for the patient starting with either foot
int sign_flag = 0;

// Min displacement required to complete a step
double step_threshold = 0.03;

double duration, distance, step_displacement, sensorValue, millivolt;

void setup() {
  pinMode(trigger_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  WiFi.begin(ssid, password);
  Serial.begin(115200);
  
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("Not connected to WiFi.");
  }
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Setting up MQTT Broker details
  mqttClient.setServer(server, 1883);
}

void loop()  {
  while(mqttClient.connected() == NULL)
  {
    Serial.println("MQTT not connected");
    Serial.println(mqttClient.connect("KSYxFSI0BicuKikKEyYaEjU","KSYxFSI0BicuKikKEyYaEjU","Na4N9kkuVLSjuO1xucSvUd60"));
  }
  Serial.println("MQTT connected");
  mqttClient.loop(); // maintain connection

  digitalWrite(trigger_pin, 1);
  delayMicroseconds(10);
  digitalWrite(trigger_pin, 0);

  if (origin_flag == 0) {

    // origin point is being set
    origin = pulseIn(echo_pin, 1);
    origin = (origin / 2000000)*sound_speed;
    origin_flag = 1;
    Serial.print("Origin set as: ");
    Serial.println(origin);
  }
  else {

    // Processing of the ultrasonic sensor's input
    
    duration = pulseIn(echo_pin, 1);
    duration = duration / 2000000; // now duration is in seconds
    distance = duration*sound_speed;

    Serial.print("Ultrasonic sensor data is: ");
    Serial.println(distance);
    // Serial.print("sign flag is: ");
    // Serial.println(sign_origin);

    // Reading EMG sensor input (gets the voltage in milliVolts)
    sensorValue = analogRead(Sensor_pin);
    sensorValue = analogRead(Sensor_pin);
    millivolt = (sensorValue/1023)*5;

    Serial.print("Muscle sensor value: ");
    Serial.println(sensorValue);
    // Serial.print("millivolts: ");
    // Serial.println(millivolt);
 
    step_displacement = distance - origin;
    Serial.print("Distance is: ");
    Serial.println(step_displacement);
    
    
    if(abs(step_displacement) >= step_threshold) {
      if(sign_flag ==0) {
        sign_flag = 1;
        if(step_displacement < 0) sign_origin = 1;
        else sign_origin = -1;
        num_steps += 1;
        Serial.print("One small step for Man, one large leap for mankind: ");
        Serial.println(num_steps);
      }
      else if (step_displacement * sign_origin > 0) {
        sign_origin *= -1;
        num_steps += 1;
        Serial.print("Number of steps: ");
        Serial.println(num_steps);
        Serial.print("Distance is: ");
        Serial.println(step_displacement);
      }  
    } 
  }
  mqttPublish(writeChannelID, sensorValue, num_steps);
  createCISteps(String(num_steps));
  createCIEMG(String(sensorValue));
  delay(500);
}

void mqttPublish(long pubChannelID, double EMG, int steps) {
  String topic1, topic2, data1, data2;
  topic1 = "channels/" + String(pubChannelID) + "/publish";
  data1 = "field1=" + String(EMG);
  topic2 = "channels/" + String(pubChannelID) + "/publish";
  data2 = "field2=" + String(steps);
  Serial.println(data1);
  Serial.println(data2);
  mqttClient.publish(topic1.c_str(), data1.c_str());
  mqttClient.publish(topic2.c_str(), data2.c_str());
}

void createCISteps(String &val)
{
  HTTPClient http;
  http.begin(server + ae1 + "/" + cnt1 + "/");

  http.addHeader("X-M2M-Origin", "admin:admin");
  http.addHeader("Content-Type", "application/json;ty=4");

  int code = http.POST("{\"m2m:cin\": {\"cnf\":\"application/json\",\"con\": " + String(val) + "}}");

  Serial.println(code);
  if (code == -1) {
    Serial.println("UNABLE TO CONNECT TO THE SERVER");
  }
  http.end();
}

void createCIEMG(String &val)
{
  HTTPClient http;
  http.begin(server + ae2 + "/" + cnt2 + "/");

  http.addHeader("X-M2M-Origin", "admin:admin");
  http.addHeader("Content-Type", "application/json;ty=4");

  int code = http.POST("{\"m2m:cin\": {\"cnf\":\"application/json\",\"con\": " + String(val) + "}}");

  Serial.println(code);
  if (code == -1) {
    Serial.println("UNABLE TO CONNECT TO THE SERVER");
  }
  http.end();
}