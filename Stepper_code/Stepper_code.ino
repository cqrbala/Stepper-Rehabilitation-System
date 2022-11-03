#define trigger_pin 2
#define echo_pin 4
#define led_pin 10
#define sound_speed 343

// inital positon of the step which we will use as a point of reference
double origin;

// Used to set the origin at the genesis of the program
int origin_flag = 0;

// Step counter
int num_steps = 0; 

// Keeps track of which side of the origin the step is present (Prevents a single step being counted more than once)
int sign_origin;

// Sets the sign_flag on the first step, this allows the flexibility to account for the patient starting with either foot
int sign_flag = 0;

// Min displacement required to complete a step
double step_threshold = 1.1;

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

  if (origin_flag == 0) {

    // origin point is being set

    origin = pulseIn(echo_pin, 1);
    origin = (origin / 2000000)*sound_speed;
    origin_flag = 1;

  }
  else {

    
    // Processing of the ultrasonic sensor's input
    double duration, distance,step_displacement;
    duration = pulseIn(echo_pin, 1);
    duration = duration / 2000000; // now duration is in seconds
    distance = duration*sound_speed;

    // Reading EMG sensor input (gets the voltage in milliVolts)
    float sensorValue = analogRead(A10);
    float millivolt = (sensorValue/1023)*5;

    step_displacement = distance - origin;
    if(sign_flag == 0) {
      if(step_displacement < 0) {
        sign_origin = -1;
        sign_flag = 1;

      }
      else if (step_displacement > 0) {
        sign_origin = 1;
        sign_flag = 1;
      }
    }
    if(sign_flag) {
      if(abs(step_displacement) >= step_threshold && step_displacement * sign_origin > 0) {
        sign_origin *= -1;
        num_steps += 1
      } 
    }

  }
   
  delay(500);
}
