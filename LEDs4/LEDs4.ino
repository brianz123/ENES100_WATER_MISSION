#include <FastLED.h>

#define LED_PIN 5
#define COLOR_ORDER GRB
#define CHIPSET     WS2811
#define NUM_LEDS    40

#define BRIGHTNESS  255
#define FRAMES_PER_SECOND 60

bool gReverseDirection = false;

CRGB leds[NUM_LEDS];

void setup() {
  delay(3000); // sanity delay
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness( BRIGHTNESS );

}

void loop() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
    FastLED.show();
    delay(20);
    leds[i] = CRGB::Red;
    FastLED.show();

  }

}
