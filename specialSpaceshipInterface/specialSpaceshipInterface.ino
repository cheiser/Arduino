
int switchstate = 0, delayIndex = 0, delayState = 10;

void setup(){
  // declare the LED pins as outputs 
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);

  // declare the switch pin as an input   
  pinMode(2,INPUT);
}

void loop(){

  // read the value of the switch
  // digitalRead() checks to see if there is voltage on the pin or not  
  switchstate = digitalRead(2);

  if (switchstate == LOW && delayState == 10) { // the button is not pressed
    digitalWrite(3, HIGH); // turn the green LED on pin 3 on
    digitalWrite(4, LOW);  // turn the red LED on pin 4 off
    digitalWrite(5, LOW);  // turn the red LED on pin 5 off
  } else if(switchstate == HIGH && delayState == 10){
    // change delay state here
    delayState = 9;
    digitalWrite(3, LOW); // turn of the green LED on pin 3
  }else if(delayState <= 0){
    // flash the red leds here
    delay(100);
    digitalWrite(4, HIGH);
    delay(100);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
    delay(100);
    digitalWrite(5, LOW);
    delayIndex++;
    if(delayIndex == 25){
      delayIndex = 0;
      delayState = 10;
    }
  } else { // the button is pressed or has been
    delay(1000);
    delayState--; // waits 1 second and then decreases delayState with one which will cause an delay for 10 seconds before the led changes
  }
}

