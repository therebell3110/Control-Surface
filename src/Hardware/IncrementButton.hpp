/* ✔ */

#pragma once

#include "Button.hpp"

/**
 * @brief   A class for buttons that increment some counter or setting.
 * 
 * It behaves the same way as a computer keyboard: when you press the button, 
 * it increments the counter once. If you keep on pressing it for longer than
 * a certain threshold, it keeps on incrementing at a faster rate, until you
 * release it.
 */
class IncrementButton {
  public:
    /** 
     * @brief   Create a IncrementButton.
     * 
     * @param   button
     *          The button to read from.  
     *          The button is copied.
     */
    IncrementButton(const Button &button) : button(button) {}

    /// @see     Button::begin
    void begin() { button.begin(); }

    /**
     * @brief   An enumeration of the different actions to be performed by the
     *          counter.
     * @todo    Add states for initial press.
     */
    enum State {
        Nothing = 0, ///< The counter must not be incremented.
        Increment,   ///< The counter must be incremented.
    };

    /**
     * @brief   Get the state of the increment button.
     */
    State getState();

#ifdef INDIVIDUAL_BUTTON_INVERT
    /// @see    Button::invert
    void invert() { button.invert(); }
#endif

  private:
    Button button;

    enum {
        Initial,
        LongPress,
    } longPressState = Initial;
    unsigned long longPressRepeat;
};