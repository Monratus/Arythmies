#define _USE_MATH_DEFINES

#include <cmath>
#include "note.h"
#include "oscillator.h"

#pragma region Constructors

oscillator::oscillator(float f, float* time) : sound(time), waveShape(signal(sine)), freq(f), ratio(0.5) { }
oscillator::oscillator(note const& n, float* time) : sound(time), waveShape(signal(sine)), freq(n.GetFreq()), ratio(0.5) { }
oscillator::oscillator(signal shape, float f, float *time) : sound(time), waveShape(shape), freq(f), ratio(0.5) { }
oscillator::oscillator(signal shape, note const& n, float* time) : sound(time), waveShape(shape), freq(n.GetFreq()), ratio(0.5) { }
oscillator::oscillator(signal shape, float f, float *time, float ratio) : sound(time), waveShape(shape), freq(f), ratio(ratio) { }
oscillator::oscillator(signal shape, note const& n, float* time, float ratio) : sound(time), waveShape(shape), freq(n.GetFreq()), ratio(ratio) { }

#pragma endregion Constructors

#pragma region Getters

/// <summary>
/// Gets the oscillator ratio's value (0.5 by default)
/// </summary>
/// <returns>current ratio's value</returns>
float oscillator::GetRatio() const
{
	return ratio;
}

/// <summary>
/// Gets the oscillator's current frequency in Hz (220Hz by default)
/// </summary>
/// <returns>current frequency</returns>
float oscillator::GetFreq() const
{
	return freq;
}

/// <summary>
/// Gets the oscillator's current wave shape (sine by default)
/// </summary>
/// <returns>current wave shape</returns>
oscillator::signal oscillator::GetWaveShape() const
{
	return waveShape;
}

#pragma endregion Getters

#pragma region Setters

/// <summary>
/// Sets the osillator ratio's value. Does not change sine waves.
/// </summary>
/// <param name="value">new value</param>
void oscillator::SetRatio(float value)
{
	ratio = value;
}

/// <summary>
/// Sets the oscillator's frequency
/// </summary>
/// <param name="f">new frequency (Hz)</param>
void oscillator::SetFreq(float f)
{
	freq = f;	
}

/// <summary>
/// Sets the oscilator's type
/// </summary>
/// <param name="shape">new wave shape (sine, triangle, ramp or square)</param>
void oscillator::SetWaveShape(signal shape)
{
	waveShape = shape;
}

#pragma endregion Setters

/// <summary>
/// get the value for the sample at t seconds for the specified oscillator.
/// </summary>
/// <returns>the sample's value</returns>
void oscillator::Update()
{
	switch (waveShape)
	{
	case sine:
		SetValue(level * sin(2 * M_PI * freq * *t));
		break;

	case triangle: // y = 2(Af/r)t - A OR y = 2(Af/(r-1))t + A 
		// there is clipping when r ~= 0.5, so for this particular we take the absolute value of a sawtooth wave and normalize it again 
		if (ratio >= 0.498 || ratio <= 0.502)
			SetValue(2 * abs(2 * (double)level * (double)freq * fmod((double)* t, (double)(1 / freq)) - level) - level);
		else
			SetValue(fmod(*t, 1 / freq) < ratio / freq ? 2 * (double)level * ((double)freq / ratio) * fmod((double)* t, (double)(1 / freq)) - level : 2 * (double)level * ((double)freq / (ratio - 1)) * fmod((double)* t, (double)(1 / freq)) + level);
		break;

	case ramp: // y = 2Aft - A
		SetValue(2 * (double)level * (double)freq * fmod((double)* t, (double)(1 / freq)) - level);
		break;

	case square:
		SetValue(fmod(*t, 1 / freq) < ratio / freq ? level : -level);
		break;
	}
}