#ifndef DEF_MIDI
#define DEF_MIDI

#include <string>

/// <summary>
/// Various operations on MIDI values
/// </summary>
class midi
{
	public:
		midi();

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
