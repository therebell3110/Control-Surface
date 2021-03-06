#pragma once

#include <MIDI_Inputs/MIDIInputElementCC.hpp>
#include <Print.h>
#include <string.h>

namespace MCU {

template <uint8_t LENGTH>
class SevenSegmentDisplay : public MIDIInputElementCC, public Printable {
  public:
    /**
    * @brief     Constructor.
    * @todo      Documentation.
    */
    SevenSegmentDisplay(const MIDICNChannelAddress &address)
        : MIDIInputElementCC{address} {
        reset();
    }

    void reset() override {
        for (char &c : text)
            c = ' ';
    }

  private:
    /**
     * @brief   Update a character.
     */
    virtual bool updateImpl(const MIDI_message_matcher &midimsg,
                            const MIDICNChannelAddress &target) override {
        uint8_t index =
            LENGTH - (target.getAddress() - address.getAddress()) - 1;
        // decimal point → 0x80, no decimal point → 0x00
        uint8_t decimalPt = (midimsg.data2 & 0x40) << 1;
        uint8_t data2 = midimsg.data2 & 0x3F;
        uint8_t character = data2 >= 0x20 ? data2 : data2 + 0x40;
        character |= decimalPt;
        text[index] = character;
        return true;
    }

    /**
     * @brief   Check if the address of the incoming MIDI message
     *          matches an address of this element.
     */
    inline bool match(const MIDICNChannelAddress &target) const override {
        return MIDICNChannelAddress::matchAddressInRange(target, address,
                                                         LENGTH);
    }

  public:
    /**
     * @brief   Copy the ASCII text into the given buffer.
     *
     * @param   buffer
     *          The destination to write the text to.
     *          Will be null-terminated.
     *          Should have a size of at least `length`+1 bytes.
     */
    void getText(char *buffer, uint8_t offset = 0,
                 uint8_t length = LENGTH) const {
        if (offset >= LENGTH)
            offset = LENGTH - 1;
        if (length > LENGTH - offset)
            length = LENGTH - offset;
        for (uint8_t i = 0; i < length; i++)
            buffer[i] = getCharacterAt(i + offset);
        buffer[length] = '\0';
    }

    /**
     * @brief   Get the character at the given index.
     * @todo    Documentation.
     */
    inline char getCharacterAt(uint8_t index) const {
        return text[index] & 0x7F;
    }

    /**
     * @brief   Copy the decimal points into the given buffer.
     *
     * @param   buffer
     *          The destination to write the decimal points to.
     *          Should have a size of at least `LENGTH` bytes.
     */
    void getDecimalPoints(bool *buffer) const {
        for (uint8_t i = 0; i < LENGTH; i++)
            buffer[i] = getDecimalPointAt(i);
    }

    /**
     * @brief   Get the decimal point state at the given index.
     * @todo    Documentation.
     */
    inline bool getDecimalPointAt(uint8_t index) const {
        return text[index] & 0x80;
    }

    /**
     * @brief   Print out the text of the display to the given Print.
     */
    size_t printTo(Print &printer) const override {
        size_t s = 0;
        for (uint8_t i = 0; i < LENGTH; i++) {
            s += printer.print(getCharacterAt(i));
            if (getDecimalPointAt(i))
                s += printer.print('.');
        }
        return s;
    }

  private:
    char text[LENGTH];
};

} // namespace MCU