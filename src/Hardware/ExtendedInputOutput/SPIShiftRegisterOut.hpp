/* ✔ */

#pragma once

#include "ShiftRegisterOutBase.hpp"
#include <Arduino.h> // MSBFIRST, SS
#include <Helpers/BitArray.hpp>

/**
 * @brief   A class for serial-in/parallel-out shift registers, 
 *          like the 74HC595 that are connected to the SPI bus.
 * 
 * @tparam  N
 *          The number of bits in total. Usually, shift registers (e.g. the
 *          74HC595) have eight bits per chip, so `length = 8 * k` where `k`
 *          is the number of cascaded chips.
 * 
 * @ingroup ExtIO
 */
template <uint8_t N>
class SPIShiftRegisterOut : public ShiftRegisterOutBase<N> {
  public:
    /**
     * @brief   Create a new SPIShiftRegisterOut object with a given bit order,
     *          and a given number of outputs.
     * 
     * Multiple shift registers can be cascaded by connecting the serial output
     * of the first one to the input of the second one:
     * 
     * ```
     * CLK   >───────────┬──────────────────────┬───────── ⋯
     *           ┏━━━━━━━┷━━━━━━━┓      ┏━━━━━━━┷━━━━━━━┓ 
     *           ┃     SH_CP     ┃      ┃     SH_CP     ┃ 
     * MOSI  >───┨ DS        Q7S ┠──────┨ DS        Q7S ┠─ ⋯
     *           ┃     ST_CP     ┃      ┃     ST_CP     ┃ 
     *           ┗━━━━━━━┯━━━━━━━┛      ┗━━━━━━━┯━━━━━━━┛ 
     * CS    >───────────┴──────────────────────┴───────── ⋯
     * ```
     * 
     * @param   latchPin
     *          The digital output pin connected to the latch pin (ST_CP or 
     *          RCLK) of the shift register.
     * @param   bitOrder
     *          Either `MSBFIRST` (most significant bit first) or `LSBFIRST`
     *          (least significant bit first).
     */
    SPIShiftRegisterOut(pin_t latchPin = SS, uint8_t bitOrder = MSBFIRST);

    /**
     * @brief   Initialize the shift register.  
     *          Setup the SPI interface, set the CS pin to output mode,
     *          and set all shift register outputs to `LOW`.
     */
    void begin() override;

    /**
     * @brief   Write the state buffer to the physical outputs.
     */
    void update() override;
};

#include "SPIShiftRegisterOut.ipp"