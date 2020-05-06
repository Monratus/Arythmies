#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <regex>
#include <cmath>
#include "sound.h"
#include "oscillator.h"
#include "chord.h"
#include "note.h"
#include "utilities.h"

using namespace std;

string const chordNatPattern = "((m|M)|(sus4|sus2))?7?((b|\\#)?[913]{0,2})*" ;

#pragma region Constructors

chord::chord() { }
chord::chord(note r)
{	
	root = r;
	notes.push_back(r);
	chordMap.push_back(1);
}
chord::chord(note r, vector<int> const& map) : root(r), chordMap(map) 
{ 
	UpdateFromChordMap();
}
chord::chord(vector<note> const& vals) : notes(vals) 
{ 
	if (!vals.empty)
		root = vals[0];
	UpdateFromNotes();
}
chord::chord(note r, string const& nat ) : root(r), nature(nat)
{
	UpdateFromNature();
}

#pragma endregion Constructors

#pragma region Getters

note chord::GetRoot() const
{
	return root;
}

string chord::GetNature() const
{
	return nature;
}

vector<note> chord::GetNotes() const
{
	return notes;
}

vector<int> chord::GetChordMap() const
{
	return chordMap;
}

#pragma endregion Getters

#pragma region Setters

void chord::SetChordMap(vector<int> const& newMap)
{
	chordMap = newMap;
	UpdateFromChordMap();
}

void chord::SetNature(string const& newNat)
{
	nature = newNat;
	UpdateFromNature();
}

void chord::SetNotes(vector<note> const& newNotes)
{
	notes = newNotes;
	UpdateFromNotes();
}

#pragma endregion Setters

#pragma region Public Methods

/// <summary>
/// Sorts the notes and the chordMap by pitch, setting the root as the lowest note.
/// </summary>
void chord::Sort()
{	
	sort(notes.begin(), notes.end());
	UpdateFromNotes();
}

/// <summary>
/// Shift every note of the chord on a 12-TET with A4 = 440 Hz without changing their order
/// </summary>
void chord::Tune()
{
	vector<note>::iterator it;
	for (it = notes.begin(); it != notes.end(); ++it)
	{
		(*it).Tune();
	}
	UpdateFromNotes();
}

/// <summary>
/// <para>Transposes the chord.</para>
/// <para>Sets a new root, but keeps the general harmony and nature</para>
/// </summary>
/// <param name="newRoot">new root</param>
void chord::Transpose(note const& newRoot)
{
	root = newRoot;
	UpdateFromChordMap();
}

/// <summary>
/// <para>Takes all the notes, puts them all close to each other</para>
/// <para>(to keep them warm and cosy? No, to add weight obviously</para>
/// </summary>
void chord::Compress()
{
	vector<int> newMap;

	if (!chordMap.empty)
	{
		vector<int>::iterator it;
		for (it = chordMap.begin(); it != chordMap.end(); ++it)
		{	
			newMap.push_back(*it % 12);
		}
	}
}

/// <summary>
/// <para>Basic harmonization of the chord depending of the root's frequency (1, 3, (5), 7, (5), ext)</para>
/// <para>Only works if the chord's nature is defined</para>
/// </summary>
void chord::Harmonize()
{

}

/// <summary>
/// Adds notes to the chord
/// </summary>
/// <param name="b"></param>
/// <returns>a new chord, which is the combination of the two</returns>
chord chord::Add(chord const& b) const
{
	chord addition(notes);

	vector<note>::const_iterator it;
	for (it = b.notes.begin(); it != b.notes.end(); ++it)
	{
		addition.notes.push_back(*it);
	}

	return addition;
}

/// <summary>
/// Adds notes to the chord
/// </summary>
/// <param name="b"></param>
/// <returns>a new chord, which is the combination of the two</returns>
chord chord::Add(note const& b) const
{
	chord addition(notes);

	addition.notes.push_back(b);

	return addition;
}

/// <summary>
/// Adds notes to the current chord
/// </summary>
/// <param name="b"></param>
chord& chord::operator+=(chord const& b)
{
	vector<note>::const_iterator it;
	for (it = b.notes.begin(); it != b.notes.end(); ++it)
	{
		notes.push_back(*it);
	}

	return *this;
}

/// <summary>
/// Adds notes to the current chord
/// </summary>
/// <param name="b"></param>
chord& chord::operator+=(note const& b)
{
	notes.push_back(b);
	return *this;
}

#pragma endregion Public Methods

#pragma region Private Methods

/// <summary>
/// Updates the chord's notes and note map using its nature
/// </summary>
void chord::UpdateFromNature() 
{

}

/// <summary>
/// Updates the chord's notes using its note map
/// </summary>
void chord::UpdateFromChordMap()
{
	// Reset the chord's notes
	notes.clear();
	
	if (!chordMap.empty)
	{
		// Populate notes from chordMap
		vector<int>::iterator it;
		
		for (it = chordMap.begin(); it != chordMap.end(); ++it)
		{
			// the chord map represents each note's distance from the root in semitones			
			notes.push_back(root * pow(2, (double)(*it) / 12));
		}
	}
}

/// <summary>
/// Updates the chord's map using a new set of notes if possible.
/// </summary>
void chord::UpdateFromNotes()
{

}

/// <summary>
/// Checks the nature's syntax validity using regular expressions
/// </summary>
/// <returns></returns>
bool chord::CheckNatureSyntax()
{
	return regex_match(nature, regex(chordNatPattern));
}

#pragma endregion Private Methods

#pragma region Operators

chord operator+(chord const& a, chord const& b)
{
	return a.Add(b);
}

chord operator+(chord const& a, note const& b)
{
	return a.Add(b);
}

#pragma endregion Operators