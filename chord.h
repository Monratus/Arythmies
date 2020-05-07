#ifndef DEF_CHORD
#define DEF_CHORD

#include <vector>
#include <string>
#include "note.h"


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

		std::vector<oscillator> OutputChord(float* t);		

		chord Add(chord const& b) const;
		chord Add(note const& b) const;
		chord& operator+=(chord const& b);
		chord& operator+=(note const& b);

	private:
		void UpdateFromNature();
		void UpdateFromChordMap();
		void UpdateFromNotes();
		bool CheckNatureSyntax();
		note root;
		std::vector<int> chordMap;
		std::vector<note> notes;
		std::string nature;
};

chord operator+(chord const& a, chord const& b);
chord operator+(chord const& a, note const& b);

#endif