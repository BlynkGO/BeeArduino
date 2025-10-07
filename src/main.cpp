#include <BeeNeXT.h>

WinSerial COM3("COM3");

void setup(){
  Serial.begin(9600); Serial.println();

  Serial.println("Hello Test");

  COM3.begin(9600);
  static SoftTimer timer;
  timer.setInterval(10,[](){
    if(COM3.available()){
      int c = COM3.readStringUntil('\n').toInt();
      Serial.println(c);
    }
  });
}

void loop(){
  BeeNeXT.update();
}

