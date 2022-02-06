 /*neopixel jewel fade in to turn on & fade out to turn off 
  contolled by press the button
  fade curves :CIE
*/

int currentLevel1 = 1; // current light level
int change = 1;       // change each time you fade
byte cie1931[256];    // pre-calculated PWM levels

const int buttonPin = 2;
const int ledPin =  3;
int buttonState = 0;
int flag =1;



#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN    6
#define NUMPIXELS  7

Adafruit_NeoPixel strip(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//first” is the index of the first pixel to fill
// “count” is the number of pixels to fill. Must be a positive value.
int first = 0;
int count = 7;

void setup() {
  //Input or output?

  pinMode(buttonPin, INPUT);
  

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  // pre-calculate the PWM levels from CIE1931 formulas:
  fillCIETable();
  Serial.begin(9600);
}

void loop() {

    uint32_t fire = strip.Color(255, 0, 255);
  uint32_t white = strip.Color(255, 255, 255);
  buttonState = digitalRead(buttonPin);

  if ( flag == 0) {
     if (currentLevel1>0) {
      currentLevel1 -= change;
     strip.setBrightness(cie1931[currentLevel1]);

    strip.fill(white, 0, 7);
    strip.show();
      delay(10);
      Serial.println(cie1931[currentLevel1]);
    }
  } else {
     if (currentLevel1 <255) {
      currentLevel1 += change;
      strip.setBrightness(cie1931[currentLevel1]);
    strip.fill(white, 0, 7);
    strip.show();
      delay(10);
      Serial.println(cie1931[currentLevel1]);
    }
  }

  //If button pressed...
  if (buttonState == HIGH) {
    //...ones, turn led on!
    //...twice, turn led off!
    flag = !flag; //change flag variable
  }
  

  delay(20); //Small delay
//Serial.print("flag");
//Serial.println(flag);
//Serial.print("buttonState");
//  Serial.println(buttonState);
}



void fillCIETable() {
  /*
    For CIE, the following formulas have  Y as luminance, and
    Yn is the luminance of a white reference (basically, max luminance).
    This assumes a perceived lightness value L* between 0 and 100,
    and  a luminance value Y of 0-1.0.
    if L* > 8:  Y = ((L* + 16) / 116)^3 * Yn
    if L* <= 8: Y = L* *903.3 * Yn
  */
  // set the range of values:
  float maxValue = 255;
  // scaling factor to convert from 0-100 to 0-maxValue:
  float scalingFactor = 100 / maxValue;
  // luminance value:
  float Y = 0.0;

  // iterate over the array and calculate the right value for it:
  for (int l = 0; l <= maxValue; l++) {
    // you need to scale L from a 0-255 range to a 0-100 range:
    float lScaled = float(l) * scalingFactor;
    if ( lScaled <= 8 ) {
      Y = (lScaled / 903.3);
    } else {
      float foo = (lScaled + 16) / 116.0;
      Y = pow(foo, 3);
    }
    // multiply to get 0-maxValue, and fill in the table:
    cie1931[l] = Y * maxValue;
  }
}
