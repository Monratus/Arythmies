#include "utilities.h"
#include "iostream"
#include <string>
#include <random>
using namespace std;


/// <summary>
/// <para>Creates a chord based on an emotion</para>
/// <para>value : changes the actual nature of the chord (major/minor)</para>
/// <para>tonicity : adds extensions to the chord</para>
/// </summary>
/// <param name="emo">the driving emotion</param>
/// <param name="rootNote">the root note of the output chord</param>
/// <returns>a chord</returns>
chord utilities::EmotionToChord(emotion emo, note rootNote)
{	
	string nat;
	chord baseChord(rootNote);

	float ego = (float)emo.destination / 255;
	float value = (float)emo.value / 255;
	float tonicity = (float)emo.tonicity / 255;

	// value
	if (value > 0.6) nat = "";
	else if (value > 0.5) nat = "sus4";
	else if (value > 0.4) nat = "sus2";
	else nat = "m";


	// tonicity
	if (tonicity > 0.4)
	{
		if (value > 0.6)	nat += "M7";
		else if (value > 0.3)	nat += "7";
		else nat += "6M7";
	}
	if (tonicity > 0.5)	nat += (value > 0.35) ? "9" : "b9";
	if (tonicity > 0.7)	nat += (value > 0.35) ? "11" : "#11";
	if (tonicity > 0.8)	nat += "b13";
	baseChord.SetNature(nat);
	if (tonicity > 0.9 && value < 0.2)	baseChord.Compress();
	
	return baseChord;
}

/// <summary>
/// drives an oscillator's signal shape with an emotion
/// </summary>
/// <param name="emo">the driving emotion</param>
/// <returns>an oscillator signal</returns>
oscillator::signal utilities::EmotionToWaveShape(emotion emo)
{
	float ego = (float)emo.destination / 255;

	// direction
	oscillator::signal waveShape;
	if (ego < 0.5) waveShape = oscillator::signal::sine;
	else if (ego < 0.75) waveShape = oscillator::signal::triangle;
	else waveShape = oscillator::signal::ramp;

	return waveShape;
}

/// <summary>
/// <para>Drives a pulse signal with an emotion</para>
/// <para>Tonicity drives the speed</para>
/// <para>Value drives the randomness</para>
/// </summary>
/// <param name="t">time pointer to drive the oscillator</param>
/// <param name="emo">the emotion</param>
/// <returns>a pulse oscillator</returns>
oscillator utilities::EmotionToPulse(float* t, emotion emo, float lowFreq)
{
	float value = (float)emo.value / 255;
	float tonicity = (float)emo.tonicity / 255;

	oscillator pulse(oscillator::signal::pulse, lowFreq + 1.5 * tonicity, t);
	pulse.SetRandomnessLfo(1 - value);

	return pulse;
}

/// <summary>
/// <para>Drives a modulation signal with an emotion</para>
/// <para>Tonicity drives the speed</para>
/// </summary>
/// <param name="t">time pointer to drive the oscillator</param>
/// <param name="emo">the emotion</param>
/// <returns>a sine oscillator</returns>
oscillator utilities::EmotionToModulation(float* t, emotion emo, float lowFreq)
{
	float tonicity = (float)emo.tonicity / 255;

	oscillator mod(oscillator::signal::sine, lowFreq + 3.5 * tonicity, t);

	return mod;
}

emotion utilities::EmotionalState(utilities::emotionalStates state)
{
	emotion emo;
	switch (state)
	{
		case E1:
			emo.tonicity = emo.MAX;
			emo.value = 0;
			emo.destination = emo.MAX;
			break;
		case E2:
			emo.tonicity = emo.MAX;
			emo.value = emo.MAX;
			emo.destination = emo.MAX;
			break;
		case E3:
			emo.tonicity = emo.MAX;
			emo.value = 0;
			emo.destination = 0;
			break;
		case E4:
			emo.tonicity = emo.MAX;
			emo.value = emo.MAX;
			emo.destination = 0;
			break;
		case E5:
			emo.tonicity = 0;
			emo.value = 0;
			emo.destination = emo.MAX;
			break;
		case E6:
			emo.tonicity = 0;
			emo.value = emo.MAX;
			emo.destination = emo.MAX;
			break;
		case E7:
			emo.tonicity = 0;
			emo.value = 0;
			emo.destination = 0;
			break;
		case E8:
			emo.tonicity = 0;
			emo.value = emo.MAX;
			emo.destination = 0;
			break;
	}

	return emo;
}