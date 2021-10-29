#include <Arduino.h>
/*

 Example sketch for TFT_eSPI library.

 No fonts are needed.
 
 Draws a 3d rotating cube on the TFT screen.
 
 Original code was found at http://forum.freetronics.com/viewtopic.php?f=37&t=5495
 
 */
#include <Wire.h>
#include "FT62XXTouchScreen.h"

// 

#define DISPLAY_WIDTH  480
#define DISPLAY_HEIGHT 320
#define BLACK 0x0000
#define WHITE 0xFFFF

#include <SPI.h>

#include <TFT_eSPI.h> // Hardware-specific library

TFT_eSPI tft = TFT_eSPI();       // Invoke custom library

FT62XXTouchScreen touchScreen = FT62XXTouchScreen(DISPLAY_HEIGHT, PIN_SDA, PIN_SCL);


#include <structure.h>
#include <fonction.h>

/***********************************************************************************************************************************/

void setup() {
  Serial.begin(115200);
  tft.init();

  // Backlight hack...
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, 128);

  touchScreen.begin();

  h = tft.height();
  w = tft.width();

  tft.setRotation(1);

  tft.fillScreen(TFT_BLACK);

  cube();

  fact = 180 / 3.14159259; // conversion from degrees to radians.

  Xoff = 240; // Position the center of the 3d conversion space into the center of the TFT screen.
  Yoff = 160;
  Zoff = 550; // Z offset in 3D space (smaller = closer and bigger rendering)
}

/***********************************************************************************************************************************/
void loop() {

  TouchPoint touchPos = touchScreen.read();

  if (touchPos.touched) {
    Serial.printf("X: %d, Y: %d\n", touchPos.xPos, touchPos.yPos);
    tft.drawCircle(touchPos.xPos, touchPos.yPos
    , 10, TFT_SILVER);
  }

  // Rotate around x and y axes in 1 degree increments
  Xan++;
  Yan++;

  Yan = Yan % 360;
  Xan = Xan % 360; // prevents overflow.

  SetVars(); //sets up the global vars to do the 3D conversion.

  // Zoom in and out on Z axis within limits
  // the cube intersects with the screen for values < 160
  Zoff += inc; 
  if (Zoff > 500) inc = -1;     // Switch to zoom in
  else if (Zoff < 160) inc = 1; // Switch to zoom out

  for (int i = 0; i < LinestoRender ; i++)
  {
    ORender[i] = Render[i]; // stores the old line segment so we can delete it later.
    ProcessLine(&Render[i], Lines[i]); // converts the 3d line segments to 2d.
  }
  RenderImage(); // go draw it!

  delay(20); // Delay to reduce loop rate (reduces flicker caused by aliasing with TFT screen refresh rate)
}

/***********************************************************************************************************************************/


