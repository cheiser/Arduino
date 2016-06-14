const int switchPin = 8;

unsigned long previousTime = 0;

int switchState = 0;
int prevSwitchState = 0;

int led = 2;

long interval = 1000; // 600000


void setup(){
  for(int i = 2; i < 8; i++){
    pinMode(i, OUTPUT);
  }
  
  pinMode(switchPin, INPUT);  
}

void loop(){
  unsigned long currentTime = millis();
  
  if(currentTime - previousTime > interval){
    previousTime = currentTime;
    
    if(led <= 7){
      digitalWrite(led, HIGH);
    }
    led++;
    
    if(led > 8){ // the end of the leds
      for(int i = 2; i < 8; i++){
        digitalWrite(i, LOW);
      }
      delay(100);
      for(int i = 2; i < 8; i++){
        digitalWrite(i, HIGH);
      }
      delay(100);
      for(int i = 2; i < 8; i++){
        digitalWrite(i, LOW);
      }
    }
  }
  
  switchState = digitalRead(switchPin);
  
  if(switchState != prevSwitchState){ // if the sensor has been tilted
   for(int i = 2; i < 8; i++){
     digitalWrite(i, LOW);
   }
   
   led = 2;
   previousTime = currentTime;
  }
  
  prevSwitchState = switchState;
}
