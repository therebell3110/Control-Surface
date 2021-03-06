/* ✔ */

#pragma once

#include <Arduino.h>
#include <Audio.h>
#include <Def/Def.hpp>
#include <Hardware/FilteredAnalog.hpp>
#include <Helpers/Updatable.hpp>

/** 
 * @brief   A class for controlling the volume of AudioMixer4 objects using a 
 *          potentiometer.
 * 
 * @tparam  N
 *          The number of mixers.
 * 
 * @ingroup Audio
 */
template <uint8_t N>
class VolumeControl : public Updatable<Potentiometer> {
  public:
    /**
     * @brief   Create a new VolumeControl object.
     * 
     * @param   mixers
     *          An array of pointers to audio mixers.  
     *          Only the pointers are saved, so the mixers should outlive this
     *          object.
     * @param   analogPin
     *          The analog pin with the potentiometer connected.
     * @param   The maximum gain for the mixers.
     */
    VolumeControl(const Array<AudioMixer4 *, N> &mixers, pin_t analogPin,
                  float maxGain = 1.0)
        : mixers(mixers), filteredAnalog(analogPin), maxGain(maxGain) {}

    /**
     * @brief   Read the potentiometer value, and adjust the gain of the mixers.
     */
    void update() override {
        if (filteredAnalog.update()) {
            float gain = filteredAnalog.getValue() * maxGain / 127.0;
            for (AudioMixer4 *mixer : mixers)
                for (uint8_t ch = 0; ch < 4; ch++)
                    mixer->gain(ch, gain);
        }
    }

    /**
     * @brief   Initialize.
     */
    void begin() override {}

  private:
    Array<AudioMixer4 *, N> mixers;
    FilteredAnalog<7> filteredAnalog;
    const float maxGain;
};