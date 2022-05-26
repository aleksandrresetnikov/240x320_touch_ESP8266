#include "UTFT_Rus_Text_Manager_Font.h"


#define COLOR_TYPE uint16_t // выбранная переменная для хранения цвета (по стандарту uint16-bit)


#define MIN_TEXT_SEZE 1     // минимальный размер текста
#define MAX_TEXT_SEZE 15    // максимальный размер текста


typedef COLOR_TYPE colorRTM;// colorRusTextManager переопределяем тип переменных цвета на выбранный тип (тип переменной)


boolean drawBackgroundStays = true;// отрисовывать фон символов
boolean drawSmallFonteFullBackground = false;// отрисовывать фон для маленьких символов, в высоту как для больших
boolean drawBoldFont = false;// отрисовывать жирные символы
colorRTM standartDrawColor = 0xFFFF;// стандартный цвет символов
colorRTM standartBackgroundColor = 0x0000;// стандартный цвет фона


boolean standartLineBreakStatys = false;// переноситб строку (по стандарту)
uint16_t corectLineBreakMaxLength = 0;
uint16_t corectLineBreakY = 14;// при переносе строки как корректировать Y текста


uint8_t textSize = 1;


//======НЕ ТРОГАТЬ======
uint16_t corectSmallFontY = 0;
//======НЕ ТРОГАТЬ======


boolean printingRusTextCenter(String text, uint16_t y){
  return true;// возвращается результат (если 0 - то ошибка вывода)
}

boolean printingRusText(String text, uint16_t x, uint16_t y){
  return (_printingRusText(text,x,y,standartLineBreakStatys));// возвращается результат (если 0 - то ошибка вывода)
}

boolean printingRusText(String text, uint16_t x, uint16_t y, boolean lineBreak){
  return (_printingRusText(text,x,y,lineBreak));// возвращается результат (если 0 - то ошибка вывода)
}

boolean _printingRusText(String text, uint16_t x, uint16_t y, boolean lineBreak){
  // --Данный метод поддерживает вывод только русских символов
  // --При попытке вывода иностранных символов цикл завершается
  if (text.length() <= 0)return 0;// если текст пустой, выходим
  startPrintingText();// перед выводом
  
  uint16_t _x = x, _y = y;// создаём переменные для хранения данных x, y
  for (uint32_t i = 0; ;){// бегаем по тексту
    yield();
    if (y >= tft.getDisplayXSize())break;// если вышли за границы
    if (i >= text.length() * 2)break;// когда закончили, выходим из цикла
    if (uint8_t(text[i]) == 0x20){ _x += (12*textSize); i++; if (lineBreak && _x >= tft.getDisplayXSize() - ((12*textSize) + corectLineBreakMaxLength)){ _x = x; _y += (corectLineBreakY*textSize); } continue; }// если пробел
    if (isUniversalChar(text[i])){ printUniversalChar(uint8_t(text[i]),_x, _y); ; _x += (8*textSize); i++; if (lineBreak && _x >= tft.getDisplayXSize() - ((8*textSize) + corectLineBreakMaxLength)){ _x = x; _y += (corectLineBreakY*textSize); } continue; }// если это универсальный символ, то отрисовываем его отдельно
    if (uint8_t(text[i]) != 0xD0 && uint8_t(text[i]) != 0xD1)break;// если символ не русский выходим из цикла
    
    printRusChar(text[i + 1],_x,_y);// выводим символ
    if (uint8_t(text[i + 1]) >= 144 && uint8_t(text[i + 1]) <= 175)// если символ большой
      _x += (12*textSize);
    else if (uint8_t(text[i + 1]) >= 176 && uint8_t(text[i + 1]) <= 191)// если символ маленький
      _x += (9*textSize);
    else if (uint8_t(text[i + 1]) >= 128 && uint8_t(text[i + 1]) <= 143)// если символ маленький
      _x += (9*textSize);

    if (lineBreak && _x >= tft.getDisplayXSize() - ((12*textSize) + (corectLineBreakMaxLength*textSize))){ _x = x; _y += (corectLineBreakY*textSize); }// если вышли за пределы и если включен перенос строки
    i+=2;
  }
  return 1;
}

void startPrintingText(){
  // коррекция маленьких символов 
  if (!drawSmallFonteFullBackground)corectSmallFontY = 3;
  else corectSmallFontY = 0;

  // коррекция размера шрифта
  if (textSize < MIN_TEXT_SEZE)textSize = MIN_TEXT_SEZE;
  else if (textSize < MIN_TEXT_SEZE)textSize = MIN_TEXT_SEZE;
  
}

void printRusChar(char charCode, uint16_t x, uint16_t y){
  /*
    Подробнее о шифровке на : https://wiki.iarduino.ru/page/encoding-arduino/
    Система кодировки UTF-8 (русские символы)
  */
  
  if (uint8_t(charCode) >= 0x90 && uint8_t(charCode) <= 0xAF)drawRusCharB (uint8_t(charCode) - 0x90, x, y);
  else if (uint8_t(charCode) >= 0xB0 && uint8_t(charCode) <= 0xBF)drawRusCharS (uint8_t(charCode) - 0xB0, x, y);
  else if (uint8_t(charCode) >= 0x80 && uint8_t(charCode) <= 0x8F)drawRusCharS (uint8_t(charCode) - (0x80 + 15), x, y);
  else return;
}

void printUniversalChar(uint8_t charCode, uint16_t x, uint16_t y){
  /*
    Подробнее о шифровке на : https://wiki.iarduino.ru/page/encoding-arduino/
    Система кодировки UTF-8 (русские символы)
  */
  
  uint8_t element = charCode - 33;
  if (element > 30)return;// если вышли за пределы универсальных символов, прерываем функцю и ничего не выводим
  else drawUniversalChar(element,x,y);
}

void drawRusCharB(uint8_t element, uint16_t x, uint16_t y){
  uint16_t _x = x, _y = y;
  if (drawBackgroundStays){ tft.setColor(standartBackgroundColor); tft.fillRect(x,y,x+(12*textSize),y+(12*textSize)); }
  tft.setColor(standartDrawColor);
  for (int i = 0; i < 144; i++){
    if (bigRusFont[element][i] == 1)
      tft.fillRect(_x,_y,_x+getZizeDrawFont(),_y+getZizeDrawFont());
    _x+=textSize;if (_x >= x + (12*textSize)){ _x = x; _y+=textSize;}
  }
}

void drawRusCharS(uint8_t element, uint16_t x, uint16_t y){
  if (element > 15)element = 0;
  uint16_t _x = x, _y = y + (3*textSize);
  if (drawBackgroundStays){ tft.setColor(standartBackgroundColor); tft.fillRect(x,y + (corectSmallFontY * textSize),x+(9*textSize),y+(12*textSize)); }
  tft.setColor(standartDrawColor);
  for (int i = 0; i < 81; i++){
    if (smallRusFont[element][i] == 1)
      tft.fillRect(_x,_y,_x+getZizeDrawFont(),_y+getZizeDrawFont());
    _x+=textSize;if (_x >= x + (9*textSize)){ _x = x; _y+=textSize;}
  }
}

void drawUniversalChar(uint8_t element, uint16_t x, uint16_t y){
  uint16_t _x = x, _y = y;
  if (drawBackgroundStays){ tft.setColor(standartBackgroundColor); tft.fillRect(x,y,x+(8*textSize),y+(12*textSize)); }
  tft.setColor(standartDrawColor);
  for (int i = 0; i < 96; i++){
    if (universalFont[element][i] == 1)
      tft.fillRect(_x,_y,_x+getZizeDrawFont(),_y+getZizeDrawFont());
    _x+=textSize;if (_x >= x + (8*textSize)){ _x = x; _y+=textSize;}
  }
}

boolean isUniversalChar(char charCode){
  // --Если символ универсальный

  if (uint8_t(charCode) > 0x20 && uint8_t(charCode) < 0x40)return true;
  else return false;
}

struct Vector2I{
  uint16_t x, y;
  Vector2I(uint16_t _x, uint16_t _y){
    x = _x;y = _y;
  }
};

uint16_t getZizeDrawFont(){
  if (drawBoldFont)return textSize;
  else return textSize - 1;
}
