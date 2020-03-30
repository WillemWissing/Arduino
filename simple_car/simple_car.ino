// ---------------------------------------------------------------------------
// combination of newping and pid control
// ---------------------------------------------------------------------------

double  Input_L, Input_R, Output_L, Output_R;
#define PIN_OUTPUT_L 9
#define PIN_OUTPUT_R 10



#include <NewPing.h>

#define TRIGGER_PIN_LEFT  A0  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN_LEFT     A1  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define TRIGGER_PIN_RIGHT  A2  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN_RIGHT     A3  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar_L(TRIGGER_PIN_LEFT, ECHO_PIN_LEFT, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar_R(TRIGGER_PIN_RIGHT, ECHO_PIN_RIGHT, MAX_DISTANCE);

void setup() {
    //initialize the variables we're linked to
    Input_L = sonar_L.ping_cm();
    Input_R = sonar_R.ping_cm();
    

  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.  
}

void loop() {
  delay(50);
  Input_L = sonar_L.convert_cm(sonar_L.ping_median(3));
  if (Input_L == 0){
    Input_L = 200;
  }

  Output_L = calc_output(Input_L, Input_R);
  
  analogWrite(PIN_OUTPUT_L, Output_L);
  Serial.print(Input_L);
  Serial.print(" L  ");
  Serial.println(Output_L);

  delay(50);
  Input_R = sonar_R.convert_cm(sonar_R.ping_median(3));
  if (Input_R == 0){
    Input_R = 200;
  }
  
  Output_R = calc_output(Input_R, Input_L);
   
  analogWrite(PIN_OUTPUT_R, Output_R);
  Serial.print(Input_R);
  Serial.print(" R  ");
  Serial.println(Output_R);  

 
}

double calc_output(double Input, double Offside) {
  double Output;
  if ( Input >= Offside) {
    Output = 255;
  }
  else Output = 255*(Input/200);
  return Output;
  }

void turnLeft()
{
  while (Input_L <= 80){
  analogWrite(PIN_OUTPUT_L, 200);
  Serial.println(Input_L);
  Input_L = sonar_L.convert_cm(sonar_L.ping_median(3));
  if (Input_L == 0){
    Input_L = 200;
    }
  }
}

void turnRight()
{
  while (Input_R <= 80){
  analogWrite(PIN_OUTPUT_R, 200);
  Serial.println(Input_R);
  Input_R = sonar_R.convert_cm(sonar_R.ping_median(3));
  if (Input_R == 0){
    Input_R = 200;
    }
  }
}
