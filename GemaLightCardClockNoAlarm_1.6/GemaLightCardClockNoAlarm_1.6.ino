/*
  GemaLight Display/Clock RTC DS1307 code free to edit and use in any project
  to use with any arduino compatible boards.
  24hs time format.
  14/9/2021
*/

#include <Adafruit_NeoPixel.h>
#include <avr/eeprom.h>
#include <RTClib.h>
#include "characters.h"
#include <avr/sleep.h>
#include "sleep.h"

#define NUM_LEDS 54 // number of NeoPixels
#define BUTTON 4 // button pin

//variables


uint8_t hours = 0; //keep the hours to display
uint8_t minutes = 0;//keep the minutes to display
uint8_t color = 1; // store color value Red, blue, green, white
uint8_t brightLevel = 0;
uint8_t lastMinute = 60; // used to update the digits only once per minute
uint16_t arrayNumberValue[1]; // stores one array pointer to array number in characters.h
bool displayOn = true; // if display is on or off
bool sqwOn = false; // SQW pin of the RTC ds1307
unsigned long buttonPressTimeStamp; // button press time

RTC_DS1307 rtc;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, 1, NEO_GRB + NEO_KHZ800);

void setup() {
  delay(360);

  pinMode(BUTTON, INPUT_PULLUP); // use internal pullup of attiny 85
  //Write to EEPROM
  if (eeprom_read_byte((uint8_t*)511) != 131) { // prevents excessive flash write and default values if first time used or no colors are choose
    eeprom_write_byte((uint8_t*)511, 131);
    eeprom_write_byte((uint8_t*)2, 1);//color
    eeprom_write_byte((uint8_t*)3, 5);//brightness level
    eeprom_write_byte((uint8_t*)4, true);//Display mode
    eeprom_write_byte((uint8_t*)5, false);//RTC SQW Pin Mode
  };

  strip.begin();
  brightLevel = eeprom_read_byte((uint8_t*)3); // read brightness from eeprom
  strip.setBrightness(brightLevel * 4);// brightness select from 0 to 255

  while (!rtc.begin()) { // wait RTC to begin
    strip.setPixelColor(52, 100, 0, 0);
    strip.setPixelColor(53, 100, 0, 0);
    strip.show();
    rtc.begin();
    delay(500);
  }

  if (rtc.readnvram(0) != 0x01) {// if there isn´t a 1 in rtc at adress 0 the rtc wasn´t initialized
    while ((millis() - buttonPressTimeStamp) < 2000) { // display batt 0% menssage
      drawDigits(0, letterB);
      drawDigits(1, letterA);
      drawDigits(2, letterT);
      drawDigits(3, letterT);
    }
    strip.clear();
    while ((millis() - buttonPressTimeStamp) >= 2000 && (millis() - buttonPressTimeStamp) < 4000) {
      drawDigits(0, number0);
      drawDigits(1, simbolPercent);
    }
    //This line sets the RTC with an explicit date & time.
    rtc.adjust(DateTime(0, 0, 0, 0, 0, 0));
    rtc.writenvram(0, 0x01); // write a 1 to RTC SRAM adress 8 to know the rtc is already initialized
    rtc.writeSqwPinMode(DS1307_OFF);// Rtc SQW pin off
    buttonPressTimeStamp = millis();
  }
  //read from EEPROM
  color = eeprom_read_byte((uint8_t*)2); //read stored color
  displayOn = eeprom_read_byte((uint8_t*)4);// read display mode
  sqwOn = eeprom_read_byte((uint8_t*)5);// read alarmMode

  while ((millis() - buttonPressTimeStamp) < 1500) { // Greeting message
    drawDigits(0, letterG);
    drawDigits(1, letterE);
    drawDigits(2, letterM);
    drawDigits(3, letterA);
  }
  while ((millis() - buttonPressTimeStamp) >= 1500 && (millis() - buttonPressTimeStamp) < 3000) {
    drawDigits(0, letterL);
    drawDigits(1, letterG);
    drawDigits(2, letterH);
    drawDigits(3, letterT);
  }
  strip.clear();
  buttonPressTimeStamp = millis();


  if (digitalRead(BUTTON) == LOW) { // if the button is pushed while connecting the device alternates SQW pin
    sqwOn = !sqwOn;
    while ((millis() - buttonPressTimeStamp) < 1500) {
      drawDigits(0, letterS);
      drawDigits(1, letterQ);
      if (sqwOn) {
        drawDigits(2, number1);
        drawDigits(3, letterH);
        rtc.writeSqwPinMode(DS1307_SquareWave1HZ);// Rtc SQW pin 1Hz pwm
        eeprom_write_byte((uint8_t*)5, sqwOn);
      }
      if (!sqwOn) {
        drawDigits(2, letterN);
        drawDigits(3, letterO);
        rtc.writeSqwPinMode(DS1307_OFF);// Rtc SQW pin off
        eeprom_write_byte((uint8_t*)5, sqwOn);
      }
    }
    strip.clear();
    buttonPressTimeStamp = millis();
  }
}

void loop() {

  if (digitalRead(BUTTON) == LOW) { // checks if the button is pressed to enter options or turn on display if the display off option is selected
    buttonPressTimeStamp = millis();
    if (!displayOn) {
      readTimeBlinkColon();
      showTime(2, minutes);
      showTime(0, hours);
      while (digitalRead(BUTTON) == LOW) {// if the button is pressed for 5seg or longer the display is turned on indefinitely
        while ((millis() - buttonPressTimeStamp) > 5000 && (millis() - buttonPressTimeStamp) < 7000) {
          displayOn = true;
          eeprom_write_byte((uint8_t*)4, true);//Display mode
          drawDigits(0, letterD);
          drawDigits(1, letterI);
          drawDigits(2, letterO);
          drawDigits(3, letterN);
        }
      }
      if (displayOn) {
        showTime(2, minutes);
        showTime(0, hours);
      } else {
        strip.clear();
        strip.show();
        sleep();
      }
    } else {
      lastMinute = 60; // lastMinute needs to be set to 60 to force time update
      strip.clear();
      setOptions();
    }
  }

  readTimeBlinkColon();

  if (minutes != lastMinute) { // time update occurs only once every minute
    lastMinute = minutes;
    if (displayOn) {
      showTime(2, minutes);
      showTime(0, hours);
    }
  }
}
// OPTIONS MENU
void setOptions() {// Al options are time based using millis (you need to be careful to time each function accordingly or the code will be unstable.
  while ((millis() - buttonPressTimeStamp) < 4000) {// each option remains for 4 second using millis function.
    drawDigits(0, letterC); // color selection
    drawDigits(1, letterO);
    showTime(2, color);
    if (digitalRead(BUTTON) == LOW  && (millis() - buttonPressTimeStamp) > 900) {// debounce function to wait for 900 millis
      buttonPressTimeStamp = (millis() - 100);
      color++;
      if (color > 4) {
        color = 1;
      }
    }
  }
  while ((millis() - buttonPressTimeStamp) >= 4000 && (millis() - buttonPressTimeStamp) < 8000) {
    drawDigits(0, letterB);
    drawDigits(1, letterR);
    showTime(2, brightLevel);
    if (digitalRead(BUTTON) == LOW  && (millis() - buttonPressTimeStamp) > 4700) {
      buttonPressTimeStamp = (millis() - 4000); // returns to 4000 millis of diferece to stay in this loop
      brightLevel++;
      if (brightLevel > 10) {
        brightLevel = 1;
      }
      strip.setBrightness((brightLevel * 4));
    }
  }
  while ((millis() - buttonPressTimeStamp) >= 8000 && (millis() - buttonPressTimeStamp) < 13000) {
    drawDigits(0, letterH);
    drawDigits(1, letterR);
    showTime(2, hours);
    if (digitalRead(BUTTON) == LOW  && (millis() - buttonPressTimeStamp) > 8400) {
      buttonPressTimeStamp = (millis() - 8000);
      if (hours < 23) {
        hours++;
      } else {
        hours = 0;
      }
    }
  }
  while ((millis() - buttonPressTimeStamp) >= 13000 && (millis() - buttonPressTimeStamp) <= 16000) {
    drawDigits(0, letterM);
    drawDigits(1, letterI);
    showTime(2, minutes);
    if (digitalRead(BUTTON) == LOW && (millis() - buttonPressTimeStamp) > 13400) {
      buttonPressTimeStamp = (millis() - 13000);
      if (minutes < 59) {
        minutes++;
      } else {
        minutes = 0;
      }
    }
  }
  rtc.adjust(DateTime(0, 0, 0, hours, minutes, 0));// rtc adjusts time

  while ((millis() - buttonPressTimeStamp) >= 16000 && (millis() - buttonPressTimeStamp) <= 20000) {
    drawDigits(0, letterD);
    drawDigits(1, letterI);
    if (displayOn) {
      drawDigits(2, letterO);
      drawDigits(3, letterN);
    }
    if (!displayOn) {
      drawDigits(2, letterN);
      drawDigits(3, letterO);
    }
    if (digitalRead(BUTTON) == LOW && (millis() - buttonPressTimeStamp) > 16600) {
      buttonPressTimeStamp = (millis() - 16000);
      displayOn = !displayOn;
    }
  }

  eeprom_write_byte((uint8_t*)2, color); // values are store in EEPROM
  eeprom_write_byte((uint8_t*)3, brightLevel);
  eeprom_write_byte((uint8_t*)4, displayOn);

  if (!displayOn) {
    strip.clear();
    strip.show();
    sleep();
  }
}

void drawDigits (uint8_t digitNumber, uint8_t arrayName[] ) {// draws on digit form 0 to 3 taking values from array in characters
  //digit number from 0 left to 3 right
  uint8_t firstLed = 0;
  uint8_t lastLed = 0;
  uint8_t led = 0;
  uint8_t ledValue = 0;;

  switch (digitNumber) { // each digit NeoPixel LED number from first to last
    case 0: // digit 0 from left to right
      firstLed = 0;
      lastLed = 12;
      break;
    case 1: // digit 1
      firstLed = 13;
      lastLed = 25;
      break;
    case 2: //digit 2
      firstLed = 26;
      lastLed = 38;
      break;
    case 3: //digit 3
      firstLed = 39;
      lastLed = 51;
      break;
  }

  for (uint8_t x = firstLed; x <= lastLed ; x++) { // all arryas with caracters are progmem to save ram, in Micros like the ATTiny 85 have few ram
    ledValue = pgm_read_byte_near (arrayName + led);// read values from progmem
    switch (color) { // this code selects the color to draw the characters in colors RED,BLUE,GREEN,WHITE
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

void showTime (uint8_t firstDigit, uint8_t value) {// this function takes the digit and value from characters.h and draws it without the 0 to the left in hours
  uint8_t valueUnits = value;                      // always draws 2 digits.
  if (value < 10) {
    if (firstDigit == 0) {
      for (uint8_t x = 0; x < 13; x++) {
        strip.setPixelColor(x, 0, 0, 0);
      }
    } else {
      drawDigits(firstDigit, number0);
    }
    arrayNumberValue[0] = pgm_read_word_near(number + value);
    drawDigits((firstDigit + 1), arrayNumberValue[0]);
  } else {
    value /= 10; // some math to substract the 0 from the left in hours digits
    arrayNumberValue[0] = pgm_read_word_near(number + value);
    drawDigits(firstDigit, arrayNumberValue[0]);
    value *= 10;

    for (uint8_t x = 0; x < value ; x++) {
      valueUnits--;
    }
    arrayNumberValue[0] = pgm_read_word_near(number + valueUnits);
    drawDigits((firstDigit + 1), arrayNumberValue[0]);
  }
}
void readTimeBlinkColon() { // read time from rtc and blink colon every second
  if ((millis() - buttonPressTimeStamp) <= 1000 ) {
    //Read time from RTC
    DateTime now = rtc.now();
    minutes = now.minute();
    hours = now.hour();
  }
  if ((millis() - buttonPressTimeStamp) > 1000 && (millis() - buttonPressTimeStamp) < 2000) {
    //colon turn off you cand delete this to keep colons on
    strip.setPixelColor(52, 0, 0, 0);
    strip.setPixelColor(53, 0, 0, 0);
  }
  if ((millis() - buttonPressTimeStamp) >= 2000 && displayOn) { // colons color select to match digits
    buttonPressTimeStamp = millis();
    switch (color) {
      case 1:
        strip.setPixelColor(52, 100, 0, 0);
        strip.setPixelColor(53, 100, 0, 0);
        break;
      case 2:
        strip.setPixelColor(52, 0, 100, 0);
        strip.setPixelColor(53, 0, 100, 0);
        break;
      case 3:
        strip.setPixelColor(52, 0, 0, 100);
        strip.setPixelColor(53, 0, 0, 100);
        break;
      case 4:
        strip.setPixelColor(52, 100, 100, 100);
        strip.setPixelColor(53, 100, 100, 100);
        break;
    }
  }
  strip.show();
}
