/*
  LCD4884 Driver
 */
 
 #include "LCD4884.h"
 #include "Arduino.h"
 #include "Fonts.h"
 
 LCD4884::LCD4884()
 { };
 
 LCD4884 lcd = LCD4884();
 
 void LCD4884::turnBacklightOn(bool switchOn)
 {
   if(switchOn == true)
   {
     digitalWrite(LCD_BACKLIGHT, HIGH);
   } else
   {
     digitalWrite(LCD_BACKLIGHT, LOW);
   }
 }
 
 void LCD4884::init(void)
 {
   unsigned int pins[6] = { 2,3,4,5,6,7 };
   // Initialize the 6 pins used by the LCD.
   for(int i = 0; i < 6; i++)
   {
     pinMode(pins[i], OUTPUT);
     digitalWrite(pins[i], LOW);
   }
   
   digitalWrite(LCD_RST, LOW);
   delayMicroseconds(1);
   digitalWrite(LCD_RST, HIGH);
   
   digitalWrite(SPI_CS, LOW);
   delayMicroseconds(1);
   digitalWrite(SPI_CS, HIGH);
   delayMicroseconds(1);
   digitalWrite(LCD_BACKLIGHT, HIGH);
   
   writeByte(0x21, 0);
   writeByte(0xc0, 0);
   writeByte(0x06, 0);
   writeByte(0x13, 0);
   writeByte(0x20, 0);
   clear();
   writeByte(0x0c, 0);
   
   digitalWrite(SPI_CS, LOW);
 }
 
 void LCD4884::writeByte(unsigned char data, unsigned char dataType)
 {
   unsigned int i;
   
   digitalWrite(SPI_CS, LOW);
   
   if(dataType == 0) digitalWrite(LCD_DC, LOW);
     else digitalWrite(LCD_DC, HIGH);
   
   for(i = 0; i < 8; i++)
   {
     if(data & 0x80) digitalWrite(SPI_MOSI, HIGH);
       else digitalWrite(SPI_MOSI, LOW);
     
     digitalWrite(SPI_SCK, LOW);
     data = data << 1;
     digitalWrite(SPI_SCK, HIGH);
   }
   
   digitalWrite(SPI_CS, HIGH);
 }
 
 void LCD4884::writeCharBig(unsigned char x, unsigned char y, unsigned char ch, char mode)
 {
   unsigned char i, j;
   unsigned char *pFont;
   unsigned char ch_dat;
   
   pFont = (unsigned char*) big_number;
   
   if(ch == '.')
   {
     ch = 10;
   } else if(ch == '+')
   {
     ch = 11;
   } else if(ch == '-')
   {
     ch = 12;
   } else
   {
     ch = ch & 0x0F;
   }
   
   for(i=0; i < 3; i++)
   {
     setCursorPosition(x, y+i);
     
     for(j=0; j < 16; j++)
     {
       ch_dat = pgm_read_byte(pFont + ch * 48 + i * 16 + j);
       writeByte( (mode == MENU_NORMAL) ? ch_dat : (ch_dat ^ 0xFF), 1);
     }
   }
 }
 
 void LCD4884::writeChar(unsigned char c, char mode)
 {
   unsigned char line;
   unsigned char *pFont;
   byte ch;
   
   pFont = (unsigned char*) font6_8;
   c -= 32;
   
   for(line = 0; line < 6; line++)
   {
     ch = pgm_read_byte(pFont + c * 6 + line);
     writeByte( (mode==MENU_NORMAL) ? ch : (ch ^ 0xff), 1);
   }
 }
 
 void LCD4884::setCursorPosition(unsigned char x, unsigned char y)
 {
   writeByte(0x40 | y, 0);
   writeByte(0x80 | x, 0);
 }
 
 void LCD4884::clear(void)
 {
   unsigned int i;
   
   writeByte(0x0C, 0);
   writeByte(0x80, 0);
   
   for(i=0; i < 504; i++) writeByte(0,1);
 }
 
 void LCD4884::writeString(unsigned char X, unsigned char Y, char* s, char mode)
 {
   setCursorPosition(X, Y);
   
   while(*s)
   {
     writeChar(*s, mode);
     s++;
   }
 }
 
 void LCD4884::writeStringBig(unsigned char x, unsigned char y, char* string, char mode)
 {
   while(*string)
   {
     writeCharBig(x, y, *string, mode);
     
     if(*string++ == '.') x += 5;
       else x += 12;
   }
 }
