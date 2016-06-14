#include <Servo.h>
Servo myServo;

const int piezo = A0;
const int switchPin = 2;
const int yellowLed = 4;
const int greenLed = 3;
const int redLed = 5;

int knockVal; // will hold the value of the knock on the piezo
int switchVal; // will hold the value of wheather or not the switch is pressed

const int quietKnock = 10; // lower limit for the knock
const int loudKnock = 100; // upper limit for the allowed knock volume

boolean locked = false;
int numberOfKnocks = 0;

void setup(){
  myServo.attach(10); // says we will be using pin 9 to control the servo
  pinMode(yellowLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(switchPin, INPUT);
  
  Serial.begin(9600);
  
  digitalWrite(greenLed, HIGH);
  myServo.write(0);
  delay(100);
  myServo.write(45);
  delay(100);
  Serial.println("The box is unlocked");
}

void loop(){
  if(locked == false){
    switchVal = digitalRead(switchPin);
    
    if(switchVal == HIGH){
      locked = true;
      digitalWrite(greenLed, LOW);
      digitalWrite(redLed, HIGH);
      myServo.write(90);
      Serial.println("The box is locked");
      delay(1000);
    }
  } else if(locked == true){
    knockVal = analogRead(piezo);
    
    if(numberOfKnocks < 3 && knockVal > 0){
      if(checkForKnock(knockVal) == true){
        numberOfKnocks++;
      }
      
      Serial.print(3-numberOfKnocks);
      Serial.println(" more knocks to go");
    }
    
    if(numberOfKnocks >= 3){
      locked = false;
      myServo.write(0);
      delay(20);
      digitalWrite(greenLed, HIGH);
      digitalWrite(redLed, LOW);
      Serial.println("The box is unlocked");
      numberOfKnocks = 0;
    }
  }
}

boolean checkForKnock(int knockValue){
  if(knockValue > quietKnock && knockValue < loudKnock){
    digitalWrite(yellowLed, HIGH);
    delay(50);
    digitalWrite(yellowLed, LOW);
    Serial.print("Valid knock of value: ");
    Serial.println(knockValue);
    
    return true;
  } else{
    Serial.print("Bad knock value: ");
    Serial.println(knockValue);
    
    return false;
  }
}
