#include <Elegoo_GFX.h>    // Core graphics library
#include <Elegoo_TFTLCD.h> // Hardware-specific library

#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4

//some colors
#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define ORANGE  0xFBE0



Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);



void setup() {

  tft.reset();

  uint16_t identifier = tft.readID();

  //
  if(identifier == 0x9325) {
    Serial.println(F("Found ILI9325 LCD driver"));
  } else if(identifier == 0x9328) {
    Serial.println(F("Found ILI9328 LCD driver"));
  } else if(identifier == 0x4535) {
    Serial.println(F("Found LGDP4535 LCD driver"));
  }else if(identifier == 0x7575) {
    Serial.println(F("Found HX8347G LCD driver"));
  } else if(identifier == 0x9341) {
    Serial.println(F("Found ILI9341 LCD driver"));
  } else if(identifier == 0x8357) {
    Serial.println(F("Found HX8357D LCD driver"));
  } else if(identifier==0x0101)
  {     
      identifier=0x9341;
       Serial.println(F("Found 0x9341 LCD driver"));
  }
  else if(identifier==0x1111)
  {     
      identifier=0x9328;
       Serial.println(F("Found 0x9328 LCD driver"));
  }
  else {
    Serial.print(F("Unknown LCD driver chip: "));
    Serial.println(identifier, HEX);
    Serial.println(F("If using the Elegoo 2.8\" TFT Arduino shield, the line:"));
    Serial.println(F("  #define USE_Elegoo_SHIELD_PINOUT"));
    Serial.println(F("should appear in the library header (Elegoo_TFT.h)."));
    Serial.println(F("If using the breakout board, it should NOT be #defined!"));
    Serial.println(F("Also if using the breakout, double-check that all wiring"));
    Serial.println(F("matches the tutorial."));
    identifier=0x9328;
  
  }


  tft.begin(identifier);
  Serial.begin(9600);
 

}


boolean firstStart = true;
const double barFactor = 0.9;
const double ramBarFactor = 5.625; //16GB RAM
const double gpuFanFactor = 0.024;

//Previous values
String cpuTempp ="";
String gpuTempp ="";
String cpuUsagep ="";
String gpuUsagep ="";
String ramUsagep ="";
String powerDrawp = "";
String powerDrawMaxp = "";
String gpuFanp = "";
String cpuFanp = "";



//*Update functions*

//update cpuBar
void updateCpuBar(String usage){
  if(!usage.equals(cpuUsagep) or cpuUsagep.equals("")){
    int barpos = 110-usage.toInt()*barFactor; 
    tft.fillRoundRect(26, 21, 128, 90,10, BLACK);
    
    int u = usage.toInt();
    if(u < 30){
      tft.fillRoundRect(26, barpos, 128, 110-barpos,10, BLUE); 
    }
    else if(u >= 30 and u <=70){
      tft.fillRoundRect(26, barpos, 128, 110-barpos,10, ORANGE);
    }
    else{
     tft.fillRoundRect(26, barpos, 128, 110-barpos,10, RED);
    }
    
    cpuFanp = usage;
   
  }
}
//update Cpu temperature
void updateCpuTemp(String temp){
   if(!temp.equals(cpuTempp) or cpuTempp.equals("")){
    tft.setCursor(105, 5);
    tft.fillRect(105, 0, 20, 20, BLACK);
    tft.print(temp);
    cpuTempp = temp;
   }
  }

//update Gpu Temperature
void updateGpuTemp(String temp){
   if(!temp.equals(cpuTempp) or cpuTempp.equals("")){
    tft.setCursor(245, 5);
    tft.fillRect(245, 0, 20, 20, BLACK);
    tft.print(temp);
    cpuTempp = temp;
   }
  }

//update Gpu bar
void updateGpuBar(String usage){
  if(!usage.equals(gpuUsagep) or gpuUsagep.equals("")){
    int barpos = 110-usage.toInt()*barFactor; 
    tft.fillRoundRect(166, 21, 128, 90, 10, BLACK);
      
    int u = usage.toInt();
    if(u < 30){
      tft.fillRoundRect(166, barpos, 128, 110-barpos, 10, BLUE); 
    }
    else if(u >= 30 and u<=70){
      tft.fillRoundRect(166, barpos, 128, 110-barpos, 10, ORANGE);
    }
    else{
     tft.fillRoundRect(166, barpos, 128, 110-barpos, 10, RED);
    }
    gpuUsagep = usage;
   
  }
}

//update Gpu fan bar
void updateGpuFanBar(String usage){
  if(!usage.equals(gpuFanp) or gpuFanp.equals("")){
    int barpos = 110-usage.toInt()*barFactor; 
    tft.fillRect(301, 21, 8, 90, BLACK);

    int u = usage.toInt();
    if(u < 30){
      tft.fillRect(301, barpos, 8, 110-barpos, BLUE); 
    }
    else if(u >= 30 and u<=70){
      tft.fillRect(301, barpos, 8, 110-barpos, ORANGE);
    }
    else{
     tft.fillRect(301, barpos, 8, 110-barpos, RED);
    }
    gpuFanp = usage;
   
  }
}

//update cpu fan bar
void updateCpuFanBar(String usage){
  if(!usage.equals(cpuFanp) or cpuFanp.equals("")){

    int u = usage.toInt();
    double usagetemp = ((double)u / 1900)* 100;
    int usagePercent = (int)usagetemp;
    int barpos = 110-usagePercent*barFactor; 
    tft.fillRect(11, 21, 8, 90, BLACK);
    
    if(usagePercent < 30){
      tft.fillRect(11, barpos, 8, 110-barpos, BLUE); 
    }
    else if(usagePercent >= 30 and usagePercent<=70){
      tft.fillRect(11, barpos, 8, 110-barpos, ORANGE);
    }
    else{
     tft.fillRect(11, barpos, 8, 110-barpos, RED);
    }
    cpuFanp = usage;
   
  }
}

//update update ram bar
void updateRamBar(String usage){
  if(!usage.equals(ramUsagep) or ramUsagep.equals("")){
    int barpos = 210-usage.toInt()*ramBarFactor; 
    tft.fillRoundRect(26, 120, 128, 90, 10, BLACK);


    int u = usage.toInt();
    if(u < 30){
      tft.fillRoundRect(26, barpos, 128, 210-barpos, 10, BLUE); 
    }
    else if(u >= 30 and u <=70){
      tft.fillRoundRect(26, barpos, 128, 210-barpos, 10, ORANGE);
    }
    else{
     tft.fillRoundRect(26, barpos, 128, 210-barpos, 10, RED);
    }
    ramUsagep = usage;
   
  }
}

//update current draw
void updateCurrentDraw(String usage){
  if(!usage.equals(powerDrawp) or powerDrawp.equals("")){
    tft.fillRect(190, 155, 40, 20, BLACK);
    tft.setCursor(190, 155); tft.setTextSize(2);
    tft.print(usage);
    powerDrawp = usage;
  }
}

//update max draw
void updateMaxDraw(String usage){
  if(!usage.equals(powerDrawMaxp) or powerDrawMaxp.equals("")){
    tft.fillRect(240, 155, 40, 20, BLACK);
    tft.setCursor(240, 155); tft.setTextSize(2);
    tft.print(usage);
    powerDrawMaxp = usage;
  }
}


void loop() {
 
  if(firstStart == true){
    //Background Color
    tft.fillScreen(BLACK);
    //Horizontal orientation
    tft.setRotation(1);
    firstStart = false;
  }

  //draw Rectangles for CPU/GPU/RAM...

  //CPU rectangle (top left)
  tft.drawRoundRect(25, 20, 130, 90, 10, WHITE);
  //CPU FAN Rectangle
  tft.drawRoundRect(10, 20, 10, 90, 3, WHITE);
  //GPU rectangle (top right)
  tft.drawRoundRect(165, 20, 130, 90, 10, WHITE);
  //GPUFAN rectangle
  tft.drawRoundRect(300, 20, 10, 90, 3, WHITE);
  //RAM rectangle (buttom left)
  tft.drawRoundRect(25, 120, 130, 90, 10, WHITE);
  //POWER rectangle
  //tft.drawRect(165, 120, 130, 40, 10, WHITE);

  //CPU text
  tft.setCursor(73, 35); tft.setTextSize(2);
  tft.print("CPU");

  //CPU temperature
  tft.setCursor(25, 5); tft.setTextSize(1);
  tft.print("Temperature: ");

  //GPU text 
  tft.setCursor(213, 35);tft.setTextSize(2);
  tft.print("GPU");

  //GPU temperature
  tft.setCursor(165, 5); tft.setTextSize(1);
  tft.print("Temperature: ");
  
  //RAM text
  tft.setCursor(73, 135); tft.setTextSize(2);
  tft.print("RAM");
  
  //Power text
  tft.setCursor(210, 120);
  tft.print("Power:");

  //curr(ently) text
  tft.setCursor(200, 145); tft.setTextSize(1);
  tft.print("curr:");
  
  //max text
  tft.setCursor(250, 145);
  tft.print("max");
  
  //time text 
  //tft.setCursor(200, 175);
  //tft.print("Operation time");

 

  //Reading Serial input
  if(Serial.available() > 1){
      String infoAll = Serial.readString(); //pattern: cpuTemp(0-2) | gpuTemp(2-4) | cpuUsage(4-6) | gpuUsage(6-8)...
      String cpuTemp = infoAll.substring(0,2);
      String gpuTemp = infoAll.substring(2,4);
      String cpuUsage = infoAll.substring(4,6);
      String gpuUsage = infoAll.substring(6,8);
      String ramUsage = infoAll.substring(8, 10);
      String powerDraw = infoAll.substring(10, 13);
      String powerDrawM = infoAll.substring(13, 16);
      String gpuFan = infoAll.substring(16, 19);
      String cpuFan = infoAll.substring(19, 23);

      updateCpuBar(cpuUsage);
      updateGpuBar(gpuUsage);
      updateCpuTemp(cpuTemp);
      updateGpuTemp(gpuTemp);
      updateRamBar(ramUsage);
      updateCurrentDraw(powerDraw);
      updateMaxDraw(powerDrawM);
      updateGpuFanBar(gpuFan);
      updateCpuFanBar(cpuFan);

     
      
  }



}
