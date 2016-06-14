const int tempSensorPin = A0; // a constant holding the name of the sensor pin that will be used
const float baseLineTemperature = 23.29; // this is the temperature in celcius, that will be used to indicate when an led should be lit
int currentPin2 = LOW;


void setup(){
  Serial.begin(9600);
  
  for(int i = 0; i < 3; i++){
    int pinNumber = i+2;
    pinMode(pinNumber, OUTPUT);
    digitalWrite(pinNumber, LOW);
    
  }
}

void loop(){
  int sensorValue = analogRead(tempSensorPin);
  Serial.print("Sensor value: ");
  Serial.println(sensorValue);
  
  // convert the ADC reading to voltage
  float voltage = (sensorValue/1024.0) * 5.0;
  
  Serial.print("\n Volts: ");
  Serial.println(voltage);
  
  float temperature = (voltage - 0.5) * 100;
  Serial.print("degrees C: ");
  Serial.println(temperature);
  
  if(temperature < baseLineTemperature){
    Serial.println("inside first if");
    currentPin2 = (currentPin2 == HIGH)? LOW : HIGH;
    digitalWrite(2, currentPin2);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
  } else if(temperature > baseLineTemperature && temperature < baseLineTemperature+2){
    Serial.println("inside first else if");
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
  }else if(temperature > baseLineTemperature+2 && temperature < baseLineTemperature+4){
    Serial.println("inside second else if");
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
  } else{
    Serial.println("inside last else");
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
  }
  
  delay(1000);
}
