#ifndef DEF_UTILITIES
#define DEF_UTILITIES

#include "sound.h"
#include "oscillator.h"
#include "chord.h"
#include <string>
#include <map>
#include <vector>

class utilities
{
	public:
		utilities();

		double GetMIDIFreq(int midiVal) const;
		int GetMIDIValue(double freq) const;
		int GetMIDIValue(float freq) const;
		std::string GetNameFromMIDI(int midiVal) const;
		int GetOctaveFromMIDI(int midiVal) const;
		int GetOctaveFromFreq(double freq) const;
		int GetOctaveFromFreq(float freq) const;

		//std::vector<oscillator> OutputChord(chord const& c, float* t);

	private:		
		void InitMIDI();		
		double MIDI[128];
};

#endif
