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

#ifndef SOFTFM_FILTERPARAMETERS_H
#define SOFTFM_FILTERPARAMETERS_H

#include "SoftFM.h"

// Class for providing filter parameters
// based on pre-calculated tables

// Class declaration

class FilterParameters {
public:
  static const IQSampleCoeff delay_3taps_only_iq;

  static const SampleCoeff jj1bdx_48khz_fmaudio;
  static const SampleCoeff jj1bdx_48khz_nbfmaudio;
  static const SampleCoeff delay_3taps_only_audio;

  static const IQSampleCoeff jj1bdx_am_12khz_medium;
  static const IQSampleCoeff jj1bdx_am_12khz_narrow;

  static const IQSampleCoeff jj1bdx_ssb_3to6khz;
  static const IQSampleCoeff jj1bdx_cw_250hz;

  // TODO: Hilbert filter coefficients are ASYMMETRIC,
  // so they should not be treated the same as
  // LPF/BPF with symmetric coefficients
};

#endif // SOFTFM_EQPARAMETERS_H
