#include <BeeNeXT.h>

void setup(){
  Serial.begin(9600); Serial.println();

  Serial.println("Hello Test");
  static SoftTimer timer;
  timer.setInterval(1000,[](){
    static int c;
    Serial.println(c++);
  });
}

void loop(){
  BeeNeXT.update();
}

