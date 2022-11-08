int Sensor_pin = 0; // the analog pin connected to the sensor
void setup()
{
  Serial.begin(115200);
}
void loop()
{

int value = analogRead(Sensor_pin);// function to read analog voltage from sensor
//value = analogRead(Sensor_pin);
Serial.print("sensor value is: ");
Serial.println(value);
delay(100); // to make the LED visible
}
