#define COLOR_TYPE uint16_t // выбранная переменная для хранения цвета (по стандарту uint16-bit)


#define MIN_TEXT_SEZE 1     // минимальный размер текста
#define MAX_TEXT_SEZE 15    // максимальный размер текста


typedef COLOR_TYPE colorRTM;// colorRusTextManager переопределяем тип переменных цвета на выбранный тип (тип переменной)


boolean drawBackgroundStays = true;// отрисовывать - ли фон символов
boolean drawSmallFonteFullBackground = false;// отрисовывать фон для маленьких символов, в высоту как для больших
colorRTM standartDrawColor = 0xFFFF;// стандартный цвет символов
colorRTM standartBackgroundColor = 0x4444;// стандартный цвет фона


boolean standartLineBreakStatys = false;// переносить - ли строку по стандарту
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
    if (i >= text.length() * 2)break;// когда закончили, выходим из цикла
    if (uint8_t(text[i]) == 0x20){ _x += 12; i++; if (lineBreak && _x >= tft.getDisplayXSize() - (12 + corectLineBreakMaxLength)){ _x = x; _y += corectLineBreakY; } continue; }// если пробел
    if (isUniversalChar(text[i])){ printUniversalChar(uint8_t(text[i]),_x, _y); ; _x += 8; i++; if (lineBreak && _x >= tft.getDisplayXSize() - (8 + corectLineBreakMaxLength)){ _x = x; _y += corectLineBreakY; } continue; }// если это универсальный символ, то отрисовываем его отдельно
    if (uint8_t(text[i]) != 0xD0 && uint8_t(text[i]) != 0xD1)break;// если символ не русский выходим из цикла
    
    printRusChar(text[i + 1],_x,_y);// выводим символ
    if (uint8_t(text[i + 1]) >= 144 && uint8_t(text[i + 1]) <= 175)// если символ большой
      _x += 12;
    else if (uint8_t(text[i + 1]) >= 176 && uint8_t(text[i + 1]) <= 191)// если символ маленький
      _x += 9;
    else if (uint8_t(text[i + 1]) >= 128 && uint8_t(text[i + 1]) <= 143)// если символ маленький
      _x += 9;

    if (lineBreak && _x >= tft.getDisplayXSize() - (12 + corectLineBreakMaxLength)){ _x = x; _y += corectLineBreakY; }// если вышли за пределы и если включен перенос строки
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

  
  switch (uint8_t(charCode)){
    case 0x90: drawRusCharB (0, x, y); break;//А  (144) (0x90)
    case 0xB0: drawRusCharS (0, x, y); break;//а  (176) (0xB0)
    
    case 0x91: drawRusCharB (1, x, y); break;//Б  (145) (0x91)
    case 0xB1: drawRusCharS (1, x, y); break;//б  (177) (0xB1)
    
    case 0x92: drawRusCharB (2, x, y); break;//В  (146) (0x92)
    case 0xB2: drawRusCharS (2, x, y); break;//в  (178) (0xB2)

    case 0x93: drawRusCharB (3, x, y); break;//Г  (147) (0x93)
    case 0xB3: drawRusCharS (3, x, y); break;//г  (179) (0xB3)

    case 0x94: drawRusCharB (4, x, y); break;//Д  (148) (0x94)
    case 0xB4: drawRusCharS (4, x, y); break;//д  (180) (0xB4)
  
    case 0x95: drawRusCharB (5, x, y); break;//Е  (149) (0x95)
    case 0xB5: drawRusCharS (0, x, y); break;//е  (181) (0xB5)

    case 0x96: drawRusCharB (6, x, y); break;//Ж  (150) (0x96)
    case 0xB6: drawRusCharS (0, x, y); break;//ж  (182) (0xB6)

    case 0x97: drawRusCharB (7, x, y); break;//З  (151) (0x97)
    case 0xB7: drawRusCharS (0, x, y); break;//з  (183) (0xB7)

    case 0x98: drawRusCharB (8, x, y); break;//И  (152) (0x98)
    case 0xB8: drawRusCharS (0, x, y); break;//и  (184) (0xB8)

    case 0x99: drawRusCharB (8, x, y); break;//Й  (153) (0x99)
    case 0xB9: drawRusCharS (0, x, y); break;//й  (185) (0xB9)

    case 0x9A: drawRusCharB (9, x, y); break;//К  (154) (0x9A)
    case 0xBA: drawRusCharS (0, x, y); break;//к  (186) (0xBA)

    case 0x9B: drawRusCharB(10, x, y); break;//Л  (155) (0x9B)
    case 0xBB: drawRusCharS (0, x, y); break;//л  (187) (0xBB)

    case 0x9C: drawRusCharB(11, x, y); break;//М  (156) (0x9C)
    case 0xBC: drawRusCharS (0, x, y); break;//м  (188) (0xBC)

    case 0x9D: drawRusCharB(12, x, y); break;//Н  (157) (0x9D)
    case 0xBD: drawRusCharS (0, x, y); break;//н  (189) (0xBD)

    case 0x9E: drawRusCharB(13, x, y); break;//О  (158) (0x9E)
    case 0xBE: drawRusCharS (0, x, y); break;//о  (190) (0xBE)

    case 0x9F: drawRusCharB(14, x, y); break;//П  (159) (0x9F)
    case 0xBF: drawRusCharS (0, x, y); break;//п  (191) (0xBF)

    case 0xA0: drawRusCharB(15, x, y); break;//Р  (160) (0xA0)
    case 0x80: drawRusCharS (0, x, y); break;//р  (128) (0x80)

    case 0xA1: drawRusCharB(16, x, y); break;//С  (161) (0xA1)
    case 0x81: drawRusCharS (0, x, y); break;//с  (129) (0x81)

    case 0xA2: drawRusCharB(17, x, y); break;//Т  (162) (0xA2)
    case 0x82: drawRusCharS (1, x, y); break;//т  (130) (0x82)

    case 0xA3: drawRusCharB(18, x, y); break;//У  (163) (0xA3)
    case 0x83: drawRusCharS (2, x, y); break;//у  (131) (0x83)

    case 0xA4: drawRusCharB(19, x, y); break;//ф  (164) (0xA4)
    case 0x84: drawRusCharS (3, x, y); break;//Ф  (132) (0x84)
/*
    case 0xA4: drawRusCharB(19, x, y); break;//Х  (164) (0xA4)
    case 0x84: drawRusCharS (3, x, y); break;//х  (132) (0x84)

    case 0xA4: drawRusCharB(19, x, y); break;//Ц  (164) (0xA4)
    case 0x84: drawRusCharS (3, x, y); break;//ц  (132) (0x84)

    case 0xA4: drawRusCharB(19, x, y); break;//Ч  (164) (0xA4)
    case 0x84: drawRusCharS (3, x, y); break;//ч  (132) (0x84)*/
  } 
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
  if (drawBackgroundStays){ tft.setColor(standartBackgroundColor); tft.fillRect(x,y,x+12,y+12); }
  tft.setColor(standartDrawColor);
  for (int i = 0; i < 144; i++){
    if (bigRusFont[element][i] == 1)
      tft.drawPixel(_x,_y);
    _x++;if (_x >= x + 12){ _x = x; _y++;}
  }
}

void drawRusCharS(uint8_t element, uint16_t x, uint16_t y){
  uint16_t _x = x, _y = y + 3;
  if (drawBackgroundStays){ tft.setColor(standartBackgroundColor); tft.fillRect(x,y + corectSmallFontY,x+9,y+12); }
  tft.setColor(standartDrawColor);
  for (int i = 0; i < 81; i++){
    if (smallRusFont[element][i] == 1)
      tft.drawPixel(_x,_y);
    _x++;if (_x >= x + 9){ _x = x; _y++;}
  }
}

void drawUniversalChar(uint8_t element, uint16_t x, uint16_t y){
  uint16_t _x = x, _y = y;
  if (drawBackgroundStays){ tft.setColor(standartBackgroundColor); tft.fillRect(x,y,x+8,y+12); }
  tft.setColor(standartDrawColor);
  for (int i = 0; i < 96; i++){
    if (universalFont[element][i] == 1)
      tft.drawPixel(_x,_y);
    _x++;if (_x >= x + 8){ _x = x; _y++;}
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
