#include <Arduino.h>
#include <EasyEQ_Config.h>
#include <Myriad_EQ.h>
Myriad_EQ EQ;

uint16_t XY(byte x, byte y) {
  uint16_t LEDaddress = x * LEDper + y;
  return LEDaddress;
}

void red(){
  for(int i = 0; i < LEDtotal/4; i++){
    hue[1]++;
    leds2[i] = CRGB(255,0,0);
  }
}

void green(){
  for(int i = 0; i < LEDtotal/4; i++){
    leds3[i] = CRGB(0,255,0);
  }
}

void blue(){
  for(int i = 0; i < LEDtotal/4; i++){
    leds4[i] = CRGB(0,0,255);
  }
}

void blackout() {
  for ( int i = 0; i < LEDtotal; i++) {
    leds[i] = CRGB(0, 0, 0);
    //leds2[i] = CRGB(0,0,0);
  }
}

void basic(){
  EVERY_N_MILLIS(4){
    blackout();
    for(int band = 0; band < EQbins; band++){
      for(int leng = 0; leng < EQ.EQscaled[band]; leng++){ // Display as 00 11 22 33 44 55 66 66 55 44 33 22 11 00  CHSV(hue+leng*5-s*7, 255, 255); EQscaled[band]
        uint8_t ahue = hue[1] +leng*5 +band*5;
        leds[XY(LEDstrips/2+band, leng)] = CHSV(ahue+leng*5, 255, 255);
        leds[XY(LEDstrips/2-1-band, leng)] = CHSV(ahue+leng*5, 255, 255);
      }
    }
    FastLED.show();
  }
  
}
void quadplexor(){
  blackout();
  for(int band = 0; band < EQbins; band++){
    byte z = map(EQ.EQscaled[band], 0, LEDper, 0, LEDper/2);
    for(int leng = 0; leng < z; leng++){                // Display as 00 11 22 33 44 55 66 66 55 44 33 22 11 00  CHSV(hue+leng*5-s*7, 255, 255); EQscaled[band]
      leds[XY(LEDstrips/2 -1  -band,   LEDper/2    -2   -leng)] = CHSV(hue[1] + band*5 + leng*5, 255, 255);  // Top left
      leds[XY(LEDstrips/2     +band,   LEDper/2    -2   -leng)] = CHSV(hue[1] + band*5 + leng*5, 255, 255);    // Top right
      leds[XY(LEDstrips/2 -1  -band,   LEDper/2    -1   +leng)] = CHSV(hue[1] + band*5 + leng*5, 255, 255);  // Bottom left
      leds[XY(LEDstrips/2     +band,   LEDper/2    -1   +leng)] = CHSV(hue[1] + band*5 + leng*5, 255, 255);    // Bottom right
    }
    if(z > 0){ //peaks
      leds[XY(LEDstrips/2 -1  -band,   LEDper/2    -1   -z )] = CHSV(255, 0, 255);  // Top left
      leds[XY(LEDstrips/2     +band,   LEDper/2    -1   -z )] = CHSV(255, 0, 255);    // Top right
      leds[XY(LEDstrips/2 -1  -band,   LEDper/2    -2   +z )] = CHSV(255, 0, 255);  // Bottom left
      leds[XY(LEDstrips/2     +band,   LEDper/2    -2   +z )] = CHSV(255, 0, 255);    // Bottom right
    }
  }
  EVERY_N_MILLIS(20){
    hue[1]++;
  }
  FastLED.show();
}

void setup() {
  Serial.begin(115200);
  FastLED.addLeds<VIRTUAL_DRIVER,Pins,CLOCK_PIN, LATCH_PIN>(leds,NUM_LEDS_PER_STRIP);
  FastLED.setBrightness(25);
  FastLED.clear(true);
}

void loop() {
  EQ.proc();
  //basic();
  quadplexor();
  EVERY_N_MILLIS(20){
    hue[1]++;
  }
}