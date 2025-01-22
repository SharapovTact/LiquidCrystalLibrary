#include "S6B0108lib.h"

S6B0108 lcd(A0,A1,A2,4,3,2,5,6,7,8,9,12,10,11,13);

void setup(){
  Serial.begin(9600);
  pinMode(A4, INPUT_PULLUP);
  pinMode(A5, INPUT_PULLUP);
  
  
  lcd.initGLCD();
  //lcd.setDisplayStartPageX();
  lcd.clearDisplay();
  //lcd.setPoint(0,0);
  lcd.setLine(10,10,10,0);
  lcd.setLine(10,10,20,10);
  lcd.setLine(10,10,10,20);
  lcd.setLine(10,10,0,10);

  lcd.setLine(10,10,15,5);
  lcd.setLine(10,10,5,5);
  
  lcd.setLine(10,10,15,15);
  lcd.setLine(10,10,5,15);

  
}
void loop(){

  
 if(analogRead(A5) < 999){
  lcd.clearDisplay();
  
 }
 if(analogRead(A4) < 999){
  lcd.rectangle(40, 32, 128, 20);
 }
}
