#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include "utilities.h"
#include "oscillator.h"
#include "waveFile.h"
#include "chord.h"

using namespace std;

/*

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
*/

int main()
{
	/*

	ofstream soundFile("SoundFiles/Test.wav", ios::binary);
	//ofstream DebugLog("log.txt");
	try
	{
		if (soundFile)
		{
			// Write the file headers
			soundFile << "RIFF----WAVEfmt ";     // (chunk size to be filled in later)
			write_word(soundFile, 16, 4);  // no extension data
			write_word(soundFile, 1, 2);  // AUDIO FORMAT -- PCM - integer samples
			write_word(soundFile, 2, 2);  // CHANNEL NUMBER -- two channels (stereo file)
			write_word(soundFile, 44100, 4);  // SAMPLING FREQUENCY -- 44100 Hz
			write_word(soundFile, 176400, 4);  // BYTES PER SECOND -- (Sample Rate * BitsPerSample * Channels) / 8
			write_word(soundFile, 4, 2);  // BYTES PER BLOC -- size of two integer samples, one for each channel, in bytes
			write_word(soundFile, 16, 2);  // BITS PER SAMPLE -- use a multiple of 8

			// Write the data chunk header
			size_t data_chunk_pos = soundFile.tellp();
			soundFile << "data----";  // (chunk size to be filled in later)

			// Write the audio samples
			// (We'll generate a single C4 note with a sine wave, fading from left to right)
			constexpr double max_amplitude = 32760;  // "master volume"

			double fs = 44100;    // sampling frequency
			double frequency = 261.626;  // middle C
			double seconds = 5;      // time
						
			//A REVOIR : �crit bien dans le fichier, mais on obtient un bruit blanc. Probablement quelque chose � voir avec t.
			// Piste : �crire les valeurs dans un fichier texte, et regarder la courbe.
			float* t(0); 
			t = new float;

			//oscillator sineWave(oscillator::signal::sine, frequency, (float)max_amplitude, t);
			oscillator triWave(oscillator::signal::triangle, frequency, (float)max_amplitude, t, 0.5);
			oscillator sawWave(oscillator::signal::ramp, frequency, (float)max_amplitude, t);
			//oscillator squareWave(oscillator::signal::square, frequency, (float)max_amplitude, t);

			int N = fs * seconds;  // total number of samples
			for (int n = 0; n < N; n++)
			{
				*t = n / fs;
				//sineWave.Update();	
				triWave.Update();
				sawWave.Update();
				//squareWave.Update();

				
				write_word(soundFile, (int)triWave.GetValue(), 2); // Left channel
				write_word(soundFile, (int)triWave.GetValue(), 2); // Right channel
				//DebugLog << *t << ";" << value << endl;
			}

			delete t;

			// (We'll need the final file size to fix the chunk sizes above)
			size_t file_length = soundFile.tellp();

			// Fix the data chunk header to contain the data size
			soundFile.seekp(data_chunk_pos + 4);
			write_word(soundFile, file_length - data_chunk_pos + 8);

			// Fix the file header to contain the proper RIFF chunk size, which is (file size - 8) bytes
			soundFile.seekp(0 + 4);
			write_word(soundFile, file_length - 8, 4);
		}
		else
		{
			throw string("ERREUR: Impossible d'ecrire dans le fichier");
		}	
	}
	catch (string const& e)
	{
		cerr << e << endl;
	}

	*/

	/*****REGEX TESTS*****/

	regex chord_regex{ "(((m|M)|(sus4|sus2))?)(7?)((b|\\#)?[5913]{0,2})*" };
	string chord_entry;
	smatch m;
	while (true)
	{
		cout << "Type in a chord" << endl;
		cin >> chord_entry;		
			
		for (auto it=m.begin(); it!=m.end(); it++)
		{
			cout << m.str() << endl;
		}
			

	}


	
	/***** WRITE A CHORD IN A WAV FILE, WITH MODULATION *****/
	/*
	utilities u;

	// create the .wav file
	ofstream stream("SoundFiles/Test4_II-V-IminCompressed.wav", ios::binary);
	waveFile soundFile(stream);

	// create the chord's notes
	note C(u, 48);
	note D(u, 50);
	note G(u, 55);
	//note tierce(u, 64);
	//note quinte(u, 67);
	//note septieme(u, 71);
	vector<int> maj{ 0, 4, 7, 11, 14 };
	vector<int> min{ 0, 3, 7, 10, 14 };
	vector<int> dominante{ 0, 4, 7, 10, 14};
	vector<int> min6{ 0, 3, 9, 14, 19 };
	vector<int> min7b5{ 0, 3, 11, 13, 18 };
	vector<int> alt{ 0, 4, 11, 13, 15 };
	
	chord Cm6(C, min6);
	chord Dm7b5(D, min7b5);
	chord G7alt(G, alt);

	Cm6.Compress();
	Dm7b5.Compress();
	G7alt.Compress();

	// This is the time in seconds.
	float* t(0);
	t = new float;
	
		
	sound osc(t); // this is where we combine all the oscillators to print out the sound
	oscillator mod(2, t); // this is the modulation frequency
	sound out(t); // the final signal

	float fs = soundFile.GetSamplingFrequency();
	soundFile.SetTimeLength(8);
	int left, right;

	vector<oscillator>::iterator it;

	for (int n = 0; n < soundFile.Size(); n++)
	{
		*t = n / fs;
		
		if ( *t < 2 )
			osc = Dm7b5.OutputChord(t);
		else if ( *t < 4 )
			osc = G7alt.OutputChord(t);
		else
			osc = Cm6.OutputChord(t);

		mod.Update();
		out = osc * mod;

		left = out.GetValue();
		right = left;
		//cout << left << endl;
		soundFile.Write(left, right);
	}
	soundFile.Close();

	delete t;
	t = 0;
	*/
}