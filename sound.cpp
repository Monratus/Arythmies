#include "sound.h"
#include <cmath>

int constexpr levelMax = 32760;

#pragma region Constructors

sound::sound() : level(16380), t(0), value(0) { }
sound::sound(float* t) : level(16380), t(t), value(0) { }
sound::sound(float lvl, float* t) : t(t), value(0)
{
	if (lvl > 0)
	{
		if (lvl < levelMax)
			level = lvl;
		else
			level = levelMax;
	}
	else
		level = 0;
}

#pragma endregion Constructors

#pragma region Getters

/// <summary>
/// Gets the current sample's value
/// </summary>
/// <returns></returns>
double sound::GetValue() const
{
	return value;
}

/// <summary>
/// Gets the sound's level in dB
/// </summary>
/// <returns>the level in dB </returns>
float sound::GetLevel() const
{
	return 20*log10(level/levelMax);
}


#pragma endregion Getters

#pragma region Setters

void sound::SetValue(double val)
{
	if (val > levelMax)
		value = levelMax;
	else if (val < -levelMax)
		value = -levelMax;
	else
		value = val;
}

/// <summary>
/// Sets the signal level in dB
/// </summary>
/// <param name="v">level in dB (0 is the max)</param>
void sound::SetLevel(float v)
{
	level = v >= 0 ? levelMax : pow(10, v/20) * levelMax;
}

#pragma endregion Setters

#pragma region Operations

bool sound::IsEqual(sound const& b) const
{
	return (value == b.value);
}
bool sound::IsEqual(float const& b) const
{
	return (value == b);
}
bool sound::IsGreater(sound const& b) const
{
	return (value > b.value);
}
bool sound::IsGreater(float const& b) const
{
	return (value > b);
}
bool sound::IsShorter(sound const& b) const
{
	return (value < b.value);
}
bool sound::IsShorter(float const& b) const
{
	return (value < b);
}

sound sound::Add(sound const& b) const
{
	sound addition(t);
	int maxLvl = level > b.level ? level : b.level;
	int sumLvl = level + b.level;
	// We need to re-normalize the sound after the addition.
	addition.value = (value + b.value)*maxLvl/sumLvl;
	addition.level = maxLvl;
	return addition;
}
sound sound::Add(float const& b) const
{
	sound addition(t);
	int maxLvl = level > b ? level : b;
	int sumLvl = level + b;
	// We need to re-normalize the sound after the addition.
	addition.value = (value + b) * maxLvl / sumLvl;
	addition.level = maxLvl;
	return addition;
}
sound sound::Subtract(sound const& b) const
{
	sound subtraction(t);
	int maxLvl = level > b.level ? level : b.level;
	int subLvl = level - b.level;
	// We need to re-normalize the sound after the addition.
	subtraction.value = (value - b.value) * maxLvl / subLvl;
	subtraction.level = maxLvl;
	return subtraction;
}
sound sound::Subtract(float const& b) const
{
	sound subtraction(t);
	int maxLvl = level > b ? level : b;
	int subLvl = level - b;
	// We need to re-normalize the sound after the addition.
	subtraction.value = (value - b) * maxLvl / subLvl;
	subtraction.level = maxLvl;
	return subtraction;
}
sound sound::Multiply(sound const& b) const
{
	sound multiplication(t);

	int maxLvl = level > b.level ? level : b.level;
	int productLvl = level * b.level;
	multiplication.value = value * b.value * maxLvl/productLvl;
	multiplication.level = maxLvl;

	return multiplication;
}
sound sound::Multiply(float const& b) const
{
	sound multiplication(t);

	int maxLvl = level > b ? level : b;
	int productLvl = level * b;
	multiplication.value = value * b * maxLvl / productLvl;
	multiplication.level = maxLvl;

	return multiplication;
}
sound sound::Multiply(envelope& b) const
{
	sound multiplication(t);
	
	int productLvl = level * b.GetLevel();
	multiplication.value = value * b.GetLevel();
	multiplication.level = productLvl;

	return multiplication;
}
sound sound::Divide(sound const& b) const
{
	sound division(t);

	int maxLvl = level > b.level ? level : b.level;
	int quotientLvl = level / b.level;
	if (b.value == 0)
		division.value = maxLvl;
	else
		division.value = (value / b.value)*(maxLvl / quotientLvl);
	division.level = maxLvl;

	return division;
}
sound sound::Divide(float const& b) const
{
	sound division(t);

	int maxLvl = level > b ? level : b;
	int quotientLvl = level / b;
	if (b == 0)
		division.value = maxLvl;
	else
		division.value = (value / b) * (maxLvl / quotientLvl);
	division.level = maxLvl;

	return division;
}

#pragma endregion Operations

#pragma region Operators

bool operator==(sound const& a, sound const& b)
{
	return a.IsEqual(b);
}
bool operator==(sound const& a, float const& b)
{
	return a.IsEqual(b);
}
bool operator!=(sound const& a, sound const& b)
{
	return !a.IsEqual(b);
}
bool operator!=(sound const& a, float const& b)
{
	return !(a==b);
}
bool operator>(sound const& a, sound const& b)
{
	return a.IsGreater(b);
}
bool operator>(sound const& a, float const& b)
{
	return a.IsGreater(b);
}
bool operator<(sound const& a, sound const& b)
{
	return a.IsShorter(b);
}
bool operator<(sound const& a, float const& b)
{
	return a.IsShorter(b);
}
bool operator>=(sound const& a, sound const& b)
{
	return (a > b || a==b);
}
bool operator>=(sound const& a, float const& b)
{
	return (a > b || a == b);
}
bool operator<=(sound const& a, sound const& b)
{
	return (a < b || a == b);
}
bool operator<=(sound const& a, float const& b)
{
	return (a < b || a == b);
}

sound& sound::operator+=(sound const& b)
{
	int maxLvl = level > b.level ? level : b.level;
	int sumLvl = level + b.level;
	// We need to re-normalize the sound after the addition.
	value = (value + b.value) * maxLvl / sumLvl;
	level = maxLvl;
	return *this;
}
sound& sound::operator-=(sound const& b)
{
	int maxLvl = level > b.level ? level : b.level;
	int difLvl = level - b.level;
	// We need to re-normalize the sound after the addition.
	value = (value - b.value) * maxLvl / difLvl;
	level = maxLvl;
	return *this;
}
sound& sound::operator*=(sound const& b)
{
	int maxLvl = level > b.level ? level : b.level;
	int productLvl = level * b.level;
	value = value * b.value * maxLvl / productLvl;
	level = maxLvl;
	
	return *this;
}
sound& sound::operator/=(sound const& b)
{
	int maxLvl = level > b.level ? level : b.level;
	int quotientLvl = level / b.level;
	if (b.value == 0)
		value = maxLvl;
	else
		value = (value / b.value) * (maxLvl / quotientLvl);
	level = maxLvl;
	
	return *this;
}
sound& sound::operator+=(float const& b)
{
	int maxLvl = level > b ? level : b;
	int sumLvl = level + b;
	// We need to re-normalize the sound after the addition.
	value = (value + b) * maxLvl / sumLvl;
	level = maxLvl;
	return *this;
}
sound& sound::operator-=(float const& b)
{
	int maxLvl = level > b ? level : b;
	int difLvl = level - b;
	// We need to re-normalize the sound after the addition.
	value = (value - b) * maxLvl / difLvl;
	level = maxLvl;
	return *this;
}
sound& sound::operator*=(float const& b)
{
	int maxLvl = level > b ? level : b;
	int productLvl = level * b;
	value = value * b * maxLvl / productLvl;
	level = maxLvl;

	return *this;
}
sound& sound::operator/=(float const& b)
{
	int maxLvl = level > b ? level : b;
	int quotientLvl = level / b;
	if (b == 0)
		value = maxLvl;
	else
		value = (value / b) * (maxLvl / quotientLvl);
	level = maxLvl;

	return *this;
}

sound operator+(sound const& a, sound const& b)
{
	return a.Add(b);
}
sound operator+(sound const& a, float const& b)
{
	return a.Add(b);
}
sound operator-(sound const& a, sound const& b)
{
	return a.Subtract(b);
}
sound operator-(sound const& a, float const& b)
{
	return a.Subtract(b);
}
sound operator*(sound const& a, sound const& b)
{
	return a.Multiply(b);
}
sound operator*(sound const& a, float const& b)
{
	return a.Multiply(b);
}
sound operator*(sound const& a, envelope& e)
{
	return a.Multiply(e);
}
sound operator/(sound const& a, sound const& b)
{
	return a.Divide(b);
}
sound operator/(sound const& a, float const& b)
{
	return a.Divide(b);
}

sound max(sound const& a, sound const& b)
{
	return a >= b ? a : b;
}
sound min(sound const& a, sound const& b)
{
	return a <= b ? a : b;
}

#pragma endregion Operators


void sound::Update()
{

}