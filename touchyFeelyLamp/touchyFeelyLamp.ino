#include <CapacitiveSensor.h>


int threshold = 1000;
const int ledPin = 3;
const int capSend = 7;
const int capSense = 8;

// starts sensor with sending on capSend and recieving on capSense
CapacitiveSensor capSensor = CapacitiveSensor(capSend, capSense);

void setup(){
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop(){
  long sensorValue = capSensor.capacitiveSensor(30); // 30 samples
  Serial.println(sensorValue);
  
  if(sensorValue > threshold){
    digitalWrite(ledPin, HIGH);
  } else{
    digitalWrite(ledPin, LOW);
  }
  
  delay(10);
}
