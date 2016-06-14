int notes[] = {262, 294, 330, 340, 349};

const int soundPin = 8;
const int keyBoardPin = A0;

void setup(){
  Serial.begin(9600);
  pinMode(soundPin, OUTPUT);
  pinMode(keyBoardPin, INPUT);
}

void loop(){
  int keyValue = analogRead(keyBoardPin);
  Serial.println(keyValue);
  
  if(keyValue == 1023){
    tone(soundPin, notes[0]);
  } else if(keyValue >= 990 && keyValue <= 1010){
    tone(soundPin, notes[1]);
  } else if(keyValue > 511 && keyValue <= 515){
    tone(soundPin, notes[3]);
  } else if(keyValue >= 505 && keyValue <= 515){
    tone(soundPin, notes[2]);
  }  else if(keyValue >= 5 && keyValue <= 10){
    tone(soundPin, notes[4]);
    // digitalWrite(soundPin, HIGH);
  } else{
    noTone(soundPin);
  }
}
