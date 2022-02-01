#include <Arduino.h>
#include "LXESP32DMX.h"
#include "LXESP32DMX1.h"

#include "init.h"
#include "remote.h"
#include "fonction.h"
#include "dmx.h"

// 35(i2s_out) 26 (i2s_in) 25(i2s_lock) 5(i2sc) 0(i2s_mc) 23 22 13 15 2 4 33 32 27 14 12 21 34 
#define DMX_SERIAL_INPUT_PIN 26
#define DMX_DIRECTION_INPUT_PIN 25
#define DMX_SERIAL_OUTPUT_PIN 35

static void lv_tick_task(void)
{
  lv_tick_inc(portTICK_RATE_MS);
}

void setup()
{

  Serial.begin(115200);

  // SET INPUT RX2
  // pinMode(DMX_SERIAL_INPUT_PIN, INPUT);
  ESP32DMX.setDirectionPin(DMX_DIRECTION_INPUT_PIN);
  ESP32DMX1.startInput(DMX_SERIAL_INPUT_PIN);

  // SET OUTPUT TX1
  pinMode(DMX_SERIAL_OUTPUT_PIN, OUTPUT);
  ESP32DMX.startOutput(DMX_SERIAL_OUTPUT_PIN);

  // lv_lib
  lv_init();
  // Setup tick hook for lv_tick_task
  esp_err_t err = esp_register_freertos_tick_hook((esp_freertos_tick_cb_t)lv_tick_task);

  // Enable TFT & Tactile
  tft_init();

  // varaiable
  init_variable();

  // lv_keypad_encoder();
  menu_create();
}

void loop()
{
  lv_task_handler();
  delay(1);

  fonction();
  // copyDMXToOutput();
}
