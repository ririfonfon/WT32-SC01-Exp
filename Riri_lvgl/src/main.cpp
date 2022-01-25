#include <Arduino.h>

#include "init.h"
// #include "keypad.h"
#include "remote.h"

char action[256];

static void lv_tick_task(void)
{
  lv_tick_inc(portTICK_RATE_MS);
}

void do_oops() 
{
  Serial.println("oops");
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
  menu_create();
}

void loop()
{
  lv_task_handler();
  delay(1);

  getAction(action);
  if (strcmp(action, "") != 0) {

    Serial.println(action);

    if (strcmp(action, "Please") == 0)          Serial.println("\t->Thanks!");
    if (strcmp(action, LV_SYMBOL_RIGHT) == 0)   Serial.println("\t->Right");
    if (strcmp(action, LV_SYMBOL_LEFT) == 0)    Serial.println("\t->Left");
  }

}
