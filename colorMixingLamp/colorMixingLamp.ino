const int greenLEDPin = 9; // the pin that will control the green part of the multi color LED
const int blueLEDPin = 10; // the pin that will control the blue part of the multi color LED
const int redLEDPin = 11; // the pin that will control the red part of the multi color LED

const int greenSensorPin = A1; // the pin that will read the value for the photoresistor for the green LED
const int redSensorPin = A0;
const int blueSensorPin = A2;

int redValue = 0; // the value that will be used to display the red color in the multi color LED
int greenValue = 0; // the value that will be used to display the green color in the multi color LED
int blueValue = 0; // the value that will be used to display the blue color in the multi color LED

int redSensorValue = 0; // the value being read from the sensor corrensponding to the red value
int greenSensorValue = 0; // the value being read from the sensor corrensponding to the green value
int blueSensorValue = 0; // the value being read from the sensor corrensponding to the blue value


void setup(){
  Serial.begin(9600);
  
  pinMode(greenLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);
}

void loop(){
  greenSensorValue = analogRead(greenSensorPin); // analogRead takes the argument for which pin it should listen for the input on
  delay(5); // used to make sure the ADC(analog to digital converter) is done
  redSensorValue = analogRead(redSensorPin);
  delay(5);
  blueSensorValue = analogRead(blueSensorPin);
  delay(5);
  
  Serial.print("RAW sensor value, red:");
  Serial.print(redSensorValue);
  Serial.print("\t green:");
  Serial.print(greenSensorValue);
  Serial.print("\t blue: ");
  Serial.println(blueSensorValue);
  
  redValue = redSensorValue/4;
  greenValue = greenSensorValue/4;
  blueValue = blueSensorValue/4;
  
  Serial.print("MAPPED sensor value, red:");
  Serial.print(redValue);
  Serial.print("\t green:");
  Serial.print(greenValue);
  Serial.print("\t blue: ");
  Serial.println(blueValue);
  
  analogWrite(greenLEDPin, greenValue);
  analogWrite(blueLEDPin, blueValue);
  analogWrite(redLEDPin, redValue);
  
}
