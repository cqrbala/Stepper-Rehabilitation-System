int sensoroutput = A3; // the analog pin connected to the sensor
int ledoutput = 0; // pin connected to LED
int THRESHOLD = 100;
void setup()
{
  pinMode(sensoroutput, INPUT);
}
void loop()
{
int value = analogRead(sensoroutput);  // function to read analog voltage from sensor
Serial.print("sensor value is: ");
Serial.println(value);
delay(100); // to make the LED visible
}
