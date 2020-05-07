#ifndef DEF_UTILITIES
#define DEF_UTILITIES

#include "sound.h"
#include "chord.h"
#include "emotion.h"

/// <summary>
/// Contains various methods performing various tasks on the signal
/// </summary>
class utilities
{
	public:
		static sound EmotionToSound(emotion emo, chord baseChord, sound mod);
};

#endif