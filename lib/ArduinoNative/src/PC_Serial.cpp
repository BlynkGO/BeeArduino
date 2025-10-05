#include "PC_Serial.h"

PC_Serial Serial;

void PC_Serial::print(int n){
  std::printf("%d", n);
  fflush(stdout);
}

void PC_Serial::print(uint32_t n){
  std::printf("%u", n);
  fflush(stdout);
}

void PC_Serial::print(String str){
  std::printf("%s", str.c_str());
  fflush(stdout);
}

void PC_Serial::print(const char* str){
  std::printf("%s", str);
  fflush(stdout);
}

void PC_Serial::print(char* str){
  std::printf("%s", str);
  fflush(stdout);
}  

void PC_Serial::print(float f, int32_t decimal){
  std::printf("%.*f", decimal, f);
  fflush(stdout);
}

void PC_Serial::print(double f, int32_t decimal){
  std::printf("%.*f", decimal, f);
  fflush(stdout);
}
