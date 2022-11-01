#define trigger_pin 2
#define echo_pin 4
#define led_pin 10
#define sound_speed 343
double threshold;
int num_steps = 0, flag = 0, threshold_flag = 0;

void setup() {
  pinMode(trigger_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  pinMode(led_pin, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  digitalWrite(trigger_pin, 1);
  delayMicroseconds(10);
  digitalWrite(trigger_pin, 0);

  if (threshold_flag == 0) {
    threshold = pulseIn(echo_pin, 1);
    threshold = (threshold / 2000000)*sound_speed;
    Serial.print("threshold set as: ");
    Serial.print(threshold);
    Serial.println(" m");
    threshold_flag = 1;
  }
  else {

    float sensorValue = analogRead(A10);
    float millivolt = (sensorValue/1023)*5;
    
    Serial.print("Sensor Value: ");
    Serial.println(sensorValue);
    
    Serial.print("Voltage: ");
    Serial.print(millivolt*1000);
    Serial.println(" mV");
    Serial.println("");
    
    double duration, distance;
    duration = pulseIn(echo_pin, 1);
    duration = duration / 2000000; // now duration is in seconds
    distance = duration*sound_speed;
    Serial.print(distance);
    Serial.println(" m");
    Serial.print("number of steps: ");
    Serial.println(num_steps);
  
    if (distance < threshold && flag == 0 && distance > 0 && distance < 4) {
      flag = 1;
      digitalWrite(led_pin, 1);
      num_steps += 2;
    }
    else if (distance > threshold && flag == 1 && distance > 0 && distance < 4) {
      flag = 0;
      digitalWrite(led_pin, 0);
    }
  }
   
  delay(500);
}
