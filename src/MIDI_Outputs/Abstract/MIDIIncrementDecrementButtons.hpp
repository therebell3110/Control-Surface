#pragma once

#include <Def/Def.hpp>
#include <Hardware/IncrementDecrementButtons.hpp>
#include <MIDI_Outputs/Abstract/MIDIOutputElement.hpp>

#include <MIDI_Senders/DigitalNoteSender.hpp>

/**
 * @brief   An abstract class for two buttons that send incremental MIDI events.
 */
template <RelativeSendFunction send>
class MIDIIncrementDecrementButtons : public MIDIOutputElement {
  protected:
    /**
     * @brief   Construct a new MIDIIncrementDecrementButtons.
     *
     * @todo    Documentation
     */
    MIDIIncrementDecrementButtons(const IncrementDecrementButtons &buttons,
                                  const MIDICNChannelAddress &address,
                                  uint8_t multiplier = 1,
                                  const MIDICNChannelAddress &resetAddress = {})
        : buttons(buttons), address(address), multiplier(multiplier),
          resetAddress(resetAddress) {}

  public:
    void begin() override { buttons.begin(); }

    void update() override {
        using IncrDecrButtons = IncrementDecrementButtons;
        switch (buttons.getState()) {
            case IncrDecrButtons::Increment: send(multiplier, address); break;
            case IncrDecrButtons::Decrement: send(-multiplier, address); break;
            case IncrDecrButtons::Reset: reset(); break;
            default: break;
        }
    }

    void reset() {
        if (resetAddress) {
            sendOn(resetAddress);
            sendOff(resetAddress);
        }
    }

#ifdef INDIVIDUAL_BUTTON_INVERT
    void invert() { buttons.invert(); }
#endif

  private:
    IncrementDecrementButtons buttons;
    const MIDICNChannelAddress address;
    const uint8_t multiplier;
    const MIDICNChannelAddress resetAddress;

    constexpr static DigitalSendFunction sendOn = DigitalNoteSender::sendOn;
    constexpr static DigitalSendFunction sendOff = DigitalNoteSender::sendOff;
};