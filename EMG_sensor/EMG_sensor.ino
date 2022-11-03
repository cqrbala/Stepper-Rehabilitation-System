int Sensor_pin = A3; // the analog pin connected to the sensor
void setup()
{
  Serial.begin(9600);
}
void loop()
{
int value = analogRead(Sensor_pin);  // function to read analog voltage from sensor
Serial.print("sensor value is: ");
Serial.println(value);
delay(1000); // to make the LED visible
}
