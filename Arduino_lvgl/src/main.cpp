#include <Arduino.h>

#include <Wire.h>

#include <SPI.h>
#include <TFT_eSPI.h>
#include "FT62XXTouchScreen.h"

TFT_eSPI tft = TFT_eSPI(); /* TFT instance */
FT62XXTouchScreen touchScreen = FT62XXTouchScreen(TFT_WIDTH, PIN_SDA, PIN_SCL);

#include "lvgl.h"
#include "esp_freertos_hooks.h"

static lv_disp_buf_t disp_buf;
static lv_color_t buf[LV_HOR_RES_MAX * 10];

lv_obj_t *btn1;
lv_obj_t *btn2;
lv_obj_t *btn3;
lv_obj_t *screenMain;
lv_obj_t *label;
lv_obj_t *slider;
lv_obj_t *sw;

static void event_handler_btn(lv_obj_t *obj, lv_event_t event)
{
  if (event == LV_EVENT_CLICKED)
  {
    if (obj == btn1)
      lv_label_set_text(label, "Hello");
    else if (obj == btn2)
    {
      lv_label_set_text(label, "Goodbye");
    }
    else if (obj == btn3)
    {
      lv_label_set_text(label, "Riri");
    }
    else if (obj == slider)
    {
      char buffer[50];
      int v = sprintf(buffer, "value  %d", lv_slider_get_value(slider));
      lv_label_set_text(label, buffer);
    }
  }
}

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

  tft.startWrite();
  tft.setAddrWindow(area->x1, area->y1, w, h);
  tft.pushColors(&color_p->full, w * h, true);
  tft.endWrite();

  lv_disp_flush_ready(disp);
}

uint16_t lastx = 0;
uint16_t lasty = 0;

/*Read the touchpad*/
bool my_input_read2(lv_indev_drv_t *drv, lv_indev_data_t *data)
{
  // Serial.println("#");
  TouchPoint touchPos = touchScreen.read();
  if (touchPos.touched)
  {
    Serial.println(String(touchPos.xPos) + ": " + String(touchPos.yPos));
    data->state = LV_INDEV_STATE_PR;
    data->point.x = touchPos.xPos;
    data->point.y = touchPos.yPos;
    lastx = touchPos.xPos;
    lasty = touchPos.yPos;
  }
  else
  {
    data->state = LV_INDEV_STATE_REL;
    data->point.x = lastx;
    data->point.y = lasty;
  }
  return false;
}

static void lv_tick_task(void)
{
  lv_tick_inc(portTICK_RATE_MS);
}

void setup()
{

  Serial.begin(115200);
  lv_init();
  // Setup tick hook for lv_tick_task
  esp_err_t err = esp_register_freertos_tick_hook((esp_freertos_tick_cb_t)lv_tick_task);

  // Enable TFT
  tft.begin();        /* TFT init */
  tft.setRotation(0); /* 1 Landscape orientation */

  // Enable Backlight
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, 1);

  // Start TouchScreen
  touchScreen.begin();

  // Display Buffer
  lv_disp_buf_init(&disp_buf, buf, NULL, LV_HOR_RES_MAX * 10);

  // Init Display
  lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  // disp_drv.hor_res = 480;
  // disp_drv.ver_res = 320;
  disp_drv.hor_res = 320;
  disp_drv.ver_res = 480;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.buffer = &disp_buf;
  lv_disp_drv_register(&disp_drv);

  // Init Touchscreen
  lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_input_read2;
  lv_indev_drv_register(&indev_drv);

  // Screen Object
  screenMain = lv_obj_create(NULL, NULL);

  // Text
  label = lv_label_create(screenMain, NULL);
  lv_label_set_long_mode(label, LV_LABEL_LONG_BREAK);
  lv_label_set_text(label, "Press a button");
  lv_label_set_align(label, LV_LABEL_ALIGN_CENTER);
  lv_obj_set_size(label, 240, 40);
  lv_obj_set_pos(label, 0, 30);

  // BUtton 1
  btn1 = lv_btn_create(screenMain, NULL);
  lv_obj_set_event_cb(btn1, event_handler_btn);
  lv_obj_set_width(btn1, 70);
  lv_obj_set_height(btn1, 32);
  lv_obj_set_pos(btn1, 12, 100);
  lv_obj_t *label1 = lv_label_create(btn1, NULL);
  lv_label_set_text(label1, "Hello");

  // Button 2
  btn2 = lv_btn_create(screenMain, NULL);
  lv_obj_set_event_cb(btn2, event_handler_btn);
  lv_obj_set_width(btn2, 70);
  lv_obj_set_height(btn2, 32);
  lv_obj_set_pos(btn2, 122, 100);
  lv_obj_t *label2 = lv_label_create(btn2, NULL);
  lv_label_set_text(label2, "Goodbye");

  // Button 3
  btn3 = lv_btn_create(screenMain, NULL);
  lv_obj_set_event_cb(btn3, event_handler_btn);
  lv_obj_set_width(btn3, 70);
  lv_obj_set_height(btn3, 32);
  lv_obj_set_pos(btn3, 232, 100);
  lv_obj_t *label3 = lv_label_create(btn3, NULL);
  lv_label_set_text(label3, "Riri");

  // slider
  slider = lv_slider_create(screenMain, NULL);
  lv_obj_set_event_cb(slider, event_handler_btn);
  lv_obj_set_width(slider, 250);
  lv_obj_set_height(slider, 32);
  lv_slider_set_range(slider, 0, 255);
  lv_slider_set_type(slider, LV_SLIDER_TYPE_NORMAL);
  lv_obj_set_pos(slider, 30, 200);
  lv_obj_t *label4 = lv_label_create(slider, NULL);
  lv_label_set_text(label4, "Slider");
  lv_obj_set_pos(label4, 100, 8);

  // switch
  sw = lv_switch_create(screenMain, NULL);
  lv_obj_set_pos(sw,20,250);
  lv_obj_set_width(sw, 70);
  lv_obj_set_height(sw, 32);

  // Screen load
  static lv_style_t blue_bg_style;
  lv_style_init(&blue_bg_style);
  lv_style_set_bg_color(&blue_bg_style, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x00, 0x00, 0x40));
  lv_obj_add_style(lv_scr_act(), LV_OBJ_PART_MAIN, &blue_bg_style);

  // lv_disp_set_bg_color(NULL,LV_COLOR_BLACK);// don't work ?
  // lv_scr_load_anim(screenMain,LV_SCR_LOAD_ANIM_MOVE_LEFT,5000,0,true);
  lv_scr_load(screenMain);
}

void loop()
{
  lv_task_handler();
  delay(1);
}
