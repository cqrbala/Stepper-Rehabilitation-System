int Sensor_pin = 4; // the analog pin connected to the sensor
int LED_pin = 10; // pin connected to LED
//int THRESHOLD = 100;
int value;
void setup()
{
  Serial.begin(9600);
}
void loop()
{
value = analogRead(Sensor_pin);  // function to read analog voltage from sensor
Serial.print("sensor value is: ");
Serial.println(value);
delay(500); 
}
