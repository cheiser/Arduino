#include <CapacitiveSensor.h>


int threshold = 1000;
const int capSend = 7;
const int capSense = 8;

// starts sensor with sending on capSend and recieving on capSense
CapacitiveSensor capSensor = CapacitiveSensor(capSend, capSense);

void setup(){
  Serial.begin(9600);
}

void loop(){
  long sensorValue = capSensor.capacitiveSensor(30); // 30 samples
  if(sensorValue/4 < 255){
    Serial.write(sensorValue/4);
  } else{
    Serial.write(0);
  }
  
  
  delay(1);
}
