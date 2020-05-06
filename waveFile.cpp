#include <iostream>
#include <fstream>
#include <string>
#include "waveFile.h"


//.WAV files are little-endian, so we have to specify that. this
namespace little_endian_io
{
	template <typename Word>
	std::ostream& write_word(std::ostream& outs, Word value, unsigned size = sizeof(Word))
	{
		for (; size; --size, value >>= 8)
			outs.put(static_cast <char> (value & 0xFF));
		return outs;
	}
}
using namespace little_endian_io;
using namespace std;

waveFile::waveFile(ofstream& stream) : stream(stream), fs(44100), duration(0)
{
	WriteHeader();
}



/// <summary>
/// Fills up the incomplete PCM header of the .wav file
/// </summary>
void waveFile::WriteHeader()
{	
	try 
	{
		if (!stream)
			throw string("ERROR: Cannot access file");
		else
		{
			stream << "RIFF----WAVEfmt ";     // (chunk size to be filled in later)
			write_word(stream, 16, 4);  // no extension data
			write_word(stream, 1, 2);  // AUDIO FORMAT -- PCM - integer samples
			write_word(stream, 2, 2);  // CHANNEL NUMBER -- two channels (stereo file)
			write_word(stream, 44100, 4);  // SAMPLING FREQUENCY -- 44100 Hz
			write_word(stream, 176400, 4);  // BYTES PER SECOND -- (Sample Rate * BitsPerSample * Channels) / 8
			write_word(stream, 4, 2);  // BYTES PER BLOC -- size of two integer samples, one for each channel, in bytes
			write_word(stream, 16, 2);  // BITS PER SAMPLE -- Here, in 16 bits

			// Write the data chunk header
			data_chunk_pos = stream.tellp();
			stream << "data----";  // (chunk size to be filled in later)
		}
	}
	catch (string const& e)
	{
		cerr << e << endl;
	}
}

/// <summary>
/// Updates the PCM header of the .wav file
/// </summary>
void waveFile::UpdateHeader()
{
	try
	{
		if (!stream)
			throw string("ERROR: Cannot access file");
		else
		{
			// We'll need the final file size to fix the chunk sizes
			size_t file_length = stream.tellp();

			// Fix the data chunk header to contain the data size
			stream.seekp(data_chunk_pos + 4);
			write_word(stream, file_length - data_chunk_pos + 8);

			// Fix the file header to contain the proper RIFF chunk size, which is (file size - 8) bytes
			stream.seekp(0 + 4);
			write_word(stream, file_length - 8, 4);
		}
	}
	catch (string const& e)
	{
		cerr << e << endl;
	}
}

/// <summary>
/// Writes a sample value in the .wav file on both channel
/// </summary>
/// <param name="left">left channel value</param>
/// <param name="right">right channel value</param>
void waveFile::Write(int left, int right)
{
	try
	{
		if (!stream)
			throw string("ERROR: Cannot access file");
		else
		{
			if (left > 32768 || right > 32768 || left < -32767 || right < -32767)
			{
				throw string("ERROR: Sample value out of bounds");
			}
			else
			{
				write_word(stream, left, 2); // Left channel
				write_word(stream, right, 2); // Right channel
			}		
		}
	}
	catch (string const& e)
	{
		cerr << e << endl;
	}
}

void waveFile::Close()
{
	UpdateHeader();
}

#pragma region Getters

/// <summary>
/// Returns the number of sound samples in the file (fs*T)
/// </summary>
/// <returns>N, the total number of samples in the file</returns>
int waveFile::Size() const
{
	return (int)fs * duration;
}

/// <summary>
/// Gets the sampling frequency in Hz (typically 44100Hz)
/// </summary>
/// <returns>fs in Hz</returns>
float waveFile::GetSamplingFrequency() const
{
	return fs;
}

/// <summary>
/// Gets the total duration of the audio clip in seconds
/// </summary>
/// <returns>the duration, in seconds</returns>
float waveFile::GetTimeLength() const
{
	return duration;
}

#pragma endregion Getters

#pragma region Setters

/*
/// <summary>
/// Sets the sampling frequency
/// </summary>
/// <param name="f"></param>
void waveFile::SetSamplingFrequency(float f)
{
	fs = f;
}
*/

/// <summary>
/// Sets the length of the audio clip in seconds
/// </summary>
/// <param name="t">total length, in seconds</param>
void waveFile::SetTimeLength(float t)
{
	duration = t;
}

#pragma endregion Setters

