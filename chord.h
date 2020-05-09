#ifndef DEF_CHORD
#define DEF_CHORD

#include <vector>
#include <string>
#include "note.h"
#include "oscillator.h"


/// <summary>
/// <para>
/// This class describes a chord, which is a set of notes.
/// </para>
/// <para>
/// Each note is ID-ed in the chord depending on its function.
/// </para>
/// <para>
/// When normalized on a 12-TET, a chord can be described by its nature.
/// </para>
/// </summary>
class chord
{
	public:
		chord();
		chord(note r);
		chord(note r, std::vector<int> const& map);
		chord(std::vector<note> const& notes);
		chord(note r, std::string const& nat);
		
		note GetRoot() const;
		std::string GetNature() const;		
		std::vector<note> GetNotes() const;
		std::vector<int> GetChordMap() const;
		
		void SetChordMap(std::vector<int> const& newMap);
		void SetNature(std::string const& newNat);
		void SetNotes(std::vector<note> const& newNotes);

		void Sort();
		void Tune();		
		void Transpose(note const& newRoot);
		void Compress();
		void Harmonize();

		sound ToSound(float* t, oscillator::signal waveShape = oscillator::signal::sine, float ratio = 0.5);		

		chord Add(chord const& b) const;
		chord Add(note const& b) const;
		chord& operator+=(chord const& b);
		chord& operator+=(note const& b);

	private:		
		enum natItem {empty, m, sus2, sus4, M6, m7, M7, b5, d5, b9, M9, d9, j11, d11, m13, M13 };
		void UpdateFromNature();
		void UpdateFromChordMap();
		void UpdateFromNotes();
		bool CheckNatureSyntax();
		natItem ToNatItem(std::string const& input);
		note root;
		std::vector<int> chordMap;
		std::vector<note> notes;
		std::string nature;
		
};

chord operator+(chord const& a, chord const& b);
chord operator+(chord const& a, note const& b);

#endif