/*
 * SPDX-FileCopyrightText: Copyright 2020-2026 OpenRTX Contributors
 * 
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef DEMODULATOR_H
#define DEMODULATOR_H

#ifndef __cplusplus
#error This header is C++ only!
#endif

#include "core/iir.hpp"
#include <cstdint>
#include <cstddef>
#include <memory>
#include <array>
#include "core/dsp.h"
#include <cmath>
#include "core/audio_path.h"
#include "core/audio_stream.h"


namespace DMR
{

class Demodulator
{
public:

    /**
     * Constructor.
     */
    Demodulator();

    /**
     * Destructor.
     */
    ~Demodulator();

    /**
     * Allocate buffers for baseband signal sampling and initialise demodulator.
     */
    void init();

    /**
     * Shutdown modulator and deallocate data buffers.
     */
    void terminate();

    /**
     * Starts the sampling of the baseband signal in a double buffer.
     */
    void startBasebandSampling();

    /**
     * Stops the sampling of the baseband signal in a double buffer.
     */
    void stopBasebandSampling();

    /**
     * Returns the a frame decoded from the baseband signal.
     *
     * @return reference to the internal data structure containing the last
     * decoded frame.
     */
  //  const frame_t& getFrame();

    /**
     * Demodulates data from the ADC and fills the idle frame.
     * Everytime this function is called a whole ADC buffer is consumed.
     *
     * @param invertPhase: invert the phase of the baseband signal before decoding.
     * @return true if a new frame has been fully decoded.
     */
    bool update(const bool invertPhase = false);

    /**
     * Process a single baseband sample through the demodulation chain.
     *
     * @param rawSample: signed 16-bit baseband sample.
     * @param invertPhase: invert the phase of the sample before decoding.
     * @return true if a new frame has been fully decoded and not yet read
     * with getFrame().
     */
    bool sample(int16_t rawSample, bool invertPhase = false);

    /**
     * @return true if a demodulator is locked on an DMR stream.
     */
    bool isLocked();

private:


}; /* DMR */
}
#endif /* DEMODULATOR_H */
