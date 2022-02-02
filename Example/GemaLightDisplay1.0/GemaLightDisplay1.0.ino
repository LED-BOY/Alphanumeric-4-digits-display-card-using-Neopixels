/*
GemaLight Display/Clock RTC DS1307 code free to edit and use in any project
to use with any arduino compatible boards.
14/9/2021
*/
#include <Adafruit_NeoPixel.h>
#include "characters.h"

#define NUM_LEDS 54// number of led used
#define BUTTON 4 // button pin ATtiny 85

//variables

uint8_t color = 1; // stores color of the display
uint16_t arrayNumberValue[1];
uint16_t buttonPressCounter = 0;// number of button presses
unsigned long buttonPressTimeStamp;// how much time the button is pressed


Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, 1, NEO_GRB + NEO_KHZ800);

void setup() {
  delay(360);

  pinMode(BUTTON, INPUT_PULLUP);
  strip.begin();
  strip.setBrightness(50);

  while ((millis() - buttonPressTimeStamp) < 1400) { // greeting message
    showSegment(0, letterG);
    showSegment(1, letterE);
    showSegment(2, letterM);
    showSegment(3, letterA);
  }
  while ((millis() - buttonPressTimeStamp) >= 1400 && (millis() - buttonPressTimeStamp) < 2800) {
    showSegment(0, letterL);
    showSegment(1, letterG);
    showSegment(2, letterH);
    showSegment(3, letterT);
  }
  strip.clear();
  buttonPressTimeStamp = millis();
}

void loop() {
  if (digitalRead(BUTTON) == LOW) {
    buttonPressTimeStamp = millis();
    if (buttonPressCounter <= 9999) {// display the button pushes up to 9999
      buttonPressCounter++;
    } else {
      buttonPressCounter = 0;
    }
    while ((millis() - buttonPressTimeStamp) < 700) {// debounce every 700 millis
    }
  }
  showAllSegments(buttonPressCounter);
}

void showSegment (uint8_t digitNumber, uint8_t arrayName[] ) {// draws on digit form 0 to 3 taking values from array in characters
  //digit number from 0 left to 3 right
  uint8_t firstLed = 0;
  uint8_t lastLed = 0;
  uint8_t led = 0;
  uint8_t ledValue = 0;;

  switch (digitNumber) {// led mapping corresponding to each digit from left to right
    case 0:
      firstLed = 0;// digit 0
      lastLed = 12;
      break;
    case 1:
      firstLed = 13;// digit 1
      lastLed = 25;
      break;
    case 2:
      firstLed = 26;// digit 2
      lastLed = 38;
      break;
    case 3:
      firstLed = 39;//digit 3
      lastLed = 51;
      break;
    default:
      firstLed = 0;
      lastLed = 12;
      break;
  }

  for (uint8_t x = firstLed; x <= lastLed ; x++) {
    ledValue = pgm_read_byte_near (arrayName + led);// reads the arrya values from progmem
    switch (color) {
      case 1:
        strip.setPixelColor(x, ledValue, 0, 0);
        break;
      case 2:
        strip.setPixelColor(x, 0, ledValue, 0);
        break;
      case 3:
        strip.setPixelColor(x, 0, 0, ledValue);
        break;
      case 4:
        strip.setPixelColor(x, ledValue, ledValue, ledValue);
        break;
    }
    led++;
  }
  strip.show();
}

void showTwoSegments (uint8_t firstDigit, uint8_t valueByte) { // this function draws two segments of the display at once
  uint8_t valueUnits = valueByte;
  if (valueByte <= 99 && firstDigit < 3) {

    if (valueByte < 10) {// some math to quite the 0 from the left
      showSegment((firstDigit), simbolNull);
      arrayNumberValue[0] = pgm_read_word_near(number + valueByte);
      showSegment((firstDigit + 1), arrayNumberValue[0]);
    } else {
      valueByte /= 10;
      arrayNumberValue[0] = pgm_read_word_near(number + valueByte);
      showSegment(firstDigit, arrayNumberValue[0]);
      valueByte *= 10;

      for (uint8_t x = 0; x < valueByte ; x++) {
        valueUnits--;
      }

      arrayNumberValue[0] = pgm_read_word_near(number + valueUnits);
      showSegment((firstDigit + 1), arrayNumberValue[0]);
    }
  }
}

void showAllSegments (uint16_t valueShort) {// draws all 4 digits at once usefull to display numbers
  uint16_t valueDecimals = valueShort;
  if (valueShort <= 9999) {

    if (valueShort < 100) { // function to draw units in digit 3, decimals in digit 2, hundredths in digit 1 and  thousand in digit 0
      showSegment(0, simbolNull);
      showSegment(1, simbolNull);
      showTwoSegments(2, valueShort);
    }

    if (valueShort >= 100 && valueShort < 9999) {
      valueShort /= 100;
      showTwoSegments(0, valueShort);
      valueShort *= 100;

      for (uint16_t x = 0; x < valueShort ; x++) {
        valueDecimals--;
      }
      showTwoSegments(2, valueDecimals);
    }
  }
}
