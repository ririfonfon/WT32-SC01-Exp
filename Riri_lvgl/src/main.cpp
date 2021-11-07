#include <Arduino.h>

#include "init.h"
#include "keypad.h"
#include "demo.h"

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

  // Enable TFT & Tactile
  tft_init();

  // lv_keypad_encoder();
  demo_create();
}

void loop()
{
  lv_task_handler();
  delay(1);
}
