/*************************************************************************

   DEMO CODE
   __________________

    [2025] - WAVELIGHTS - Markus E. Loeffler

*/

#ifdef __AVR_ATtiny85__
#define tinyblink 1
#endif

#ifdef tinyblink
// ATTiny85 ----------------------- ATTiny85
#define LED_PIN 1
#else
// Nano --------------------------- Nano
#define doprint 1
#define LED_PIN 12
#endif

#include <Adafruit_NeoPixel.h>

#define LED_COUNT 33  // LED COUNT
#define ANIMATION_FRAMES 15

#define ROTATION_SPEED 1850
#define FLASH_TIME 100
#define AFTER_GLOW 10

Adafruit_NeoPixel matrix(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);


//----------------------------------- setup

void setup() {

#ifdef doprint
  Serial.begin(115200);
#endif
  matrix.begin();
}

int16_t gStoryPtr = 0;
int16_t gColorPtr = 0;
//----------------------------------- loop
void loop() {

  int16_t spin = ((millis()) % ROTATION_SPEED) * (ANIMATION_FRAMES * FLASH_TIME) / ROTATION_SPEED;
  uint16_t ledIndex = 0;
  uint32_t color;
#ifndef tinyblink
  if (Serial.available() > 0) {
    int inByte = Serial.read();
    Serial.print("key: ");

    if (inByte == 'd') {
      gStoryPtr += 1;
      Serial.println(gStoryPtr);
    } else if (inByte == 'c') {
      gStoryPtr -= 1;
      Serial.println(gStoryPtr);
    } else if (inByte == 's') {
      gColorPtr += 1;
      Serial.println(gColorPtr);
    } else if (inByte == 'x') {
      gColorPtr -= 1;
      Serial.println(gColorPtr);
    }
  }
  spin = gStoryPtr * FLASH_TIME;
#endif
  matrix.clear();
  for (int16_t i = 0; i < ANIMATION_FRAMES; i++) {
    color = abs(i * FLASH_TIME - spin) < AFTER_GLOW ? 0x202010 : 0;

    matrix.setPixelColor(ledIndex, color);
    ++ledIndex;
    matrix.setPixelColor(ledIndex, color);
    ++ledIndex;

    // some LEDs are in the middle between 2 frames and need to stay off
    if ( i == 3 || i == 8 || i == 12)
      ledIndex++;
  }
  matrix.show();
}
