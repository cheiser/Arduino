int sensorValue; // the value being read from the sensor
int sensorLow = 1023; // sets this to this high value to make sure that the read sensorValue is smaller and gets a new reading during the calibration of the first 5 seconds after the start
int sensorHigh = 0; // sets this low to make sure that the sensorValue is bigger during calibration, after calibration sensorHigh >= sensorLow, this is to make sure that we will be able to
// sense when we cover the photosensor and when we don't

const int ledPin = 13;
const int calibrationTime = 5000; // the time that we have to calibrate, expressed in milliseconds
const int tonePin = 8;
const int toneDuration = 20;

void setup(){
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH); // turns on the LED to show that it is time to calibrate
  
  while(millis() < calibrationTime){// millis() reports how long the arduino has been running since it was last turned on/reset 
    sensorValue = analogRead(A0);
    if(sensorValue > sensorHigh){
      sensorHigh = sensorValue;
    }
    if(sensorValue < sensorLow){
      sensorLow = sensorValue;
    }
  }
  digitalWrite(ledPin, LOW); // turns of the LED to indicate that the calibration time is over
}

void loop(){
  sensorValue = analogRead(A0); // reads the value from the pin A0
  
  int pitch = map(sensorValue, sensorLow, sensorHigh, 5000, 25000); // maps the value sensorValue which should be between sensorLow and sensorHigh to a value between 50 and 4000
  
  tone(tonePin, pitch, toneDuration); // arg1: the pin to use the tone on, arg2: the frequency to send the electric signals at, arg3: for how long to keep sending the pulses
  
  delay(10); // waits 10 milliseconds
}
