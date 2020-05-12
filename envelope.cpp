#include "envelope.h"
#include <iostream>
using namespace std;

#pragma region Constructors

envelope::envelope(float* time, float attack, float decay, float sustain, float release) : t(time)
{ 
	 _attack = attack > 0 ? attack : 0;	
	_decay = decay > 0 ? decay : 0;
	if (sustain > 1) _sustain = 1;
	else if (sustain < 0) _sustain = 0;
	else _sustain = sustain;
	_release = release > 0 ? release : 0;

	level = 0;
	gate = 0;
	gateUpTime = 0;
	gateDownTime = 0;
	currentStage = None;
}

#pragma endregion Constructors

#pragma region Getters

float envelope::GetAttack() const
{
	return _attack;
}
float envelope::GetDecay() const
{
	return _decay;
}
float envelope::GetSustain() const
{
	return _sustain;
}
float envelope::GetRelease() const
{
	return _release;
}
float envelope::GetLevel()
{
	Update();
	return level;
}
envelope::stage envelope::GetCurrentStage() const
{
	return currentStage;
}

#pragma endregion Getters

#pragma region Setters

void envelope::SetAttack(float a)
{
	_attack = a;
}
void envelope::SetDecay(float d)
{
	_decay = d;
}
void envelope::SetSustain(float s)
{
	_sustain = s;
}
void envelope::SetRelease(float r)
{
	_release = r;
}
void envelope::SetGate(float g)
{
	if (g > 0.1 && gate <= 0.2)
	{
		gateUpTime = *t;
		//cout << "Up :" << gateUpTime << endl;
	}
	else if (g <= 0.1 && gate > 0.2)
	{
		gateDownTime = *t;
		//cout << "Down :" << gateDownTime << endl;;
	}
	gate = g;
}

#pragma endregion Setters

#pragma region Public Methods

envelope envelope::Add(envelope const& e) const
{
	return envelope(t, _attack + e._attack, _decay + e._decay, _sustain + e._sustain, _release + e._release);
}
envelope envelope::Subtract(envelope const& e) const
{
	return envelope(t, _attack - e._attack, _decay - e._decay, _sustain - e._sustain, _release - e._release);
}
envelope envelope::Multiply(envelope const& e) const
{
	return envelope(t, _attack * e._attack, _decay * e._decay, _sustain * e._sustain, _release * e._release);
}

#pragma endregion Public Methods

#pragma region Private Methods

/// <summary>
/// <para>Updates the envelope level value</para>
/// </summary>
void envelope::Update()
{
	UpdateStage();
	switch (currentStage)
	{
	case None:
		level = 0;
		break;

	case Sustain:
		level = gate * _sustain;
		break;

	case Release:
		level = _sustain - (_sustain / _release) * (*t - gateDownTime);
		break;

	case Attack:
		level = gate * (1 / _attack) * (*t - gateUpTime);
		break;

	case Decay:
		level = gate * (1 - ((1 - _sustain) / _decay) * (*t - (gateUpTime + _attack)));
		break;
	}
}

void envelope::UpdateStage()
{
	if (gate > 0)
	{
		if (*t - gateUpTime < _attack) currentStage = Attack;
		else if (*t - gateUpTime < _attack + _decay) currentStage = Decay;
		else currentStage = Sustain;
	}
	else if (gate <= 0 && *t - gateDownTime < _release && *t > _release) currentStage = Release;
	else currentStage = None;
}

#pragma endregion Private Methods

#pragma region Operators

envelope& envelope::operator+=(envelope const& e)
{
	_attack += e._attack;
	_decay += e._decay;
	_sustain += e._sustain;
	_release += e._release;

	return *this;
}
envelope& envelope::operator-=(envelope const& e)
{
	_attack -= e._attack;
	_decay -= e._decay;
	_sustain -= e._sustain;
	_release -= e._release;

	return *this;
}
envelope& envelope::operator*=(envelope const& e)
{
	_attack *= e._attack;
	_decay *= e._decay;
	_sustain *= e._sustain;
	_release *= e._release;
	
	return *this;
}
envelope operator+(envelope const& a, envelope const& b)
{
	return a.Add(b);
}
envelope operator-(envelope const& a, envelope const& b)
{
	return a.Subtract(b);
}
envelope operator*(envelope const& a, envelope const& b)
{
	return a.Multiply(b);
}

#pragma endregion Operators