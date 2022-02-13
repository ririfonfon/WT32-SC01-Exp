#include <Arduino.h>
#include <LXESP32DMX.h>
#include "esp_task_wdt.h"
#include "ririlvgl_LXESP32DMX1.h"

bool update = true;
int16_t output[513];

#include "init.h"
#include "remote.h"
#include "fonction.h"
// #include "dmx.h"

// 35(i2s_out) 26 (i2s_in) 25(i2s_lock) 5(i2sc) 0(i2s_mc) 23 22 13 15 2 4 33 32 27 14 12 21 34

// input output no work with screen 15 22 21
// input output no work 13
// dir no work 34

#define DMX_SERIAL_INPUT_PIN 12
#define DMX_SERIAL_OUTPUT_PIN 23
#define DMX_DIRECTION 32

#define DMX1_SERIAL_INPUT_PIN 2 // 2 work with screen and lxespdmx
#define DMX1_SERIAL_OUTPUT_PIN 4
#define DMX1_DIRECTION 33

// the addresses of the slots to observe
int test_slotA = 1;
int test_slotB = 2;
int test_slotC = 3;

// the levels of those slots
uint8_t test_levelA = 0;
uint8_t test_levelB = 0;
uint8_t test_levelC = 0;

// // pins for PWM output
// uint8_t led_pinA = 26;
// uint8_t led_pinB = 33;
// uint8_t led_pinC = 25;

// ledc channels (set to zero to disable)
uint8_t led_channelA = 1;
uint8_t led_channelB = 2;
uint8_t led_channelC = 3;

uint8_t dataChanged = 1;


/************************************************************************

  callback for when DMX frame is received
  Note:  called from receive task

  Checks to see if the level of the designated slot has changed
  and sets the dataChanged flag.

  Processing in this callback should be minimal.

  Instead, use a flag and do more intense processing in a lower priority task.

*************************************************************************/

void receiveCallback(int slots)
{
  if (slots)
  {
    xSemaphoreTake(ESP32DMX.lxDataLock, portMAX_DELAY);
    if (test_levelA != ESP32DMX.getSlot(test_slotA))
    {
      test_levelA = ESP32DMX.getSlot(test_slotA);
      dataChanged = 1;
    }
    if (test_levelB != ESP32DMX.getSlot(test_slotB))
    {
      test_levelB = ESP32DMX.getSlot(test_slotB);
      dataChanged = 1;
    }
    if (test_levelC != ESP32DMX.getSlot(test_slotC))
    {
      test_levelC = ESP32DMX.getSlot(test_slotC);
      dataChanged = 1;
    }
    xSemaphoreGive(ESP32DMX.lxDataLock);
  }
}

static void lv_tick_task(void)
{
  lv_tick_inc(portTICK_RATE_MS);
}

void setup()
{
  Serial.begin(115200);
  Serial.print("setup");

  // DISARM RX
  pinMode(DMX_SERIAL_INPUT_PIN, OUTPUT);
  pinMode(DMX1_SERIAL_INPUT_PIN, OUTPUT);

  Serial.print(", set callback");
  ESP32DMX.setDataReceivedCallback(receiveCallback);

  digitalWrite(DMX_SERIAL_INPUT_PIN, LOW);
  digitalWrite(DMX1_SERIAL_INPUT_PIN, LOW);
  delay(200);

  // lv_lib
  lv_init();
  // Setup tick hook for lv_tick_task
  esp_err_t err = esp_register_freertos_tick_hook((esp_freertos_tick_cb_t)lv_tick_task);

  // Enable TFT & Tactile
  tft_init();

  // lv_keypad_encoder();
  menu_create();

  // varaiable
  init_variable();

  // SET INPUT RX2
  ESP32DMX1.setDirectionPin(DMX1_DIRECTION);
  pinMode(DMX1_SERIAL_INPUT_PIN, INPUT);
  pinMode(DMX1_SERIAL_OUTPUT_PIN, OUTPUT);
  delay(100);
  ESP32DMX1.startOutput(DMX1_SERIAL_OUTPUT_PIN);
  // ESP32DMX1.startInput(DMX1_SERIAL_INPUT_PIN);

  // SET OUTPUT TX1
  ESP32DMX.setDirectionPin(DMX_DIRECTION);
  pinMode(DMX_SERIAL_INPUT_PIN, INPUT);
  pinMode(DMX_SERIAL_OUTPUT_PIN, OUTPUT);
  delay(100);
  // ESP32DMX.startOutput(DMX_SERIAL_OUTPUT_PIN);
  ESP32DMX.startInput(DMX_SERIAL_INPUT_PIN);

  Serial.println(", setup complete.");
}

void loop()
{
  lv_task_handler();
  delay(1);

  if (lv_tabview_get_tab_act(tv) == 0)
  {
  fonction();
  }
  else if (lv_tabview_get_tab_act(tv) == 1)
  {
    if(update)
    {
      // Serial.print(" => if(update) ");
      // output_update();
      // Serial.print(" => output_update(); ");
      // update = false;
      // Serial.print(" => false ");
    }
  }


  if (dataChanged)
  {
    dataChanged = 0;
    Serial.print(test_slotA);
    Serial.print(" => ");
    Serial.println(test_levelA);

    Serial.print(test_slotB);
    Serial.print(" => ");
    Serial.println(test_levelB);

    Serial.print(test_slotC);
    Serial.print(" => ");
    Serial.println(test_levelC);
  }
  else
  {
    delay(25);
  }
}
