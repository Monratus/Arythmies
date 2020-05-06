#ifndef DEF_OSCILLATOR
#define DEF_OSCILLATOR


#include "sound.h"
#include "note.h"

/// <summary>
/// <para>This class is a basic oscillator capable of generating 4 different waveforms</para>
/// </summary>
class oscillator : public sound
{ 
	public:	
		enum signal { sine, triangle, ramp, square };

		oscillator();
		oscillator(float f, float* time);
		oscillator(note const& n, float* time);
		oscillator(signal shape, float f, float* time);
		oscillator(signal shape, note const& n, float* time);
		oscillator(signal shape, float f, float* time, float ratio);
		oscillator(signal shape, note const& n, float* time, float ratio);
				
		void SetRatio(float value);
		float GetRatio() const;

		void SetFreq(float value);
		float GetFreq() const;

		void SetWaveShape(signal shape);
		signal GetWaveShape() const;
			
		virtual void Update();

	private:
		signal waveShape;
		float ratio; // only used for square signals
		float freq;	
};

#endif




