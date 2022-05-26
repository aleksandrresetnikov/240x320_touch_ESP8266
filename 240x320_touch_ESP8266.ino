#include <Arduino.h>
#include <SPI.h> // not necessary if Arduino IDE version >=1.6.6
#include <avr/pgmspace.h>

#include <UTFT.h>
#include <XPT2046.h>
#include "BitMaps.h"

extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t BigFontRus[];

UTFT tft(ILI9341_S5P, 15, 5, 4);
XPT2046 ts(/*cs=*/ 2, /*irq=*/ 5);

void setup () {
  randomSeed(analogRead(0));
  
  tft.InitLCD();
  tft.setFont(BigFont);
  tft.setBrightness(2);
  tft.clrScr();

  ts.begin(240,320);
  ts.setCalibration(209, 1759, 1775, 273);

  Serial.begin(115200);
  
  uint32_t timer = millis();
  //printingRusText("АаБбВвГгДдЕеЖжЗзИиЙйКкЛлМмНнОоПпРрСсТтУуФфХхЦцЧчШшЩщЪъЫыЬьЭэЮюЯя!\"#$%&'()*+,-./:;<=>?",10,10,true);
  Serial.println(millis() - timer);
}

void loop () {
  //clockA();
  paint();
}

uint32_t BTx = 0, BTy = 0, BTi = 0;
void drawBitmapM(){
  BTi++;BTx++;
  if (BTx >= 320){BTx = 0; BTy++;}
  if (BTy >= 210){delay(10000); BTi = 0; BTx = 0; BTy = 0;tft.clrScr();}
  tft.setColor(pgm_read_word(&bitmapImage2[BTi]));
  tft.drawPixel(BTx,BTy);
}

int getTouchPositionsX(){
  uint16_t x, y;
  if (ts.isTouching()){
    ts.getPosition(x, y);
    if ((240 - (int)(x - 7)) < 1000 && (240 - (int)(x - 7)) > -1)
      return (int)(y - 7);
  }
}

int getTouchPositionsY(){
  uint16_t x, y;
  if (ts.isTouching()){
    ts.getPosition(x, y);
    if ((240 - (int)(x - 7)) < 1000 && (240 - (int)(x - 7)) > -1)
      return 240 - (int)(x + 7);
  }
}

String utf8rus(String source)
{
  int i,k;
  String target;
  unsigned char n;
  char m[2] = { '0', '\0' };

  k = source.length(); i = 0;

  while (i < k) {
    n = source[i]; i++;

    if (n >= 0xC0) {
      switch (n) {
        case 0xD0: {
          n = source[i]; i++;
          if (n == 0x81) { n = 0xA8; break; }
          if (n >= 0x90 && n <= 0xBF) n = n + 0x30;
          break;
        }
        case 0xD1: {
          n = source[i]; i++;
          if (n == 0x91) { n = 0xB8; break; }
          if (n >= 0x80 && n <= 0x8F) n = n + 0x70;
          break;
        }
      }
    }
    m[0] = n; target = target + String(m);
  }
return target;
}
