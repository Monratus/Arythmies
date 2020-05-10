#ifndef DEF_SOUND
#define DEF_SOUND


class sound
{		
	public:
		sound();		
		sound(float* t);
		sound(float vol, float* t);		
		

		double GetValue() const;	
		void SetValue(double val);
		float GetLevel() const;
		void SetLevel(float vol);


		bool IsEqual(sound const& b) const;		
		bool IsEqual(float const& b) const;
		bool IsGreater(sound const& b) const;		
		bool IsGreater(float const& b) const;
		bool IsShorter(sound const& b) const;		
		bool IsShorter(float const& b) const;
		sound Add(sound const& b) const;		
		sound Add(float const& b) const;
		sound Subtract(sound const& b) const;		
		sound Subtract(float const& b) const;
		sound Multiply(sound const& b) const;
		sound Multiply(float const& b) const;
		sound Divide(sound const& b) const;
		sound Divide(float const& b) const;
		sound& operator+=(sound const& b);
		sound& operator-=(sound const& b);
		sound& operator*=(sound const& b);
		sound& operator/=(sound const& b);
		sound& operator+=(float const& b);
		sound& operator-=(float const& b);
		sound& operator*=(float const& b);
		sound& operator/=(float const& b);
			
		virtual void Update();
		
		int level;
		float* t; // time in s
		double value;
};

bool operator==(sound const& a, sound const& b);
bool operator!=(sound const& a, sound const& b);
bool operator>(sound const& a, sound const& b);
bool operator<(sound const& a, sound const& b);
bool operator>=(sound const& a, sound const& b);
bool operator<=(sound const& a, sound const& b);
bool operator==(sound const& a, float const& b);
bool operator!=(sound const& a, float const& b);
bool operator>(sound const& a, float const& b);
bool operator<(sound const& a, float const& b);
bool operator>=(sound const& a, float const& b);
bool operator<=(sound const& a, float const& b);

sound operator+(sound const& a, sound const& b);
sound operator+(sound const& a, float const& b);
sound operator-(sound const& a, sound const& b);
sound operator-(sound const& a, float const& b); 
sound operator*(sound const& a, sound const& b);
sound operator*(sound const& a, float const& b); 
sound operator/(sound const& a, sound const& b);
sound operator/(sound const& a, float const& b);

sound max(sound const& a, sound const& b);

sound min(sound const& a, sound const& b);


#endif