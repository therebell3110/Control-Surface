/* ✔ */

#pragma once

#include "ExtendedIOElement.hpp"
#include <Arduino.h> // pin functions and constants

#define EXT_PIN(x) (x + NUM_DIGITAL_PINS + NUM_ANALOG_INPUTS)

const static uint8_t tmp_HIGH = HIGH;
const static uint8_t tmp_LOW = LOW;
const static uint8_t tmp_INPUT = INPUT;
const static uint8_t tmp_OUTPUT = OUTPUT;
const static uint8_t tmp_INPUT_PULLUP = INPUT_PULLUP;


#ifdef HIGH
#undef HIGH
#endif
#ifdef LOW
#undef LOW
#endif

#ifdef INPUT
#undef INPUT
#endif
#ifdef OUTPUT
#undef OUTPUT
#endif
#ifdef INPUT_PULLUP
#undef INPUT_PULLUP
#endif

const uint8_t HIGH = tmp_HIGH;
const uint8_t LOW = tmp_LOW;

const uint8_t INPUT = tmp_INPUT;
const uint8_t OUTPUT = tmp_OUTPUT;
const uint8_t INPUT_PULLUP = tmp_INPUT_PULLUP;

/**
 * @brief   A namespace with alternatives to the standard Arduino IO functions
 *          that can be used with extended IO pin numbers.
 */
namespace ExtIO {
/**
 * @brief   Find the IO element of a given extended IO pin number. 
 * 
 * @param   pin
 *          The extended IO pin number to find the IO element of.
 * @return  A pointer to the extended IO element that the given pin belongs to.
 */
extern ExtendedIOElement &getIOElementOfPin(pin_t pin);
/// An ExtIO version of the Arduino function
extern void pinMode(pin_t pin, uint8_t mode);
/// An ExtIO version of the Arduino function
extern void pinMode(int pin, uint8_t mode);
/// An ExtIO version of the Arduino function
extern void digitalWrite(pin_t pin, uint8_t val);
/// An ExtIO version of the Arduino function
extern void digitalWrite(int pin, uint8_t val);
/// An ExtIO version of the Arduino function
extern int digitalRead(pin_t pin);
/// An ExtIO version of the Arduino function
extern int digitalRead(int pin);
/// An ExtIO version of the Arduino function
extern void shiftOut(pin_t dataPin, pin_t clockPin, uint8_t bitOrder,
                     uint8_t val);
/// An ExtIO version of the Arduino function
extern void shiftOut(int dataPin, int clockPin, uint8_t bitOrder, uint8_t val);
/// An ExtIO version of the Arduino function
extern analog_t analogRead(pin_t pin);
/// An ExtIO version of the Arduino function
extern analog_t analogRead(int pin);

}