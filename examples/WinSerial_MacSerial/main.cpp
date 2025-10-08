#include <BeeNeXT.h>

// เลือก WinSerial หรือ MacSerial ตาม platform
#ifdef _WIN32
  WinSerial PC_Port("COM3");
#else
  MacSerial PC_Port("/dev/tty.usbserial"); // ตัวอย่างบน Mac
#endif

void setup() {
  Serial.begin(9600);
  Serial.println();

  Serial.println("Hello Test");

  PC_Port.begin(9600);

  static SoftTimer timer;
  timer.setInterval(10, []() {
    while(PC_Port.available()) {
      String raw = PC_Port.readStringUntil('\n');
      raw.trim();
      Serial.println(raw);
    }
  });
}

void loop() {
  BeeNeXT.update();
}


