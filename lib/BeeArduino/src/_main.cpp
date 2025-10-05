
#define BEEARDUINO_USE_LVGL      0

#include <BeeNeXT.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <unistd.h>
#include "ardu_helper.h"

#if BEEARDUINO_USE_LVGL
  #include "utils/lvgl/lvgl.h"
  static lv_display_t * hal_init(int32_t w, int32_t h);
#endif

void _FnNoOpCbk() {}
void setup();
void loop() __attribute__((weak, alias("_FnNoOpCbk")));

#if BEEARDUINO_USE_LVGL
lv_indev_t * mouse;
lv_indev_t * pc_keyboard;
lv_indev_t * mousewheel;
#endif

int main()
{
#if BEEARDUINO_USE_LVGL
  lv_set_font_default(&prasanmit_30);
  lv_init();
  #if defined(LCD_WIDTH) && defined(LCD_HEIGHT)
    hal_init(LCD_WIDTH,LCD_HEIGHT);
  #else
    hal_init(800,480);
  #endif
#endif


#if BEEARDUINO_USE_LVGL
  lv_sdl_window_set_title(lv_disp_get_default(), "BlynkGO กะเพราหมูกรอบ");

  /*Set a tick source so that LVGL will know how much time elapsed. */
  lv_tick_set_cb([]()->uint32_t { return millis(); });
#endif

#if BEEARDUINO_USE_LVGL
  static SoftTimer _timer_graphic;
  _timer_graphic.setInterval(5,[](){ lv_timer_handler(); });
    // _timer_graphic.setInterval(5,[](){
    //   lv_timer_handler();
    //   // lv_tick_inc(5);
    // });
#endif

  setup();

  #if !BEEARDUINO_USE_NOLOOP
  while(1){
    loop();
  }
  #endif
  return 0;
}

#if BEEARDUINO_USE_LVGL
lv_display_t * hal_init(int32_t w, int32_t h)
{

   lv_group_set_default(lv_group_create());

  lv_display_t * disp = lv_sdl_window_create(w, h);
  lv_sdl_window_set_resizeable(disp, true);  // ปรับให้ ขยายได้

  // lv_indev_t * mouse = lv_sdl_mouse_create();
  mouse = lv_sdl_mouse_create();
  lv_indev_set_group(mouse, lv_group_get_default());
  lv_indev_set_display(mouse, disp);
  lv_display_set_default(disp);

  // LV_IMAGE_DECLARE(mouse_cursor_icon); /*Declare the image file.*/
  // lv_obj_t * cursor_obj;
  // cursor_obj = lv_image_create(lv_screen_active()); /*Create an image object for the cursor */
  // lv_image_set_src(cursor_obj, &mouse_cursor_icon);           /*Set the image source*/
  // lv_indev_set_cursor(mouse, cursor_obj);             /*Connect the image  object to the driver*/

  mousewheel = lv_sdl_mousewheel_create();
  lv_indev_set_group(mousewheel, lv_group_get_default());
  lv_indev_set_display(mousewheel, disp);

  pc_keyboard = lv_sdl_keyboard_create();
  // lv_indev_set_group(keyboard, lv_group_get_default());
  lv_indev_set_display(pc_keyboard, disp);

  return disp;
}
#endif // #if BEEARDUINO_USE_LVGL


#ifdef __cplusplus
} // extern "C"
#endif
