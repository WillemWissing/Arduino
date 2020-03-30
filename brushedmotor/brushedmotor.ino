/*
Adafruit Arduino - Lesson 13. DC Motor
*/
 
 
int motorPin1 = 9;
int motorPin2 = 10;
int motorPin3 = 11;
int motorPin4 = 6;
 
void setup() 
{ 
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  Serial.begin(115200);
  while (! Serial);
  Serial.println("Speed 0 to 255");
} 
 
 
void loop() 
{ 
  if (Serial.available())
  {
    int speed = Serial.parseInt();
    if (speed >= 0 && speed <= 255)
    {
      analogWrite(motorPin1, speed);
      analogWrite(motorPin2, speed);
      analogWrite(motorPin3, speed); 
      analogWrite(motorPin4, speed); 
      Serial.println(speed);
    }
  }
} 
