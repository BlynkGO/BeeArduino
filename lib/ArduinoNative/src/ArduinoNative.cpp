#include <windows.h>
#include <bcrypt.h>  // True Random

#include "ardu_helper.h"
#include "Arduino.h"

#define USE_LGVL_RANDOM   0

#if USE_LGVL_RANDOM
#include "lvgl.h"
#endif

long random(long howsmall, long howbig);

long random( long howbig )
{
#if USE_LGVL_RANDOM
  return lv_rand(0,howbig);
#else
  if ( howbig == 0 )
  {
    return 0 ;
  }
  if (howbig < 0) {
    return (random((long)0, (long)-howbig));
  }

  return random((long)0, howbig);
  // // if randomSeed was called, fall back to software PRNG
  // srand((unsigned int)time(NULL));
  // uint32_t val = rand();
  // return val % howbig;
#endif
}

long random(long howsmall, long howbig)
{
#if USE_LGVL_RANDOM
  return lv_rand(howsmall,howbig);
#else
  unsigned char buffer[4]; // ใช้ 4 ไบต์สำหรับการสร้างเลขสุ่ม 32 บิต
  if (BCryptGenRandom(NULL, buffer, sizeof(buffer), BCRYPT_USE_SYSTEM_PREFERRED_RNG) != 0) {
      return 0;
  }

  // แปลง buffer เป็น unsigned int
  unsigned int random_value = *(unsigned int*)buffer;

  // คำนวณค่าในช่วง howsmall ถึง howbig
  return howsmall + (random_value % (howbig - howsmall + 1));

#endif
}

void randomSeed(unsigned long){
#if USE_LGVL_RANDOM
  lv_rand_set_seed(time(NULL));
#else
  srand((unsigned int)time(NULL));
#endif
}

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
