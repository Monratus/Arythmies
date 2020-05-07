#ifndef DEF_UTILITIES
#define DEF_UTILITIES

#include <string>
#include <map>
#include <vector>


/// <summary>
/// Contains various methods performing various tasks on the signal
/// </summary>
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

	private:		
		void InitMIDI();		
		double MIDI[128];
};

#endif
