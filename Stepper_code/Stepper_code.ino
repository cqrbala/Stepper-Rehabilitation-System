#define trigger_pin 2
#define echo_pin 4
#define sound_speed 343

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

void setup() {
  pinMode(trigger_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  Serial.begin(115200);
}

void loop() {

  digitalWrite(trigger_pin, 1);
  delayMicroseconds(10);
  digitalWrite(trigger_pin, 0);

  if (origin_flag == 0) {

    // origin point is being set
    origin = pulseIn(echo_pin, 1);
    origin = (origin / 2000000)*sound_speed;
    origin_flag = 1;
//    Serial.print("Origin set as: ");
//    Serial.println(origin);
  }
  else {

    // Processing of the ultrasonic sensor's input
    double duration, distance,step_displacement;
    duration = pulseIn(echo_pin, 1);
    duration = duration / 2000000; // now duration is in seconds
    distance = duration*sound_speed;

//    Serial.print("Ultrasonic sensor data is: ");
//    Serial.println(distance);
//    Serial.print("sign flag is: ");
//    Serial.println(sign_origin);

//    Reading EMG sensor input (gets the voltage in milliVolts)
    float sensorValue = analogRead(0);
    sensorValue = analogRead(0);
    float millivolt = (sensorValue/1023)*5;

    Serial.print("Muscle sensor value: ");
    Serial.println(sensorValue);
    Serial.print("millivolts: ");
    Serial.println(millivolt);
 
    step_displacement = distance - origin;
//    Serial.print("Distance is: ");
//    Serial.println(step_displacement);
    
    
    if(abs(step_displacement) >= step_threshold) {
      if(sign_flag ==0) {
        sign_flag = 1;
        if(step_displacement < 0) sign_origin = 1;
        else sign_origin = -1;
        num_steps += 1;
//        Serial.print("One small step for Man, one large leap for mankind: ");
//        Serial.println(num_steps);
      }
      else if (step_displacement * sign_origin > 0) {
        sign_origin *= -1;
        num_steps += 1;
//        Serial.print("Number of steps: ");
//        Serial.println(num_steps);
//        Serial.print("Distance is: ");
//        Serial.println(step_displacement);
      }  
    } 
  }
  delay(50);
}
