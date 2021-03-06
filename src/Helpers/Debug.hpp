#pragma once

#include <Settings/SettingsWrapper.hpp>

#ifdef ARDUINO

// #define DEBUG_OUT Serial // Uncomment this line to override Arduino IDE debug
// level

#include <stdlib.h>

#ifndef PRINTSTREAM_FALLBACK
#include "PrintStream.hpp"
#else
#include <Arduino.h>
typedef Print &manipulator(Print &);
inline Print &endl(Print &printer) {
    printer.println();
    printer.flush();
    return printer;
}
template <class T>
inline Print &operator<<(Print &printer, const T printable) {
    printer.print(printable);
    return printer;
}
template <>
inline Print &operator<<(Print &printer, manipulator pf) {
    return pf(printer);
}
#endif

#else // No Arduino

#include <iomanip>
#include <iostream>

using std::boolalpha;
using std::cout;
using std::dec;
using std::endl;
using std::flush;
using std::hex;
using std::noboolalpha;
using std::noshowbase;
using std::nouppercase;
using std::setbase;
using std::setprecision;
using std::showbase;
using std::uppercase;
#ifndef Arduino_h
#define F(x) (x)
#endif

#endif // Arduino

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

#define FUNC_LOCATION                                                          \
    '[' << __PRETTY_FUNCTION__ << F(" @ line " STR(__LINE__) "]:\t")
#define LOCATION F("[" __FILE__ ":" STR(__LINE__) "]:\t")

#ifdef DEBUG_OUT

/**
 * @brief   If debugging is enabled, print the given data to the
 *          debug output stream.
 *
 * @param   x
 *          The data to be printed.
 */
#define DEBUG(x)                                                               \
    do {                                                                       \
        DEBUG_OUT << x << endl;                                                \
        DEBUG_OUT.flush();                                                     \
    } while (0)

/**
 * @brief   If debugging is enabled, print the filename and line number to the
 *          debug output stream, followed by the given data.
 *
 * @param   x
 *          The data to be printed.
 */
#define DEBUGREF(x)                                                            \
    do {                                                                       \
        DEBUG_OUT << LOCATION << x << endl;                                    \
        DEBUG_OUT.flush();                                                     \
    } while (0)

/**
 * @brief   If debugging is enabled, print the function name and line number to
 *          the debug output stream, followed by the given data.
 *
 * @param   x
 *          The data to be printed.
 */
#define DEBUGFN(x)                                                             \
    do {                                                                       \
        DEBUG_OUT << FUNC_LOCATION << x << endl;                               \
        DEBUG_OUT.flush();                                                     \
    } while (0)

#define DEBUGVAR(x) F(STR(x) " = ") << x

#else // ifdef DEBUG_OUT

#define DEBUG(x)                                                               \
    do {                                                                       \
    } while (0)
#define DEBUGREF(x)                                                            \
    do {                                                                       \
    } while (0)
#define DEBUGFN(x)                                                             \
    do {                                                                       \
    } while (0)

#endif