#include "midi.h"
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

midi::midi() 
{		
	InitMIDI();	
}
/// <summary>
/// Initialize MIDI center frequecies with A4 = 440Hz
/// </summary>
void midi::InitMIDI()
{
	MIDI[69] = 440; // A4
	for (int i = 0; i < 128; i++)
	{
		MIDI[i] = MIDI[69] * pow(2, (double)(i-69)/12);
	}
}
/// <summary>
/// Gets the MIDI value's frequency
/// </summary>
/// <param name="midiVal">MIDI value between 0 and 127</param>
/// <returns>center frequency in Hz</returns>
double midi::GetMIDIFreq(int midiVal) const
{
	try
	{
		if (midiVal < 0 || midiVal > 127)
			throw int(0);
		else
			return MIDI[midiVal];
	}
	catch (int const& e)
	{
		if(e==0)
			cerr << "Value out of range! (MIDI val should be between 0 and 127)" << endl;
	}
	
}
/// <summary>
/// Gets the frequency's closest MIDI value
/// </summary>
/// <param name="freq">frequency in Hz</param>
/// <returns>the nearest MIDI value</returns>
int midi::GetMIDIValue(double freq) const
{
	try
	{
		if (freq < 0)
			throw(0);
		else
		{
			int val = 0;
			if (freq <= MIDI[0])
				return 0;
			else
			{
				while (freq > MIDI[val])
					val++;
				if (freq - MIDI[val - 1] < MIDI[val] - freq)
					return val - 1;
				else
					return val;
			}		
		}
	}
	catch (int const& e)
	{
		if (e == 0)
			cerr << "Value out of range! (Frequency should be positive)" << endl;
	}
}
/// <summary>
/// Gets the frequency's closest MIDI value
/// </summary>
/// <param name="freq">frequency in Hz</param>
/// <returns>the nearest MIDI value</returns>
int midi::GetMIDIValue(float freq) const
{
	try
	{
		if (freq < 0)
			throw(0);
		else
		{
			int val = 0;
			if (freq <= MIDI[0])
				return 0;
			else
			{
				while (freq > MIDI[val])
					val++;
				
				if (freq - MIDI[val-1] < MIDI[val] - freq)
					return val - 1;
				else
					return val;
			}
		}
	}
	catch (int const& e)
	{
		if (e == 0)
			cerr << "Value out of range! (Frequency should be positive)" << endl;
	}
}
/// <summary>
/// Gets a note's name from its MIDI value
/// </summary>
/// <param name="midiVal">MIDI value</param>
/// <returns>the note's name (ex: "C", "Db"...)</returns>
string midi::GetNameFromMIDI(int midiVal) const
{
	int val = midiVal % 12;
	switch (val)
	{
		case 0: return "C";
		case 1: return "Db";
		case 2: return "D";
		case 3: return "Eb";
		case 4: return "E";
		case 5: return "F";
		case 6: return "Gb";
		case 7: return "G";
		case 8: return "Ab";
		case 9: return "A";
		case 10: return "Bb";
		case 11: return "B";
	}
}
/// <summary>
/// Gets the note's octave from its MIDI value
/// </summary>
/// <param name="midiVal">MIDI value</param>
/// <returns>the octave (-1 is the lowest)</returns>
int midi::GetOctaveFromMIDI(int midiVal) const
{
	return (int)(floor(midiVal / 12) - 1);
}
/// <summary>
/// Gets the note's octave from its frequency
/// </summary>
/// <param name="midiVal">frequency in Hz</param>
/// <returns>the octave (-1 is the lowest)</returns>
int midi::GetOctaveFromFreq(double freq) const
{
	return (int)(floor(GetMIDIValue(freq) / 12) - 1);
}
/// <summary>
/// Gets the note's octave from its frequency
/// </summary>
/// <param name="midiVal">frequency in Hz</param>
/// <returns>the octave (-1 is the lowest)</returns>
int midi::GetOctaveFromFreq(float freq) const
{
	return (int)(floor(GetMIDIValue(freq) / 12) - 1);
}

