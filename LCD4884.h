#ifndef LCD4884_H
#define LCD4884_H

#define SPI_SCK 2
#define SPI_MOSI 3
#define LCD_DC 4
#define SPI_CS 5
#define LCD_RST 6
#define LCD_BACKLIGHT 7

// Display Mode (Normal/Highlight)
#define MENU_NORMAL 0
#define MENU_HIGHLIGHT 1
#define OFF 0
#define ON 1

class LCD4884
{
  public:
  LCD4884();
  void init(void);
  void turnBacklightOn(bool switchOn);
  void writeByte(unsigned char data, unsigned char dataType);
  void drawBmpPixel(unsigned char x, unsigned char y, unsigned char *map, unsigned char pixelX, unsigned char pixelY);
  void writeString(unsigned char x, unsigned char y, char *s, char mode);
  void writeStringBig(unsigned char x, unsigned char y, char* string, char mode);
  void writeCharBig(unsigned char x, unsigned char y, unsigned char ch, char mode);
  void writeChar(unsigned char c, char mode);
  void setCursorPosition(unsigned char x, unsigned char y);
  void clear(void);
  
};

extern LCD4884 lcd;

#include <avr/pgmspace.h>

#endif
