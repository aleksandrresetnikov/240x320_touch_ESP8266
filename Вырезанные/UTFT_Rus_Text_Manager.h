/*
  -Версия : 1.0

  -Разработчик : Решетников Александр А.
  -Дата : 30.08.2021

  -Библиотека заточена на выводе русского шрифта с поддержкой доп. символов 
  -Библиотека не является нарушением авторского права разработчика библиотеки UTFT, а является только дополнением
*/

/*
  -Version: 1.0

  -Developer: Reshetnikov Alexander A.
  -Date: 08/30/2021

  -The library is sharpened on the output of the Russian font with support for additional. symbols
  -The library is not an infringement of the copyright of the developer of the UTFT library, and is also an add-on
*/


#include <Arduino.h>
#include <UTFT.h> // 
#include <SPI.h> // not necessary if Arduino IDE version >=1.6.6
#include "UTFT_Rus_Text_Manager_Font.h"


#define C_WHITE 0xFFFF
#define C_BLACK 0x0000


class UTFT_Rus_Text_Manager{
public:
  UTFT_Rus_Text_Manager(UTFT _tft){
    UTFT_Type = _tft;
    textColor = C_WHITE;
    drawTextBackground = false;
    backColor = C_BLACK;
  }

  void setUTFT_Type(UTFT _tft){ UTFT_Type = _tft; }
  void setRusTextColor(uint16_t _textColor){ textColor = _textColor; }
  void setDrawRusTextBackgroundStatys(boolean statys){ drawTextBackground = statys; }
  void setRusBackColor(uint16_t _backColor){ backColor = _backColor; }

  UTFT getUTFT_Type(){ return UTFT_Type; }
  uint16_t getRusTextColor(){return textColor; }
  boolean getDrawRusTextBackgroundStatys(){ return drawTextBackground; }
  uint16_t getRusBackColor(){ return backColor; }

private:
  UTFT UTFT_Type;
  uint16_t textColor;
  boolean drawTextBackground;
  uint16_t backColor;
}
