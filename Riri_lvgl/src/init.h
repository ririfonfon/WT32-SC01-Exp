#ifndef init_h
#define init_h


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

static void tft_init()
{
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
}

#endif
