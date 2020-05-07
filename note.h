#ifndef DEF_NOTE
#define DEF_NOTE

#include <string>
#include "utilities.h"


class note
{
	public:
		note();		
		note(utilities const& u);
		note(float f);
		note(utilities const& u, float f);
		note(utilities const& u, int midi);

		void Tune();
		bool IsTuned() const;

		float GetFreq() const;
		void SetFreq(float f);
		int GetMIDI() const;
		void SetMIDI(int m);		

		bool IsNull() const;
		bool IsNull(note const& a) const;
		bool IsEqual(note const& b) const;
		bool IsEqual(float const& f) const;
		bool IsGreater(note const& b) const;
		bool IsGreater(float const& f) const;
		bool IsShorter(note const& b) const;
		bool IsShorter(float const& b) const;
		note Add(note const& b) const;
		note Add(float const& b) const;
		note Subtract(note const& b) const;
		note Subtract(float const& b) const;
		note Multiply(note const& b) const;
		note Multiply(float const& b) const;
		note Divide(note const& b) const;
		note Divide(float const& b) const;
		note& operator++();
		note& operator++(int);
		note& operator--();
		note& operator--(int);
		note& operator=(note const& a);
		note& operator=(int const& a);
		note& operator+=(note const& a);
		note& operator-=(note const& a);
		note& operator*=(note const& a);
		note& operator/=(note const& a);
		note& operator+=(float const& a);
		note& operator-=(float const& a);
		note& operator*=(float const& a);
		note& operator/=(float const& a);

	private:		
		float freq;
		int midiId;		
		std::string name;
		int oct;
		utilities const u;
		
};

bool operator==(note const& a, note const& b);
bool operator!=(note const& a, note const& b);
bool operator>(note const& a, note const& b);
bool operator<(note const& a, note const& b);
bool operator>=(note const& a, note const& b);
bool operator<=(note const& a, note const& b);
bool operator==(note const& a, float const& b);
bool operator!=(note const& a, float const& b);
bool operator>(note const& a, float const& b);
bool operator<(note const& a, float const& b);
bool operator>=(note const& a, float const& b);
bool operator<=(note const& a, float const& b);

note operator+(note const& a, note const& b);
note operator-(note const& a, note const& b);
note operator*(note const& a, note const& b);
note operator/(note const& a, note const& b);
note operator+(note const& a, float const& b);
note operator-(note const& a, float const& b);
note operator*(note const& a, float const& b);
note operator/(note const& a, float const& b);


note max(note const& a, note const& b);
note min(note const& a, note const& b);

#endif




