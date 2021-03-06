#pragma once

#include <Banks/BankableMIDIOutput.hpp>
#include <Def/Def.hpp>
#include <Hardware/Button.hpp>
#include <MIDI_Outputs/Abstract/MIDIOutputElement.hpp>

namespace Bankable {

/**
 * @brief   An abstract class for momentary push buttons that send MIDI events.
 *
 * The button is debounced.
 *
 * @see     Button
 */
template <DigitalSendFunction sendOn, DigitalSendFunction sendOff>
class MIDIButton : public BankableMIDIOutput, public MIDIOutputElement {
  public:
    /**
     * @brief   Construct a new bankable MIDIButton.
     *
     * @param   pin
     *          The digital input pin with the button connected.
     *          The internal pull-up resistor will be enabled.
     */
    MIDIButton(const OutputBankConfig &config, pin_t pin,
               const MIDICNChannelAddress &address)
        : BankableMIDIOutput{config}, button{pin}, address(address) {}

    void begin() final override { button.begin(); }
    void update() final override {
        Button::State state = button.getState();
        MIDICNChannelAddress sendAddress = address;
        if (state == Button::Falling) {
            lock();
            sendAddress += getAddressOffset();
            sendOn(sendAddress);
        } else if (state == Button::Rising) {
            sendAddress += getAddressOffset();
            sendOff(sendAddress);
            unlock();
        }
    }

#ifdef INDIVIDUAL_BUTTON_INVERT
    void invert() { button.invert(); }
#endif

  private:
    Button button;
    const MIDICNChannelAddress address;
};

} // namespace Bankable