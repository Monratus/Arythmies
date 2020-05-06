#ifndef DEF_WAVEFILE
#define DEF_WAVEFILE


#include <fstream>
#include <iostream>
#include <string>

/// <summary>
/// <para>This class allows you to write values in a stereo 16bits .WAV file.</para>
/// <para>It writes the file's header at its creation, and updates it before destruction</para>
/// </summary>
class waveFile
{
	public:
		waveFile(std::ofstream& stream);

		void Write(int left, int right);
		void Close();
		int Size() const;

		float GetSamplingFrequency() const;
		//void SetSamplingFrequency(float f);
		float GetTimeLength() const;
		void SetTimeLength(float t);

	private:		
		std::ofstream& stream;
		size_t data_chunk_pos;
		
		float fs; // sampling frequency
		float duration; // length in seconds

		void WriteHeader();
		void UpdateHeader();
};


#endif