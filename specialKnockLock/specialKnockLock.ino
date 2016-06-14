#include <Servo.h>
Servo myServo;

const int piezo = A0;
const int switchPin = 2;
const int yellowLed = 4;
const int greenLed = 3;
const int redLed = 5;

int knockVal; // will hold the value of the knock on the piezo
int switchVal; // will hold the value of wheather or not the switch is pressed

const int quietKnock = 5; // lower limit for the knock
const int loudKnock = 100; // upper limit for the allowed knock volume

boolean locked = false;
int numberOfKnocks = 0;


// POTENTIAL CHANGE: could also store the "relative" time the knock has occured at and simply signal the end of input with a negative value or something and then when checking the code simply
//   check if the knock occurs on the same time as the stored one within a specific interval(eg. if the time stamp is 00:12 you check if it is between 00:02 and 00:22)
int knockCode[] = {1, 2, 0, 0, 0, 0, 0, 0}; // the knock code to match the knocking against

#define knockCodeLength (sizeof(knockCode)/sizeof(int)) // calculates the knockCode length and stores it so we don't have to recalculate incase we need it again

int enteredKnockCode[knockCodeLength]; // this will hold the knocks entered by the user
long timeFirstKnock = 0; // this will hold the time the first knock was entered for this trial
long thisTime = 0; // will simply hold millis() for the current loop run so we don't recalculate it every time

const int knockInterval = 16000; // this will be the time in milliseconds that the knockCode above will be divided into intervals from, NOTE: can't be to big as it will "overflow" when added
const int knockExtraTime = 1000; // the extra time that will be added in the wait to make sure that all the knocks has been entered

#define intervalLengths (knockInterval / knockCodeLength)


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
  
  resetEnteredKnockCode();
}



/*
 * Skulle eventuellt kunna ha en boolean array av en viss längd och bestämma att den ska motsvara en viss tidslängd t.ex. 10 sekunder och så får varje "cell" i den motsvara en knackning
 * under motsvarande sekund och så kollar man bara efter första knackingen om den stämmer mot mönstret, får ju även ha ett visst intervall inom vilket knackningen behöver komma.
 *
 * Skulle kunna ha det som så att knackningarna "lagras", så om man t.ex. knackar 3 gånger på 1 sekund så delas detta upp och motsvarar de 3 första platserna i boolean arrayen, eller om man
 * bara har en int array och kollar i den.
 *
 *
 * För att sedan kolla så det följer mönstret så har man en till array som töms efter varje gång som det tidsintervall som knackningarna motsvarar har passerat(plus någon sekund) och så
 * räknar man bara knackningarna och har koll på tiden med millis() så det blir rätt.
 *
 *
 *
 */


void loop(){
  if(locked == false){
    switchVal = digitalRead(switchPin);
    
    if(switchVal == HIGH){
      lockBox();
    }
  } else if(locked == true){
    knockVal = analogRead(piezo);
    switchVal = digitalRead(switchPin);
    thisTime = millis();
    
    if(switchVal == HIGH){
      resetEnteredKnockCode();
      numberOfKnocks = 0;
      timeFirstKnock = millis();
    }
    
    
    
    if(knockVal > 0 && checkForKnock(knockVal) == true){
      if(numberOfKnocks == 0){
        timeFirstKnock = millis();
      }
      
      numberOfKnocks++;
      
      if(thisTime <= timeFirstKnock + (knockInterval + knockExtraTime)){
        enteredKnockCode[getKnockIndex(thisTime, timeFirstKnock)] += 1;
        // could check the code continously here or simply check in the else below
      } else{
        numberOfKnocks = 0;
        if(enteredCodeMatchesStored()){
          unlockBox();
        } else{
          Serial.println("the entered code does not match the expected one");
          printEnteredKnockCode();
        }
        Serial.println("resetting the knockCode");
        Serial.println(thisTime);
        Serial.println(timeFirstKnock);
        Serial.println(knockInterval);
        
        // reset the entered knock sequence here
        resetEnteredKnockCode();
        // either check the sequence of entered knocks here or if that should already have been checked
      }
      
      Serial.print(3-numberOfKnocks);
      Serial.println(" more knocks to go");
    } else{
      // Serial.println("knockVal: ");
      // Serial.println(knockVal);
      
      if(((thisTime-timeFirstKnock) / intervalLengths) % 2 == 0){
        // Serial.println("lamp on");
        digitalWrite(greenLed, HIGH);
      } else{
        // Serial.println("lamp off");
        digitalWrite(greenLed, LOW);
      }
      
      
      if(enteredCodeMatchesStored()){
        Serial.println("codes match");
        printEnteredKnockCode();
        resetEnteredKnockCode();
        unlockBox();
      } else{
        Serial.println("the entered code does not match the expected one");
        printEnteredKnockCode();
      }
      
      
      
    }
  }
}

/**
 * checks if the knock entered is within the valid interval, in other words is not to quiet and not to loud
 */
boolean checkForKnock(int knockValue){
  if(knockValue > quietKnock && knockValue < loudKnock){
    digitalWrite(yellowLed, HIGH);
    delay(100);
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

/**
 * gets the total number of knocks inside the knockCode "password"
 */
int numberOfKnocksInKnockCode(){
  int numberOfKnocks = 0;
  
  for(int i = 0; i < knockCodeLength; i++){
    numberOfKnocks = knockCode[i];
  }
  
  return numberOfKnocks;
}

/**
 * gets the index for which the knock entered at this current time should be stored in the enteredKnockCode so we can match it against the knockCode array
 */
int getKnockIndex(long currentTime, long timeFirstKnock){
  int slotTime = knockInterval / knockCodeLength;
  int timeDifference = currentTime - timeFirstKnock;
  int index = ceil(timeDifference / slotTime);
  Serial.print("returning index: ");
  Serial.println(index);
  
  return index;
}

/**
 * sets the entered code to all zeros so the array will be clean for the next "open attempt"
 */
int resetEnteredKnockCode(){
 for(int i = 0; i < knockCodeLength; i++){
   enteredKnockCode[i] = 0; 
  } 
}

/**
 * locks "the box"
 */
void lockBox(){
  locked = true;
  digitalWrite(greenLed, LOW);
  digitalWrite(redLed, HIGH);
  myServo.write(90);
  Serial.println("The box is locked");
  delay(100);
}

/**
 * unlocks "the box"
 */
void unlockBox(){
  locked = false;
  myServo.write(0);
  delay(20);
  digitalWrite(greenLed, HIGH);
  digitalWrite(redLed, LOW);
  Serial.println("The box is unlocked");
}

/**
 * returns true if the code currently in the array enteredKnockCode matches the "correct" one inside the knockCode array
 */
boolean enteredCodeMatchesStored(){
  for(int i = 0; i < knockCodeLength; i++){
    if(knockCode[i] != enteredKnockCode[i]){
      return false;
    }
  }
  
  return true;
}

/**
 * prints the knocks that are currently stored inside the array enteredKnockCode
 */
void printEnteredKnockCode(){
 for(int i = 0; i < knockCodeLength; i++){
  Serial.print(enteredKnockCode[i]);
  Serial.print(" ");
 }
 Serial.println("");
 
}
