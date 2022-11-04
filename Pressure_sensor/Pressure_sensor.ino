int Sensor_pin = 0; // the analog pin connected to the sensor
int LED_pin = 10; // pin connected to LED
//int THRESHOLD = 100;
int value;
void setup()
{
  pinMode(LED_pin, OUTPUT);
  Serial.begin(9600);
}
void loop()
{
value = analogRead(Sensor_pin);  // function to read analog voltage from sensor
Serial.print("sensor value is: ");
Serial.println(value);
delay(500); // to make the LED visible
}
