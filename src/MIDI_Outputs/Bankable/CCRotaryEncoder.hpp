#pragma once

#include <MIDI_Outputs/Bankable/Abstract/MIDIRotaryEncoder.hpp>
#include <MIDI_Senders/RelativeCCSender.hpp>

namespace Bankable {

/**
 * @brief   A class of MIDIOutputElement%s that read the input of a **quadrature
 *          (rotary) encoder** and send out relative MIDI **Control Change**
 *          events.
 * 
 *          This version can be banked.
 *
 * @note    To use this class, include the [PJRC Encoder library]
 *          (https://github.com/PaulStoffregen/Encoder) before the
 *          Control-Surface library.
 *
 * @ingroup MIDIOutputElements
 */
class CCRotaryEncoder : public MIDIRotaryEncoder<RelativeCCSender::send> {
  public:
    /**
     * @brief   Construct a new Bankable CCRotaryEncoder object with the given 
     *          pins, controller, channel, speed factor, and number of pulses
     *          per step.
     * 
     * @param   pins
     *          A list of the two pins connected to the A and B outputs of the
     *          encoder.  
     *          The internal pull-up resistors will be enabled by the Encoder
     *          library.
     * @param   controller
     *          The MIDI controller number. [0, 119]
     * @param   channel
     *          The MIDI channel. [1, 16]
     * @param   speedMultiplier
     *          A constant factor to increase the speed of the rotary encoder.
     *          The difference in position will just be multiplied by this 
     *          factor. 
     * @param   pulsesPerStep
     *          The number of pulses per physical click of the encoder.
     *          For a normal encoder, this is 4. If you want to increase the
     *          resolution, for the use of Jog wheels, for example, you can go
     *          as 1.  
     *          Whereas a greater speedMultiplier factor will increase the 
     *          speed, increasing the number of pulsesPerStep will result in a 
     *          lower speed.
     * 
     * @ingroup MIDIOutputElementConstructors
     */
    CCRotaryEncoder(const OutputBankConfig &config, const EncoderPinList &pins,
                    const MIDICNChannelAddress &address,
                    uint8_t speedMultiplier, uint8_t pulsesPerStep)
        : MIDIRotaryEncoder<RelativeCCSender::send>(
              config, pins, address, speedMultiplier, pulsesPerStep) {}

// For tests only (PJRC Encoder library's copy constructor doesn't work)
#ifndef ARDUINO
    CCRotaryEncoder(const OutputBankConfig &config, const Encoder &encoder,
                    const MIDICNChannelAddress &address,
                    uint8_t speedMultiplier, uint8_t pulsesPerStep)
        : MIDIRotaryEncoder<RelativeCCSender::send>(
              config, encoder, address, speedMultiplier, pulsesPerStep) {}
#endif
};

} // namespace Bankable