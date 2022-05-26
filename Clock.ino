uint64_t clockATimer1 = millis() + 1000;

int timeNumS = 0;
int timeNumM = 29;
int timeNumH = 18;

boolean startVivoClock = true;

void clockA(){
  if (startVivoClock){startClockA();startVivoClock = false;}
  clockManager();
}

void startClockA(){
  tft.setColor(0xFFFF);
  tft.fillCircle(120,120,112);yield();
  clearClockFace();
}

void clockManager(){
  if (clockATimer1 > millis())return;
  clockATimer1 = millis() + 1000; 
  timeNumS++;
  if (timeNumS >= 60){ timeNumM++; timeNumS = 0; }
  if (timeNumM >= 60){ timeNumH++; timeNumM = 0; }
  if (timeNumH >= 24){ timeNumH = 0; timeNumM = 0; timeNumS = 0; }
  drawClockFace();
}

void drawClockFace(){ 
  int lineXS = 0, lineYS = 0;
  int lineXM = 0, lineYM = 0;
  int lineXH = 0, lineYH = 0;

  int ClineXS = 0, ClineYS = 0;
  int ClineXM = 0, ClineYM = 0;
  int ClineXH = 0, ClineYH = 0;

  if (timeNumH == 11 && timeNumM == 59 && timeNumS == 59){ clearClockFace(); return; }
  if (timeNumH == 23 && timeNumM == 59 && timeNumS == 59){ clearClockFace(); return; }

  for (int rot = 0; rot < 360; rot+=6){
    if (radians(rot - 90) == radians((timeNumS * 6 ) - 90)){
      ClineXS = (int)(120 + cos(radians(rot - 96))*95);
      ClineYS = (int)(120 + sin(radians(rot - 96))*95);
      lineXS = (int)(120 + cos(radians(rot - 90))*95);
      lineYS = (int)(120 + sin(radians(rot - 90))*95);
    }
    if (radians(rot - 90) == radians((timeNumM * 6 ) - 90)){
      ClineXM = (int)(120 + cos(radians(rot - 96))*75);
      ClineYM = (int)(120 + sin(radians(rot - 96))*75);
      lineXM = (int)(120 + cos(radians(rot - 90))*75);
      lineYM = (int)(120 + sin(radians(rot - 90))*75);
    }
    if (timeNumH < 12 && radians(rot - 90) == radians((timeNumH * 30) - 90)){
      ClineXH = (int)(120 + cos(radians(rot - 120))*60);
      ClineYH = (int)(120 + sin(radians(rot - 120))*60);
      lineXH = (int)(120 + cos(radians(rot - 90))*60);
      lineYH = (int)(120 + sin(radians(rot - 90))*60);
    }
    if (timeNumH >= 12 && radians(rot - 90) == radians(((timeNumH - 12) * 30) - 90)){
      ClineXH = (int)(120 + cos(radians(rot - 120))*60);
      ClineYH = (int)(120 + sin(radians(rot - 120))*60);
      lineXH = (int)(120 + cos(radians(rot - 90))*60);
      lineYH = (int)(120 + sin(radians(rot - 90))*60);
    }
    
    yield();
    
    int radius = 1;
    if ((rot / 6) % 5==0)radius = 4;
    tft.setColor(0xFFFF);
    tft.fillCircle(120 + cos(radians(rot - 90))*100,120 + sin(radians(rot - 90))*100, radius);
  }
  yield();
  
  tft.setColor(0x32D3);
  tft.drawLine(120,120,ClineXS,ClineYS);
  tft.setColor(0x32D3);
  tft.drawLine(120,120,ClineXM,ClineYM);
  tft.setColor(0x32D3);
  tft.drawLine(120,120,ClineXH,ClineYH);
  
  tft.setColor(0xFFFF);
  tft.drawLine(120,120,lineXS, lineYS);
  tft.setColor(0x0000);
  tft.drawLine(120,120,lineXM, lineYM);
  tft.setColor(0xEF64);
  tft.drawLine(120,120,lineXH, lineYH);
  
  tft.setColor(0xFFFF);
  tft.fillCircle(120,120,5);

  drawClockNum();
}

void drawClockNum(){
  //rect(2,398,396,50);
  printingRusText(returnUnNumText(timeNumH) + ":" + returnUnNumText(timeNumM) + ":" + returnUnNumText(timeNumS),243,114);
}

void clearClockFace(){
  tft.setColor(0x32D3);
  tft.fillCircle(120,120,110);yield();
}

String returnUnNumText(int num){
  String ret = "0";ret += num;
  if(num < 10)return ret;
  else return (String)num;
}
