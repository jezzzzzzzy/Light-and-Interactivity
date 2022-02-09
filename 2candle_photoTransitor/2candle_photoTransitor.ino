

#define lightSensor A2
int sensorReading;

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN    2
#define NUMPIXELS  7

Adafruit_NeoPixel strip(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int currentLevel;
int change = 1;

byte levelTable[256];

void setup() {

  Serial.begin(9600);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  


}

void loop() {

  int LightLevel = analogRead(lightSensor);


  uint32_t candle = strip.Color(255, 150,0 );
  Serial.print("LightLevel:" );
  Serial.print(LightLevel  );
   Serial.println();


  if (LightLevel <=1) {
    
    


    //PWM output the result:
    strip.setBrightness( random(180,230));
    strip.fill(candle, 0, 7);
    strip.show();
    
Serial.println("currentLevel");
    Serial.print(currentLevel);
    Serial.println();

  } else {
    strip.setBrightness(0);
    strip.fill(candle, 0, 7);
    strip.show();
   
  }
   delay(10);  
}
