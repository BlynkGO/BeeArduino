#include <BeeNeXT.h>

WinSerial COM3("COM3");

void setup(){
  Serial.begin(9600); Serial.println();

  Serial.println("Hello Test");

  COM3.begin(9600);
  static SoftTimer timer;
  timer.setInterval(10,[](){
    if(COM3.available()){
      String raw = COM3.readStringUntil('\n'); raw.trim();
      Serial.println(raw);
    }
  });
}

void loop(){
  BeeNeXT.update();
}

