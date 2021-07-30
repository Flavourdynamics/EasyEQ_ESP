#ifndef EasyEQ_Config_h // Contains settings for Myriad components
#define EasyEQ_Config_h

/*
NBIS2SERIALPINS represents the number of pins used by the esp value, it ranges from 1->15
NUM_LEDS_PER_STRIP the length of your strip if you have different strips size put here the longest strip
for each pin you would be able to drive 8 virtuals pins
linked the 74hc595 with the strips
Q0/PIN 15 => VIRTUAL PIN 8
Q1/PIN 1  => VIRTUAL PIN 7
Q2/PIN 2  => VIRTUAL PIN 6
Q3/PIN 3  => VIRTUAL PIN 5
Q4/PIN 4  => VIRTUAL PIN 4
Q5/PIN 5  => VIRTUAL PIN 3
Q6/PIN 6  => VIRTUAL PIN 2
Q7/PIN 7  => VIRTUAL PIN 1
*/
#define ESP32_VIRTUAL_DRIVER true //To enable virtual pin driver for esp32
#define ESP_VIRTUAL_DRIVER_8 1    //to use the 8:1 ratio
#define NBIS2SERIALPINS 4         // you will be able to drive up to 32 strips the number of strips will be always a multiple of 8
#define NUM_LEDS_PER_STRIP 60     //the length of your strip if you have different strips size put here the longuest strip
#define FASTLED_ALLOW_INTERRUPTS 1

#include "FastLED.h"
#define CLOCK_PIN 25 //for a reason I don't know, the CLOCK_PIN needs to be >=16
#define LATCH_PIN 27

#define NUM_STRIPS 28
#define NUM_LEDS NUM_LEDS_PER_STRIP * NUM_STRIPS

int start;

int Pins[NBIS2SERIALPINS]={18,19,23,26}; //example pins

#define LEDtilewidth 4 // How much width each input controls
#define LEDtileheight 60 // how high each strip is
#define LEDtilehorz 7 // number of matrices arranged horizontally
#define LEDtilevert 1  // how many tiles stacked vertically
#define LEDstrips (LEDtilewidth*LEDtilehorz)  // How many LEDs across the array is
#define LEDper (LEDtileheight*LEDtilevert)    // How many LEDs are on each vertical strip
#define LEDsegm (LEDtilewidth*LEDper)         // The number of LEDs on each segment connected to the
#define LEDtotal (LEDstrips*LEDper)
#define NUMleds LEDtotal
uint16_t LEDhalfstrips, LEDhalfper;
// Compatibility for NeoMatrix
#define mw LEDstrips
#define mh LEDper
#define NUMMATRIX LEDtotal
// Compatibility for some other demos
#define MATRIX_WIDTH LEDstrips
#define MATRIX_HEIGHT LEDper

// Create two LED array objects for crossfading
/*
cLEDMatrix<LEDtilewidth, LEDtileheight, VERTICAL_MATRIX, LEDtilehorz, LEDtilevert , VERTICAL_BLOCKS> ledmatrix;
CRGB *leds = ledmatrix[0];
cLEDMatrix<LEDtilewidth, LEDtileheight, VERTICAL_MATRIX, LEDtilehorz, LEDtilevert , VERTICAL_BLOCKS> ledmatrix2;
CRGB *leds2 = ledmatrix2[0];
*/
CRGB leds[LEDtotal];
CRGB leds2[LEDtotal];
/*
FastLED_NeoMatrix *matrix = new FastLED_NeoMatrix(leds, LEDtilewidth, LEDtileheight, LEDtilehorz, LEDtilevert,
  NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE + NEO_TILE_TOP + NEO_TILE_LEFT + NEO_TILE_PROGRESSIVE);
*/

// LED Settings
#define LEDtype WS2813
#define LEDcorr TypicalSMD5050
#define LEDdither 255     //try 0 to reduce flickering
bool LEDonoff = true;
uint8_t LEDtargbright;
uint8_t LEDcurbright;
uint16_t LEDamps = 3500;

// Fader
#define deffade 5         // Default fade amt
uint8_t currfade = deffade; // Initialize variable fader
uint8_t targfade;           // Value for storing saving 

// Palette
CRGBPalette16 currentPalette;   // This is the palette used by patterns
CRGBPalette16 targetPalette;    // This palette is used to store a target palette for blending
bool palshuff = false;          // Don't shuffle by default
bool palmatch = true;           // Match by default
uint8_t palnum;             // change back to 0
uint8_t blendspeed = 35;        // How fast the palette blends (higher is faster)
uint8_t hue[2];                 // Hue value as an array to be used during crossfading

// Pattern variables, these are arrays to handle two independent values during crossfading
uint8_t patternum;    // For keeping track of what patterns are running. Default = 0
uint8_t oldpattern;       // For storing what pattern we're fading away from on swap
uint8_t crossct = 255;   // This may need to be 16 bits, or could be trimmed to 8 maybe
int16_t rowcount[2];          // For patterns that roll out
int16_t colcount[2];
int16_t count[2];
bool patshuffle = false;
uint16_t noise[30][2];
uint16_t timer;
uint8_t stars[LEDstrips]; // Deprecated, probably
uint8_t beat = 144;
uint8_t beatmod = LEDper/60; // to ensure some patterns don't run too fast

//State
uint8_t STATEBTinterval = 200;
uint16_t STATEloopinterval = 25;
uint16_t STATEshuffleinterval = 10;
uint16_t STATEpalshuffleinterval = 10;

//Pattern Key
//typedef void (*SimplePatternList[])();
bool newP; // For indicating if the pattern is new
using pattern_func = void (*)(bool newpatbool);
typedef struct {
  pattern_func Pattern;
  const String Name;
} NamedPattern;
//uint8_t PATTERNnum = 0; // Index number of which pattern is current
//#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

// Core 0 Setup
//TaskHandle_t Core0;

#endif