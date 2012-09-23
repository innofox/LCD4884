#include "LCD4884.h"

#define MENU_X  0      // 0-83
#define MENU_Y  0       // 0-5

int counter = 0;
char string[10];

void setup()
{

  lcd.init();
  lcd.turnBacklightOn(true);
  lcd.clear();
}

void loop(){

  if(++counter < 1000){
    char counterMessage[100] = "Count ";
    char counterAscii[10] = "";
    itoa(counter,counterAscii,10);
    strcat(counterMessage, counterAscii);
    lcd.writeString(MENU_X, MENU_Y + 2, counterMessage, MENU_NORMAL);
  }
  else  counter = 0;
  delay(1);

}

