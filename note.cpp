#include "note.h"
#include "utilities.h"
#include <iostream>

using namespace std;

note::note() : freq(0), midiId(-1), oct(-1) { }
note::note(utilities const& u) : freq(0), midiId(-1), u(u), oct(-1) { }
note::note(float f) : freq(f > 0 ? f : 0)
{
	utilities u;
	midiId = -1;
	oct = u.GetOctaveFromFreq(freq);
}
note::note(utilities const& u, float f) : u(u)
{	
	midiId = -1;	
	freq = f > 0 ? f : 0;	
	oct = u.GetOctaveFromFreq(freq);
}
note::note(utilities const& u, int midi) : midiId(midi), u(u)
{	
	freq = u.GetMIDIFreq(midi);
	name = u.GetNameFromMIDI(midi);
	oct = u.GetOctaveFromMIDI(midi);
}

#pragma region Getters

float note::GetFreq() const
{
	return freq;
}

int note::GetMIDI() const
{
	return midiId;
}

#pragma endregion Getters

#pragma region Setters

void note::SetFreq(float f)
{
	freq = f > 0 ? f : 0;
}

void note::SetMIDI(int m)
{
	try
	{
		if (m < 0 || m > 127)
			throw int(0);
		else
		{
			midiId = m;
			freq = u.GetMIDIFreq(m);
		}					
	}
	
	catch (int const& e)
	{
		if (e==0)
			cerr << "Value out of range! (MIDI val should be between 0 and 127)" << endl;
	}
}

#pragma endregion Setters

#pragma region Operations

bool note::IsNull() const
{
	return freq <= 0;
}
bool note::IsNull(note const& a) const
{
	return a.freq <= 0;
}
bool note::IsEqual(note const& b) const
{
	return freq == b.freq;
}
bool note::IsEqual(float const& f) const
{
	return freq == f;
}
bool note::IsGreater(note const& b) const
{
	return freq > b.freq;
}
bool note::IsGreater(float const& f) const
{
	return freq > f;
}
bool note::IsShorter(note const& b) const
{
	return freq < b.freq;
}
bool note::IsShorter(float const& f) const
{
	return freq < f;
}
note note::Add(note const& b) const
{
	note addition;
	addition.freq = freq + b.freq;
	if (midiId > -1 && b.midiId > -1)
		addition.midiId = midiId + b.midiId;
	return addition;
}
note note::Add(float const& b) const
{
	note addition;
	addition.freq = freq + b;
	return addition;
}
note note::Subtract(note const& b) const
{
	note subtraction;
	subtraction.freq = freq - b.freq > 0 ? freq - b.freq : 0;
	if (midiId > -1 && b.midiId > -1)
		subtraction.midiId = midiId - b.midiId > 0 ? midiId - b.midiId : 0;
	return subtraction;
}
note note::Subtract(float const& b) const
{
	note subtraction;
	subtraction.freq = freq - b > 0 ? freq - b : 0;
	return subtraction;
}
note note::Multiply(note const& b) const
{
	note multiply;
	multiply.freq = freq * b.freq;
	return multiply;
}
note note::Multiply(float const& b) const
{
	note multiply;
	multiply.freq = freq * b;
	return multiply;
}
note note::Divide(note const& b) const
{
	note divide;
	divide.freq = b.freq > 0 ? freq / b.freq : 20000;
	return divide;
}
note note::Divide(float const& b) const
{
	note divide;
	divide.freq = b > 0 ? freq / b : 20000;
	return divide;
}

#pragma endregion Operations

#pragma region Operators

note& note::operator++()
{
	if (midiId < 0)
		Tune();
	++midiId;
	freq = u.GetMIDIFreq(midiId);

	return *this;
}
note& note::operator++(int)
{
	if (midiId < 0)
		Tune();
	midiId++;
	freq = u.GetMIDIFreq(midiId);
	return *this;
}
note& note::operator--()
{
	if (midiId < 0)
		Tune();
	--midiId;
	freq = u.GetMIDIFreq(midiId);
	return *this;
}
note& note::operator--(int)
{
	if (midiId < 0)
		Tune();
	midiId--;
	freq = u.GetMIDIFreq(midiId);
	return *this;
}
note& note::operator=(note const& a)
{
	freq = a.freq;
	midiId = a.midiId;	
	return *this;
}
note& note::operator=(int const& a)
{
	if (a >= 0 || a < 128)
	{
		midiId = a;
		freq = u.GetMIDIFreq(a);
	}
	else
	{
		throw string("Invalid MIDI number!");
	}
	return *this;
}
note& note::operator+=(note const& b)
{
	freq = freq + b.freq;
	if (midiId > -1 && b.midiId > -1)
		midiId = midiId + b.midiId;
	return *this;
}
note& note::operator-=(note const& b)
{
	freq = freq - b.freq > 0 ? freq - b.freq : 0;
	if (midiId > -1 && b.midiId > -1)
		midiId = midiId - b.midiId > 0 ? midiId - b.midiId : 0;
	return *this;
}
note& note::operator*=(note const& b)
{
	freq = freq * b.freq;
	return *this;
}
note& note::operator/=(note const& b)
{
	freq = b.freq > 0 ? freq / b.freq : 20000;
	return *this;
}
note& note::operator+=(float const& b)
{
	freq = freq + b;
	return *this;
}
note& note::operator-=(float const& b)
{
	freq = freq - b > 0 ? freq - b : 0;
	return *this;
}
note& note::operator*=(float const& b)
{
	freq = freq * b;
	return *this;
}
note& note::operator/=(float const& b)
{
	freq = b > 0 ? freq / b : 20000;
	return *this;
}
bool operator==(note const& a, note const& b)
{
	return a.IsEqual(b);
}
bool operator!=(note const& a, note const& b)
{
	return !(a == b);
}
bool operator>(note const& a, note const& b)
{
	return a.IsGreater(b);
}
bool operator<(note const& a, note const& b)
{
	return a.IsShorter(b);
}
bool operator>=(note const& a, note const& b)
{
	return (a > b) || (a == b);
}
bool operator<=(note const& a, note const& b)
{
	return (a < b) || (a == b);
}
bool operator==(note const& a, float const& b)
{
	return a.IsEqual(b);
}
bool operator!=(note const& a, float const& b)
{
	return !(a == b);
}
bool operator>(note const& a, float const& b)
{
	return a.IsGreater(b);
}
bool operator<(note const& a, float const& b)
{
	return a.IsShorter(b);
}
bool operator>=(note const& a, float const& b)
{
	return (a > b) || (a == b);
}
bool operator<=(note const& a, float const& b)
{
	return (a < b) || (a == b);
}
note operator+(note const& a, note const& b)
{
	return a.Add(b);
}
note operator-(note const& a, note const& b)
{
	return a.Subtract(b);
}
note operator*(note const& a, note const& b)
{
	return a.Multiply(b);
}
note operator/(note const& a, note const& b)
{
	return a.Divide(b);
}
note operator+(note const& a, float const& b)
{
	return a.Add(b);
}
note operator-(note const& a, float const& b)
{
	return a.Subtract(b);
}
note operator*(note const& a, float const& b)
{
	return a.Multiply(b);
}
note operator/(note const& a, float const& b)
{
	return a.Divide(b);
}
note max(note const& a, note const& b)
{
	return a >= b ? a : b;
}
note min(note const& a, note const& b)
{
	return a <= b ? a : b;
}

#pragma endregion Operators

/// <summary>
/// tunes the note to the nearest note in a 12 tone equal temperament (12-TET) where A4 = 440Hz
/// </summary>
void note::Tune()
{	
	midiId = u.GetMIDIValue(freq);
	freq = u.GetMIDIFreq(midiId);
}

bool note::IsTuned() const
{
	return midiId > -1;
}
