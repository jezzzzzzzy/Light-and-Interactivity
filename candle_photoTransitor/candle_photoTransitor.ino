

#define lightSensor A2
int sensorReading;

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN    2
#define NUMPIXELS  7

Adafruit_NeoPixel strip(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


int change = 1;
int currentLevel = 125;
byte levelTable[256];

void setup() {

  Serial.begin(9600);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  fillLevelTable();



}

void loop() {

  int LightLevel = analogRead(lightSensor);


  uint32_t candle = strip.Color(255, 150,0 );
  Serial.print("LightLevel:" );
  Serial.print(LightLevel  );
   Serial.println();


  if (LightLevel <= 80) {
    if (currentLevel <= 120 || currentLevel >= 220) {
      change = -change;
    }
    currentLevel += change;


    //PWM output the result:
    strip.setBrightness( levelTable[currentLevel]);
    strip.fill(candle, 0, 7);
    strip.show();
    
Serial.println("levelTable[currentLevel]:" );
    Serial.print(levelTable[currentLevel]);
    Serial.println();

  } else {
    strip.setBrightness(0);
    strip.fill(candle, 0, 7);
    strip.show();
   
  }
   delay(20);  
}

void fillLevelTable() {
  // set the range of values:
  float maxValue = 255;

  // iterate over the array and calculate the right value for it:
  for (int l = 0; l <= maxValue; l++) {

    // map input to a 0-179 range:
    float angle = map(l, 0, maxValue, 0, 179);
    /* here's the explanation of the calulation:
      // convert to radians:
      float result = angle * PI/180;
      // now add PI/2 to offset by 90 degrees:
      result = result + PI/2;
      // get the sine of that:
      result = sin(result);
      // now you have -1 to 1. Add 1 to get 0 to 2:
      result = result + 1;
      // multiply to get 0-255:
      result = result * 127.5;
    */
    //here it all is in one line:
    float lightLevel = (sin((angle * PI / 180) + PI / 2) + 1) * 127.5;
    levelTable[l] = lightLevel;
  }
}
