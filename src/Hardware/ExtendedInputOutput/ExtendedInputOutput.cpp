#include "ExtendedInputOutput.hpp"
#include "ExtendedIOElement.hpp"
#include <Arduino.h>
#include <Helpers/Error.hpp>

namespace ExtIO {

template <class T>
bool inRange(T target, T start, T end) {
    return target >= start && target < end;
}

ExtendedIOElement &getIOElementOfPin(pin_t pin) {
    for (ExtendedIOElement &el : ExtendedIOElement::getAll())
        if (pin < el.getStart())
            break;
        else if (inRange(pin, el.getStart(), el.getEnd()))
            return el;

    FATAL_ERROR(F("Error: the given pin does not correspond to an Extended IO "
                  "element."),
                0x8888);

    // TODO: why doesn't this give a compilation error?
    // No return statement. On desktop, FATAL_ERROR throws an exception, so
    // I get why that works, but on Arduino, it just calls fatalErrorExit, which
    // is marked 'noreturn'. However, if I remove the 'noreturn' attribute, and 
    // have it return immediately, it still compiles, without returning a valid
    // reference.
}

void pinMode(pin_t pin, uint8_t mode) {
    // DEBUGFN(DEBUGVAR(pin) << '\t' << DEBUGVAR(mode));
    if (pin < NUM_DIGITAL_PINS + NUM_ANALOG_INPUTS) {
        ::pinMode(pin, mode);
    } else {
        ExtendedIOElement &el = getIOElementOfPin(pin);
        el.pinMode(pin - el.getStart(), mode);
    }
}
void pinMode(int pin, uint8_t mode) { pinMode((pin_t)pin, mode); }

void digitalWrite(pin_t pin, uint8_t val) {
    // DEBUGFN(DEBUGVAR(pin) << '\t' << DEBUGVAR(val));
    if (pin < NUM_DIGITAL_PINS + NUM_ANALOG_INPUTS) {
        ::digitalWrite(pin, val);
    } else {
        ExtendedIOElement &el = getIOElementOfPin(pin);
        el.digitalWrite(pin - el.getStart(), val);
    }
}
void digitalWrite(int pin, uint8_t val) { digitalWrite((pin_t)pin, val); }

int digitalRead(pin_t pin) {
    if (pin < NUM_DIGITAL_PINS + NUM_ANALOG_INPUTS) {
        return ::digitalRead(pin);
    } else {
        ExtendedIOElement &el = getIOElementOfPin(pin);
        return el.digitalRead(pin - el.getStart());
    }
    return 0;
}
int digitalRead(int pin) { return digitalRead((pin_t)pin); }

void shiftOut(pin_t dataPin, pin_t clockPin, uint8_t bitOrder, uint8_t val) {
    uint8_t i;

    for (i = 0; i < 8; i++) {
        if (bitOrder == LSBFIRST)
            digitalWrite(dataPin, !!(val & (1 << i)));
        else
            digitalWrite(dataPin, !!(val & (1 << (7 - i))));

        digitalWrite(clockPin, HIGH);
        digitalWrite(clockPin, LOW);
    }
}
void shiftOut(int dataPin, int clockPin, uint8_t bitOrder, uint8_t val) {
    shiftOut((pin_t)dataPin, (pin_t)clockPin, bitOrder, val);
}

analog_t analogRead(pin_t pin) {
    if (pin < NUM_DIGITAL_PINS + NUM_ANALOG_INPUTS) {
        return ::analogRead(pin);
    } else {
        ExtendedIOElement &el = getIOElementOfPin(pin);
        return el.analogRead(pin - el.getStart());
    }
    return 0;
}
analog_t analogRead(int pin) { return analogRead((pin_t)pin); }

} // namespace ExtIO