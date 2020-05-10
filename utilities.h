#ifndef DEF_UTILITIES
#define DEF_UTILITIES

#include "sound.h"
#include "chord.h"
#include "oscillator.h"
#include "emotion.h"

/// <summary>
/// Contains various methods performing various tasks on the signal
/// </summary>
class utilities
{
	public:
		static enum emotionalStates { E1, E2, E3, E4, E5, E6, E7, E8 };
		static sound EmotionToSound(float* t, emotion emo, chord baseChord, oscillator& mod);
		static sound EmotionToSound(float* t, emotion emo, note rootNote, oscillator& mod);
		static emotion EmotionalState(emotionalStates state);		
		static chord EmotionToChord(emotion emo, note rootNote);
		static oscillator::signal EmotionToWaveShape(emotion emo);
		static oscillator EmotionToPulse(float *t, emotion emo);
};

#endif