#include <Servo.h>

Servo myServo;

int const potPin = A0;
int potValue;
int angle;

void setup(){
  myServo.attach(3);
  Serial.begin(9600);
  
}

void loop(){
  potValue = analogRead(potPin);
  Serial.print("potValue: ");
  Serial.print(potValue);
  
  angle = map(potValue, 0, 1023, 0, 179);
  Serial.print(", angle: ");
  Serial.print(angle);
  
  myServo.write(angle);
  delay(15);
  
  
}
