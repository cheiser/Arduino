#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int switchPin = 6;
int switchState = 0;
int prevSwitchState = 0;
int replyIndex = 0;

String replies[] = {"YES", "NO", "MAYBE", "MOST LIKELY", "CERTAINLY", "OUTLOOK GOOD", "UNSURE", "ASK AGAIN"};

void setup(){
  lcd.begin(16, 2); // there is 2 rows and 16 columns
  
  pinMode(switchPin, INPUT);
  
  lcd.print("ASK THE");
  lcd.setCursor(0, 1); // move to the second row
  lcd.print("CRYSTAL BALL");
}

void loop(){
  switchState = digitalRead(switchPin);
  
  if(switchState != prevSwitchState){
    if(switchState == LOW){
      replyIndex = random(8); // can simply add replies.length here to have it easy increasing the responses
      
      lcd.clear(); // empties the lcd
      lcd.setCursor(0, 0); // move the cursor back to the beginning
      lcd.print("THE BALL SAYS:");
      lcd.setCursor(0, 1); // next line
      
      lcd.print(replies[replyIndex]);
      
    }
  }
  
  prevSwitchState = switchState;
}

