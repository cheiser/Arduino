#include <CapacitiveSensor.h>
#include <LiquidCrystal.h>

// initiate LiquidCrystal object
LiquidCrystal lcd(12, 11, 5, 8, 3, 7);

int threshold = 1000;
const int capSend = 4;
const int capSense = 2;
const int tempSensorPin = A0;

// starts sensor with sending on capSend and recieving on capSense
CapacitiveSensor capSensor = CapacitiveSensor(capSend, capSense);

void setup(){
  Serial.begin(9600);
  // specify display size
  lcd.begin(16, 2);
}

void loop(){
  long sensorValue = capSensor.capacitiveSensor(30); // 30 samples
  Serial.print("cap sensorValue:");
  Serial.println(sensorValue);
  int temperatureVal = analogRead(tempSensorPin);
  Serial.print("temperatureVal: ");
  Serial.println(temperatureVal);

  lcd.clear(); // clear previous text on display
  lcd.setCursor(0, 0); // reset cursor
  if(sensorValue > threshold){
    lcd.print("Temperature:");
    lcd.setCursor(0, 1);
    lcd.print(sensorReadToCelsius(temperatureVal));
  } else{
    lcd.print("No touch");
    lcd.setCursor(0, 1);
    lcd.print(sensorValue);
  }
  
  delay(100);
}

int sensorReadToCelsius(int sensorVal){
  float voltage = (sensorVal/1024.0) * 5.0; // convert ADC reading to voltage
  float temperature = (voltage - 0.5) * 100;
  return temperature;
}

