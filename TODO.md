## TODO

- Make many protected functions private if 1) they are not needed in tests 2) they should not be called from within subclasses.
- ✔ Automatic dependencies in Makefiles for tests.
- Fix and reorder examples.
- Move Wikis to tttapa.github.io.
- Make it easier to add custom bitmaps.
- ✔ Cleanup structure of input elements.
- Cleanup structure of display elements.
- Extension consistency.
- ✔ Malloc → new.
- Add motorized faders.
- Make constructors of abstract classes protected.
- Make destructors virtual if necessary. (e.g. callback classes)
- GitHub template
- Flashing LEDs
- Keywords
- Fix firmware link DFU scripts https://raw.githubusercontent.com/arduino/ArduinoCore-avr/master/firmwares/atmegaxxu2/Arduino-COMBINED-dfu-usbserial-atmega16u2-Uno-Rev3.hex
- Find and list all TODO's throughout the source code.

## Specific elements

### Outputs

#### MIDI Notes
- ✔ Button
- ✔ Latching Button
- ✔ Buttons
- ✔ Button Matrix

- ✔ Bankable Button
- ✔ Bankable Latching Button
- ✔ Bankable Buttons
- ✔ Bankable Button Matrix

#### MIDI CC
- ✔ Button
- ✔ Latching Button
- ✔ Buttons
- ✔ Button Matrix

- Potentiometer
- Potentiometers

- ✔ Rotary Encoder

- ✔ Bankable Button
- ✔ Bankable Latching Button
- ✔ Bankable Buttons
- ✔ Bankable Button Matrix

- ✔ Bankable Potentiometer
- Bankable Potentiometers

- ✔ Bankable Rotary Encoder

#### MIDI Pitch Bend
- ✔ Potentiometer
- Potentiometers
- Motorized fader

- ✔ Bankable Potentiometer
- Bankable Potentiometers
- Bankable Motorized fader


### Inputs

#### Generic
- ✔ LED

- ✔ Bankable LED

#### MCU
- ✔ VPotRing
- ✔ VU
- ✔ Assignment display
- ✔ Time display
- Flashing LED
- LCD display (SysEx)

- ✔ Bankable VPotRing
- ✔ Bankable VU
- Flashing LED


### Display
- ✔ Selectors
- ✔ VPotRing
- ✔ VU
- ✔ LED Bitmap
- ✔ Timedisplay
- Assignment display
- LCD


### Selectors
- Switch
- Latching
- Encoder
- ✔ Increment
- ✔ Increment/Decrement
- ✔ Many Buttons

### Selectable
- ✔ Bank
- Program Change
- Transpose
