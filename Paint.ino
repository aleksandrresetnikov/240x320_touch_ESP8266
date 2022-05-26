boolean startVivoPaint = true;
unsigned long buttonTimer = millis() + 150;

byte selectPanel = 1;
unsigned long selectColor = 0xE7E0;
byte sizeBrush = 4;

int colorStackNum = 0; 
const unsigned long colorStack[16][2] = {
  {0xFFFF, 0xEF7D},
  {0xFE60, 10145515},
  {10145515, 0xE7E0},
  {0xFEC0, 0x05B5},
  {0x07EB, 0x0547},
  {11216719, 0x17E0},
  {0xF800, 5147401},
  {0xB800, 10148515},

  {5147901, 0x5812},
  {0x02FF, 11994623},
  {0x0B, 0x27},
  {0x6811, 0xC01F},
  {0xC018, 0xF815},
  {6970061, 0x738E},
  {0xF83B, 0},
  {0, 0}
};

void paint(){
  if (startVivoPaint){startPaint();startVivoPaint = false;}

  int x, y;                   // Переменные для работы с координатами нажатий 
  if(ts.isTouching())         // Пока имеются данные с сенсорного модуля
  {
    x = getTouchPositionsX();                  // Считываем координату нажатия X
    y = getTouchPositionsY();                  // Считываем координату нажатия Y

    if (x < 270 - sizeBrush && y > 25 + sizeBrush + 2){
      tft.setColor(selectColor);
      tft.fillCircle(x, y, sizeBrush); // Рисуем окружность, закрашенную желтым 
    }
    else 
      interfaceClickControl(x,y);
  }
}

void startPaint(){
  tft.clrScr();yield();
  tft.setFont(BigFont);
  drawInterface();yield();
  drawSelectColorControl();yield();
  drawSizeBrushPanel();yield();
}

void drawInterface(){
  drawInscription();
  drawColorPalette();
  drawColorPaletteBorders();
  drawButtons();

  tft.setColor(0xFFFF);
  tft.fillRect(0,25,320,25);
  tft.fillRect(70,0,70,25);
}

void drawInscription(){
  tft.setColor(16600807);
  tft.print("p",3,4);
  tft.setColor(8191310);
  tft.print("a",15,4);
  tft.setColor(16600656);
  tft.print("i",27,4);
  tft.setColor(16643918);
  tft.print("n",39,4);
  tft.setColor(5147901);
  tft.print("t",51,4);
}

void drawColorPalette(){
  if (selectPanel != 1)return;
  
  for (int x = 0; x < 8; x++){
    for (int y = 0; y < 2; y++){
      tft.setColor(colorStack[x + (colorStackNum * 8)][y]);
      tft.fillRect(270 + 25 * y,25 + x * 25,(269 + 25 * y) + 25,(25 + x * 25) + 25);
    }
  }
}

void drawColorPaletteBorders(){
  if (selectPanel != 1)return;

  tft.setColor(0xFFFF);
  tft.fillRect(270,25,270,25 + 320);
  tft.fillRect(295,25,295,25 + 200); 
  tft.fillRect(319,25,319,25 + 320);

  for (int i = 1; i <= 9; i++){
    tft.fillRect(270,i * 25,319,(i * 25));
  }
}

void drawSettimgsPanel(){
  tft.setColor(0);
  tft.fillRect(271,26,319,240);
}

void drawSelectColorControl(){
  tft.setColor(0xFFFF);
  tft.fillRect(70,0,70,25);
  tft.setColor(selectColor);
  tft.fillRect(71,0,95,24);
  tft.setColor(0xFFFF);
  tft.fillRect(96,0,96,25);
}

void drawSizeBrushPanel(){
  tft.setColor(0xFFFF);
  tft.fillRect(96,0,96,25);
  tft.setColor(0);
  tft.fillRect(97,0,140,24);
  tft.setColor(0xFFFF);
  tft.print(String(sizeBrush),104,6);
  tft.setColor(0xFFFF);
  tft.fillRect(141,0,141,25);
}

void drawButtons(){
  tft.setBackColor (0xFFFF);
  tft.setColor(0xFFFF);
  tft.fillRect(143,0,167,25);
  tft.setColor(0);
  tft.print("-",148,5);

  tft.setColor(0xFFFF);
  tft.fillRect(169,0,193,25);
  tft.setColor(0);
  tft.print("+",174,5);

  tft.setColor(0xFFFF);
  tft.fillRect(195,0,219,25);
  tft.setColor(0);
  tft.print("C",200,5);

  tft.setColor(0xFFFF);
  tft.fillRect(221,0,245,25);
  tft.setColor(0);
  tft.print("F",226,5);

  tft.setBackColor (0);

  tft.setColor(0xFFFF);
  tft.fillRect(270,0,270,25);
  tft.fillRect(295,0,295,25);
  tft.fillRect(319,0,319,25);
  tft.setColor(0xFFFF);
  tft.print("<",275,4);
  tft.print(">",301,4);
}

void drawSelectPanel(){
  switch(selectPanel){
    case 1: drawColorPalette(); drawColorPaletteBorders(); break;
    case 2: drawSettimgsPanel(); break;
    default: selectPanel = 1; drawSelectPanel(); break;
  }
}

void interfaceClickControlColorPanel(int x, int y){
  if (y > 25 && y < 50 && x > 270 && x < 295)  selectColor = colorStack[0 + (colorStackNum * 8)][0];
  if (y > 25 && y < 50 && x > 295 && x < 319)  selectColor = colorStack[0 + (colorStackNum * 8)][1];
  if (y > 50 && y < 75 && x > 270 && x < 295)  selectColor = colorStack[1 + (colorStackNum * 8)][0];
  if (y > 50 && y < 75 && x > 295 && x < 319)  selectColor = colorStack[1 + (colorStackNum * 8)][1];
  if (y > 75 && y < 100 && x > 270 && x < 295) selectColor = colorStack[2 + (colorStackNum * 8)][0];
  if (y > 75 && y < 100 && x > 295 && x < 319) selectColor = colorStack[2 + (colorStackNum * 8)][1];
  if (y > 100 && y < 125 && x > 270 && x < 295)selectColor = colorStack[3 + (colorStackNum * 8)][0];
  if (y > 100 && y < 125 && x > 295 && x < 319)selectColor = colorStack[3 + (colorStackNum * 8)][1];
  if (y > 125 && y < 150 && x > 270 && x < 295)selectColor = colorStack[4 + (colorStackNum * 8)][0];
  if (y > 125 && y < 150 && x > 295 && x < 319)selectColor = colorStack[4 + (colorStackNum * 8)][1];
  if (y > 150 && y < 175 && x > 270 && x < 295)selectColor = colorStack[5 + (colorStackNum * 8)][0];
  if (y > 150 && y < 175 && x > 295 && x < 319)selectColor = colorStack[5 + (colorStackNum * 8)][1];
  if (y > 175 && y < 200 && x > 270 && x < 295)selectColor = colorStack[6 + (colorStackNum * 8)][0];
  if (y > 175 && y < 200 && x > 295 && x < 319)selectColor = colorStack[6 + (colorStackNum * 8)][1];
  if (y > 200 && y < 225 && x > 270 && x < 295)selectColor = colorStack[7 + (colorStackNum * 8)][0];
  if (y > 200 && y < 225 && x > 295 && x < 319)selectColor = colorStack[7 + (colorStackNum * 8)][1];
}

void interfaceClickControl(int x, int y){
  SET:;
  if (selectPanel == 1)interfaceClickControlColorPanel(x, y);
  else if (selectPanel == 2);
  else {selectPanel = 1; goto SET;}
  
  if (y > 0 && y < 25 && x > 143 && x < 168)if (sizeBrush > 1 && buttonTimer <= millis()){sizeBrush--; buttonTimer = millis() + 150; drawSizeBrushPanel();}//-
  if (y > 0 && y < 25 && x > 169 && x < 194)if (sizeBrush < 48  && buttonTimer <= millis()){sizeBrush++; buttonTimer = millis() + 150; drawSizeBrushPanel();}//+
  
  if (y > 0 && y < 25 && x > 195 && x < 220){tft.setColor(0); tft.fillRect(0,26,269,26 + 215);}//C
  if (y > 0 && y < 25 && x > 221 && x < 246){tft.setColor(selectColor); tft.fillRect(0,26,269,26 + 215);}//F

  if (y > 0 && y < 25 && x > 270 && x < 295){selectPanel--;if (selectPanel < 1)selectPanel = 2;drawSelectPanel();}//<
  if (y > 0 && y < 25 && x > 295 && x < 319){selectPanel++;if (selectPanel > 2)selectPanel = 1;drawSelectPanel();}//>
  
  if (y > 225 && y < 240 && x > 270 && x < 320){colorStackNum++;if (colorStackNum > 1)colorStackNum = 0; drawColorPalette(); drawColorPaletteBorders();}//...
  drawSelectColorControl();
}
