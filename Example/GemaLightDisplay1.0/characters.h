/* Digits to draw the leds using arrays.
  Each digits are 13 Neopixels leds from 0 to 51
  52 and 53 are blink colons
  LED POSITION EXAMPLE X 4 DIGITS:
 *  *  *
 *     *
 *  *  *
 *     *
 *  *  *

*/

#define LED 100

const PROGMEM uint8_t number0 [13] = {LED, LED, LED,
                                      LED,       LED,
                                      LED,  0,   LED,
                                      LED,       LED,
                                      LED, LED,  LED
                                     };


const PROGMEM uint8_t number1 [13] = {0,   0,  LED,
                                      0,        LED,
                                      0,   0,   LED,
                                      0,        LED,
                                      0,   0,   LED
                                     };

const PROGMEM uint8_t number2 [13] = {LED, LED, LED,
                                      0,        LED,
                                      LED, LED, LED,
                                      LED,        0,
                                      LED, LED, LED
                                     };

const PROGMEM uint8_t number3 [13] = {LED, LED, LED,
                                      0,         LED,
                                      LED, LED,  LED,
                                      0,         LED,
                                      LED, LED,  LED
                                     };

const PROGMEM uint8_t number4 [13] = {LED,  0,   LED,
                                      LED,       LED,
                                      LED, LED,  LED,
                                      0,         LED,
                                      0,    0,   LED
                                     };

const PROGMEM uint8_t number5 [13] = {LED, LED, LED,
                                      LED,        0,
                                      LED,  LED, LED,
                                      0,         LED,
                                      LED,  LED, LED
                                     };

const PROGMEM uint8_t number6 [13] = {LED,  0,   0,
                                      LED,        0,
                                      LED,  LED, LED,
                                      LED,       LED,
                                      LED,  LED, LED
                                     };

const PROGMEM uint8_t number7 [13] = {LED, LED, LED,
                                      0,         LED,
                                      0,   0,    LED,
                                      0,         LED,
                                      0,   0,    LED
                                     };

const PROGMEM uint8_t number8 [13] = {LED, LED, LED,
                                      LED,       LED,
                                      LED, LED,  LED,
                                      LED,       LED,
                                      LED, LED,  LED
                                     };

const PROGMEM uint8_t number9 [13] = {LED, LED, LED,
                                      LED,       LED,
                                      LED, LED,  LED,
                                      0,         LED,
                                      0,   0,    LED
                                     };


// Array containing all numbers array
const PROGMEM uint16_t number[10] = { number0, number1, number2, number3, number4,
                                      number5, number6, number7, number8, number9
                                    };
//letters
const PROGMEM uint8_t letterA [13] = {  0,  LED,    0,
                                        LED,        LED,
                                        LED,  LED,  LED,
                                        LED,        LED,
                                        LED,    0,  LED
                                     };



const PROGMEM uint8_t letterB [13] = {LED,  LED,  0,
                                      LED,        LED,
                                      LED,  LED,  0,
                                      LED,        LED,
                                      LED,  LED,  0
                                     };


const PROGMEM uint8_t letterC [13] = { 0,  LED,   0,
                                       LED,        0,
                                       LED,  0,    0,
                                       LED,        0,
                                       0,  LED,   0
                                     };

const PROGMEM uint8_t letterD [13] = {LED,  LED,    0,
                                      LED,        LED,
                                      LED,  0,    LED,
                                      LED,        LED,
                                      LED,  LED,    0
                                     };

const PROGMEM uint8_t letterE [13] = {LED,  LED,   0,
                                      LED,         0,
                                      LED,  LED,   0,
                                      LED,         0,
                                      LED,  LED,   0
                                     };


const PROGMEM uint8_t letterF [13] = {LED,  LED,   0,
                                      LED,         0,
                                      LED,  LED,   0,
                                      LED,         0,
                                      LED,   0,    0
                                     };

const PROGMEM uint8_t letterG [13] = {  0, LED,    0,
                                        LED,         0,
                                        LED,  LED,  LED,
                                        LED,        LED,
                                        LED,  LED,   0
                                     };

const PROGMEM uint8_t letterH [13] = {LED,  0  , LED,
                                      LED,       LED,
                                      LED, LED,  LED,
                                      LED,       LED,
                                      LED,   0,  LED
                                     };

const PROGMEM uint8_t letterI [13] = {0,   LED,  0,
                                      0,         0,
                                      0,   LED,  0,
                                      0,         0,
                                      0,   LED,  0
                                     };

const PROGMEM uint8_t letterJ [13] = {   0,   0,    LED,
                                         0,       LED,
                                         LED,  0,   LED,
                                         LED,       LED,
                                         0,  LED, LED
                                     };

const PROGMEM uint8_t letterK [13] = {   LED,   0,  LED,
                                         LED,         0,
                                         LED,  LED,   0,
                                         LED,         0,
                                         LED,  0,   LED
                                     };

const PROGMEM uint8_t letterL [13] = {   LED,   0,     0,
                                         LED,          0,
                                         LED,   0,     0,
                                         LED,          0,
                                         LED,  LED,    0
                                     };

const PROGMEM uint8_t letterM [13] = {   0,   0,     0,
                                         LED,       LED,
                                         LED,  LED, LED,
                                         LED,       LED,
                                         LED,  0,   LED
                                     };

const PROGMEM uint8_t letterN [13] = {  LED,  LED, LED,
                                        LED,       LED,
                                        LED,  0,   LED,
                                        LED,       LED,
                                        LED,  0,   LED
                                     };


const PROGMEM uint8_t letterO [13] = { 0,  LED,   0,
                                       LED,       LED,
                                       LED,   0,  LED,
                                       LED,       LED,
                                       0,  LED,  0
                                     };


const PROGMEM uint8_t letterP [13] = {LED, LED,   0,
                                      LED,       LED,
                                      LED, LED,   0,
                                      LED,        0,
                                      LED,   0,   0
                                     };

const PROGMEM uint8_t letterQ [13] = {  0, LED,   0,
                                        LED,       LED,
                                        0, LED,  LED,
                                        0,       LED,
                                        0,   0,  LED
                                     };

const PROGMEM uint8_t letterR [13] = {LED, LED,   0,
                                      LED,       LED,
                                      LED, LED,   0,
                                      LED,       LED,
                                      LED,   0,  LED
                                     };

const PROGMEM uint8_t letterS [13] = { 0, LED, LED,
                                       LED,       0,
                                       0,   LED,  0,
                                       0,       LED,
                                       LED,  LED,  0
                                     };

const PROGMEM uint8_t letterT [13] = {LED, LED, LED,
                                      0,         0,
                                      0,   LED,  0,
                                      0,         0,
                                      0,   LED,  0
                                     };

const PROGMEM uint8_t letterX [13] = {LED,  0,  LED,
                                      0,          0,
                                      0,   LED,   0,
                                      0,          0,
                                      LED,   0,  LED
                                     };

const PROGMEM uint8_t letterY [13] = {LED,   0, LED,
                                      0,          0,
                                      0,   LED,   0,
                                      0,          0,
                                      0,   LED,   0
                                     };

const PROGMEM uint8_t letterZ [13] = {LED, LED, LED,
                                      0,        LED,
                                      0,   LED,   0,
                                      LED,          0,
                                      LED, LED,  LED
                                     };
//simbols

const PROGMEM uint8_t simbolStop [13] = {0,   0,   0,
                                         0,        0,
                                         0,   0,   0,
                                         0,        0,
                                         0,  LED,  0
                                        };

const PROGMEM uint8_t simbolPercent [13] = {LED,   0,  0,
                                            0,       LED,
                                            0,   LED,  0,
                                            LED,       0,
                                            0,  0,   LED
                                           };

const PROGMEM uint8_t simbolDegree [13] = {LED,  LED, 0,
                                            LED,       0,
                                            LED,  LED, 0,
                                            0,       0,
                                            0,  0, LED
                                           };

const PROGMEM uint8_t simbolNull [13] = {   0,   0,  0,
                                            0,       0,
                                            0,   0,  0,
                                            0,       0,
                                            0,  0,   0
                                        };
