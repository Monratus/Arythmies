#ifndef DEF_ENVELOPE
#define DEF_ENVELOPE


class envelope
{
	public:
		enum stage { None, Attack, Decay, Sustain, Release };

		envelope(float* time, float attack = 0.2, float decay = 0.2, float sustain = 0.5, float release = 0.4);

		float GetAttack() const;
		void SetAttack(float a);

		float GetDecay() const;
		void SetDecay(float d);

		float GetSustain() const;
		void SetSustain(float s);

		float GetRelease() const;
		void SetRelease(float r);

		float GetLevel();
		stage GetCurrentStage() const;

		void SetGate(float g);

		envelope Add(envelope const& e) const;
		envelope Subtract(envelope const& e) const;
		envelope Multiply(envelope const& e) const;

		envelope& operator+=(envelope const& e);
		envelope& operator-=(envelope const& e);
		envelope& operator*=(envelope const& e);		

	private:		
		stage currentStage;
		float gate;
		float gateUpTime; // time key of the last time trigger was set to true
		float gateDownTime; // time key of the last time gate went back to 0
		float _attack; // time taken to get from 0 to 1
		float _decay; // time take to get from 1 to the sustained level
		float _sustain; // sustain level
		float _release; // time to get from the sustained level back to 0		
		float level;		
		float* t; // time in s
		
		void Update();
		void UpdateStage();
};

envelope operator+(envelope const& a, envelope const& b);
envelope operator-(envelope const& a, envelope const& b);
envelope operator*(envelope const& a, envelope const& b);

#endif