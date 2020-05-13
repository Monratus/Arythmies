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
						
			//A REVOIR : Écrit bien dans le fichier, mais on obtient un bruit blanc. Probablement quelque chose à voir avec t.
			// Piste : écrire les valeurs dans un fichier texte, et regarder la courbe.
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
	//regex chord_regex{ "([A-G])([m|M]|(sus4)|(sus2))?(6)?(M?7)?([b|\\#]5)?([b|\\#]?9)?([b|\\#]?11)?([b|\\#]?13)?" };
	//string chord_entry;
	//smatch m;
	//while (true)
	//{
	//	cout << "Type in a chord" << endl;
	//	cin >> chord_entry;		
	//	
	//	if (regex_match(chord_entry, m, chord_regex))
	//	{
	//		cout << "Bien!" << endl;
	//		cout << 1 << m[1] << endl;
	//		cout << 2 << m[2] << endl;
	//		cout << 3 << m[3] << endl;
	//		cout << 4 << m[4] << endl;
	//		cout << 5 << m[5] << endl;
	//		cout << 6 << m[6] << endl;
	//		cout << 7 << m[7] << endl;
	//		cout << 8 << m[8] << endl;
	//		cout << 9 << m[9] << endl;
	//		cout << 10 << m[10] << endl;
	//		cout << 11 << m[11] << endl;
	//	}
	//}
	
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

	/*****TESTS ON CHORDS (using spain)*****/
	//midi m;
	//// create the .wav file
	//ofstream stream("SoundFiles/TestChords_Spain.wav", ios::binary);
	//waveFile soundFile(stream);
	//
	//// create the chords roots	
	//note g(m, 55);
	//note a(m, 57);
	//note b(m, 59);
	//note cd(m, 61);
	//note d(m, 50);
	//note e(m, 52);
	//note fd(m, 54);
	//
	////note tierce(u, 64);
	//	
	//chord GM7(g, "M7"); // 2, 1
	//chord A7(a, "713"); // 1
	//chord B7(b, "7#9"); //1
	//chord B7b9(b, "7b9"); //1
	//chord Cd7(cd, "7#9"); // 1
	//chord DM7(d, "M79"); // 1
	//chord Em7(e, "m79"); // 1
	//chord Fd7(fd, "7b13"); // 2, 1
	//
	//// This is the time in seconds.
	//float* t(0);
	//t = new float;
	//
	//
	//sound osc(t); // this is where we combine all the oscillators to print out the sound
	//oscillator mod(2, t); // this is the modulation frequency
	//sound out(t); // the final signal
	//
	//float fs = soundFile.GetSamplingFrequency();
	//soundFile.SetTimeLength(24);
	//int left, right;
	//
	//vector<oscillator>::iterator it;
	//
	//for (int n = 0; n < soundFile.Size(); n++)
	//{
	//	*t = n / fs;
	//
	//	if (*t < 4)
	//		osc = GM7.OutputChord(t);
	//	else if (*t < 8)
	//		osc = Fd7.OutputChord(t);
	//	else if (*t < 10)			
	//		osc = Em7.OutputChord(t);
	//	else if (*t < 12)
	//		osc = A7.OutputChord(t);
	//	else if (*t < 14)
	//		osc = DM7.OutputChord(t);
	//	else if (*t < 16)
	//		osc = GM7.OutputChord(t);
	//	else if (*t < 18)
	//		osc = Cd7.OutputChord(t);
	//	else if (*t < 20)
	//		osc = Fd7.OutputChord(t);
	//	else if (*t < 22)
	//		osc = B7.OutputChord(t);
	//	else
	//		osc = B7b9.OutputChord(t);
	//
	//	mod.Update();
	//	out = osc * mod;
	//
	//	left = out.GetValue();
	//	right = left;
	//	//cout << left << endl;
	//	soundFile.Write(left, right);
	//}
	//soundFile.Close();
	//
	//delete t;
	//t = 0;

	/*****TEST ON ENVELOPES*****/
	//midi m;
	//// create the .wav file
	//ofstream stream("SoundFiles/TestBeat.wav", ios::binary);

	//waveFile soundFile(stream);

	//// create the chords roots	
	//note C(m, 36);	

	//// This is the time in seconds.
	//float* t(0);
	//t = new float;


	//oscillator osc(oscillator::signal::triangle, C, t);
	//oscillator gate(oscillator::signal::pulse, 1.5, t);
	//envelope beat(t, 0.01f, 0.02f, 0.001f, 0.01f);
	//sound out(t); // the final signal

	//float fs = soundFile.GetSamplingFrequency();
	//soundFile.SetTimeLength(5);
	//int left, right;

	//for (int n = 0; n < soundFile.Size(); n++)
	//{
	//	*t = n / fs;
	//	osc.Update();
	//	gate.Update();
	//	beat.SetGate(gate.GetValue());
	//	
	//	out = osc * beat;

	//	left = out.GetValue();
	//	right = left;
	//	//cout << left << endl;
	//	soundFile.Write(left, right);
	//}
	//soundFile.Close();

	//delete t;
	//t = 0;

	/*****OUTPUTS BASIC EMOTIONS*****/
	midi m;
	// create the .wav file
	ofstream stream("SoundFiles/Test.wav", ios::binary);

	waveFile soundFile(stream);

	
	// create the chords roots	
	note G(m, 57);
	note GLow(m, 45);
	emotion emo = utilities::EmotionalState(utilities::E2);
	chord chordEmo = utilities::EmotionToChord(emo, G);
	
	// This is the time in seconds.
	float* t(0);
	t = new float;
	
	oscillator gate = utilities::EmotionToPulse(t, emo, 1);
	oscillator mod = utilities::EmotionToModulation(t, emo, 1);
	oscillator::signal waveShape = utilities::EmotionToWaveShape(emo);
	envelope beatEnvelope(t, 0.01f, 0.02f, 0.005f, 0.02f);
	oscillator beatOsc(oscillator::signal::sine, GLow, t);
	sound osc(t);
	
	sound out(t); // the final signal
	
	float fs = soundFile.GetSamplingFrequency();
	soundFile.SetTimeLength(30);
	int left, right;
	
	for (int n = 0; n < soundFile.Size(); n++)
	{
		*t = n / fs;
		osc = chordEmo.ToSound(t, waveShape);
		gate.Update();
		beatOsc.Update();
		beatEnvelope.SetGate(gate.GetValue());
		mod.Update();
		out = osc * mod + beatOsc * beatEnvelope;
	
		left = out.GetValue();
		right = left;		
		//cout << left << endl;
		soundFile.Write(left, right);
	}
	soundFile.Close();
	
	delete t;
	t = 0;
}