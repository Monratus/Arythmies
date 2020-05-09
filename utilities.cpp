#include "utilities.h"
#include "iostream"
#include <string>
#include <random>
using namespace std;


/// <summary>
/// <para>! DOES NOT COMBINE MODULATION !</para>
/// <para>Drives a sound with an emotion.</para>
/// <para>tonicity drives the modulation's frequency and the chord's compression </para>
/// <para>direction drives the wave shape</para>
/// <para>value drives the chord's nature and randomizes the modulation's frequency</para>
/// </summary>
/// <param name="emo">the driving emotion</param>
/// <param name="baseChord">the chord, which is the set of notes we are hearing</param>
/// <param name="mod">The modulating sound</param>
/// <returns>the combined sound</returns>
sound utilities::EmotionToSound(float* t, emotion emo, chord baseChord, oscillator& mod)
{
	sound out;	
	float randomness;
	string nat;

	float ego = (float)emo.destination / 255;
	float value = (float)emo.value / 255;
	float tonicity = (float)emo.tonicity / 255;
	
	// direction
	oscillator::signal waveShape;
	if (ego < 0.5) waveShape = oscillator::signal::sine;
	else if (ego < 0.75) waveShape = oscillator::signal::triangle;
	else waveShape = oscillator::signal::ramp;

	// value
	randomness = 1 - value;
	if (value > 0.6) nat = "";
	else if (value > 0.5) nat = "sus4";
	else if (value > 0.4) nat = "sus2";
	else nat = "m";

	randomness = (1 - value)*((rand() % 100 - 50)/100);

	// tonicity
	if (tonicity > 0.4)	nat += value > 0.6 ? "M7" : "7";
	if (tonicity > 0.5)	nat += (value > 0.35) ? "9" : "b9" ;	
	if (tonicity > 0.7)	nat += "11";
	if (tonicity > 0.8)	nat += "b13";
	if (tonicity > 0.9)	baseChord.Compress();

	// Combine
	mod.SetFreq(1 + randomness + 1.5 * tonicity);

	return baseChord.ToSound(t, waveShape);
}

/// <summary>
/// <para>! DOES NOT COMBINE MODULATION !</para>
/// <para>Drives a sound with an emotion.</para>
/// <para>tonicity drives the modulation's frequency and the chord's compression </para>
/// <para>direction drives the wave shape</para>
/// <para>value drives the chord's nature and randomizes the modulation's frequency</para>
/// </summary>
/// <param name="emo">the driving emotion</param>
/// <param name="rootNote">the root note the output chord is based upon</param>
/// <param name="mod">The modulating sound</param>
/// <returns>the combined sound</returns>
sound utilities::EmotionToSound(float* t, emotion emo, note rootNote, oscillator& mod)
{
	sound out;
	float randomness;
	string nat;
	chord baseChord(rootNote);

	float ego = (float)emo.destination / 255;
	float value = (float)emo.value / 255;
	float tonicity = (float)emo.tonicity / 255;

	// direction
	oscillator::signal waveShape;
	if (ego < 0.5) waveShape = oscillator::signal::sine;
	else if (ego < 0.75) waveShape = oscillator::signal::triangle;
	else waveShape = oscillator::signal::ramp;

	// value
	if (value > 0.6) nat = "";
	else if (value > 0.5) nat = "sus4";
	else if (value > 0.4) nat = "sus2";
	else nat = "m";


	// tonicity
	if (tonicity > 0.4)	nat += value > 0.6 ? "M7" : "7";
	if (tonicity > 0.5)	nat += (value > 0.35) ? "9" : "b9";
	if (tonicity > 0.7)	nat += "11";
	if (tonicity > 0.8)	nat += "b13";
	baseChord.SetNature(nat);
	if (tonicity > 0.9)	baseChord.Compress();


	return baseChord.ToSound(t, waveShape);
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