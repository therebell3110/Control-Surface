#include "MIDI_Parser.hpp"
#include "SysExBuffer.hpp"

#if defined(USB_MIDI4_SERIAL) || defined(USB_MIDI4)
#define USB_MIDI_NUMBER_OF_CABLES 4
#elif defined(USB_MIDI16_AUDIO_SERIAL) || defined(USB_MIDI16_SERIAL) ||        \
    defined(USB_MIDI16)
// TODO: || defined(USB_EVERYTHING)
#define USB_MIDI_NUMBER_OF_CABLES 16
#else
#define USB_MIDI_NUMBER_OF_CABLES 1
#endif

class USBMIDI_Parser : public MIDI_Parser {
  public:
    MIDI_read_t parse(uint8_t *packet);

    SysExMessage getSysEx() const override {
        return {sysexbuffers[CN].getBuffer(), sysexbuffers[CN].getLength(), CN};
    }

    uint8_t getCN() const override { return CN; }

  protected:
    void startSysEx(uint8_t CN) { sysexbuffers[CN].start(); }
    void endSysEx(uint8_t CN) { sysexbuffers[CN].end(); }
    bool addSysExByte(uint8_t CN, uint8_t data) {
        return sysexbuffers[CN].add(data);
    }
    bool receivingSysEx(uint8_t CN) const {
        return sysexbuffers[CN].isReceiving();
    }

    uint8_t CN = 0;

  private:
    SysExBuffer sysexbuffers[USB_MIDI_NUMBER_OF_CABLES];
};
