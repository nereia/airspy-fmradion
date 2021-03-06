// airspy-fmradion
// Software decoder for FM broadcast radio with Airspy
//
// Copyright (C) 2019 Kenji Rikitake, JJ1BDX
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <cassert>

#include "IfAgc.h"
#include "Utility.h"

// class IfAgc

IfAgc::IfAgc(const float initial_gain, const float max_gain,
             const float reference, const float rate)
    // Initialize member fields
    : m_log_current_gain(std::log(initial_gain)),
      m_log_max_gain(std::log(max_gain)), m_log_reference(std::log(reference)),
      m_rate(rate) {
  // Do nothing
}

// IF AGC.
// Algorithm shown in:
// https://www.mathworks.com/help/comm/ref/comm.agc-system-object.html
// https://www.mathworks.com/help/comm/ref/linear_loop_block_diagram.png

void IfAgc::process(const IQSampleVector &samples_in,
                    IQSampleVector &samples_out) {
  unsigned int n = samples_in.size();
  samples_out.resize(n);

  for (unsigned int i = 0; i < n; i++) {
    // Compute output based on the current gain.
    float current_gain = std::exp(m_log_current_gain);
    IQSample input = samples_in[i];
    IQSample output =
        IQSample(input.real() * current_gain, input.imag() * current_gain);
    samples_out[i] = output;
    // Update the current gain.
    // Note: the original algorithm multiplied the abs(input)
    //       with the current gain (exp(log_current_gain))
    //       then took the logarithm value, but the sequence can be
    //       realigned as taking the log value of the abs(input)
    //       then add the log_current_gain.
    float log_amplitude =
        std::log(Utility::estimate_magnitude(input)) + m_log_current_gain;
    float error = (m_log_reference - log_amplitude) * m_rate;
    float new_log_current_gain = m_log_current_gain + error;
    if (new_log_current_gain > m_log_max_gain) {
      new_log_current_gain = m_log_max_gain;
    }
    m_log_current_gain = new_log_current_gain;
  }
}

// end
