const int irSensorPin = A0;

int sensorValue = 0;

void setup(){
  Serial.begin(9600);
}

void loop(){
  sensorValue = analogRead(irSensorPin);
  
  delay(50);
  
  Serial.print("Recieved data: ");
  Serial.println(sensorValue);
}
