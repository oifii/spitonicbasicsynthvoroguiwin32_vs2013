/*
 * Copyright (c) 2015-2016 Stephane Poirier
 *
 * stephane.poirier@oifii.org
 *
 * Stephane Poirier
 * 3532 rue Ste-Famille, #3
 * Montreal, QC, H2X 2L1
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef BasicSynth_h
#define BasicSynth_h

#include "Tonic.h"
#include <functional>

using namespace Tonic;

class BasicSynth : public Synth{

public:
	BasicSynth(){

//#if TONIC_HAS_CPP_11
#if 1
		// create a new oscillator which we'll use for the actual audio signal
		SineWave tone = SineWave();

		// create a sine wave we'll use for some vibrato
		SineWave vibratoOsc = SineWave();
		//vibratoOsc.freq(10); //original
		vibratoOsc.freq(addParameter("vibrato_freq", 10.0).min(0.1).max(20.0));

		// you can use the regular arithmatic operators on Generators and their subclasses (SineWave extends Generator)
		//float basePitch = 400; //original
		//TonicFloat basePitch = 400.0;
		ControlGenerator basePitch = addParameter("base_pitch", 400).min(50).max(3000);
		//Generator frequency = basePitch + (vibratoOsc * basePitch * 0.01); //original
		Generator frequency = basePitch + (vibratoOsc * basePitch * 0.01);

		// plug that frequency generator into the frequency slot of the main audio-producing sine wave
		tone.freq(frequency);

		// let's also create a tremelo effect
		//SineWave tremeloSine = SineWave().freq(1);
		SineWave tremeloSine = SineWave().freq(addParameter("tremolo_freq", 1.0).min(0.1).max(20.0));

		StereoDelay delay = StereoDelay(3.0f, 3.0f, 3.0f, 3.0f)
			//.delayTimeLeft(0.5 + SineWave().freq(0.2) * 0.01)
			.delayTimeLeft(addParameter("delay_left", 0.5).min(0.0).max(3.0) + SineWave().freq(0.2) * 0.01)
			//.delayTimeRight(0.55 + SineWave().freq(0.23) * 0.01)
			.delayTimeRight(addParameter("delay_right", 0.55).min(0.0).max(3.0) + SineWave().freq(0.23) * 0.01)
			//.feedback(0.3)
			.feedback(addParameter("delay_feedback", 0.5).min(0.0).max(1.0))
			.dryLevel(addParameter("delay_drylevel", 0.5).min(0.0).max(1.0))
			//.wetLevel(0.2);
			.wetLevel(addParameter("delay_wetlevel", 0.5).min(0.0).max(1.0));

		// set the synth's final output generator
		setOutputGen(delay.input(tone * tremeloSine));

#else

#pragma message("C++11 Support not available - ControlSwitcherTestSynth disabled")

#endif
	}
};

//TONIC_REGISTER_SYNTH(BasicSynth)

#endif
