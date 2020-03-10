/**
 * Note and frequency helpers
 *
 * http://newt.phys.unsw.edu.au/jw/notes.html
 */
#pragma once

#include <iostream>
#include "Config/Frequency.h"
#include <Midi/Note.h>

namespace Orza { namespace Midi { namespace Frequency {

/**
 * Base frequency of A0 from A4
 */

inline const float_t getBaseFrequency(
	const float_t A4Frequency
) {

	//Assume 4 octaves making 2^4 == 16

	return A4Frequency / 16;

};

inline float_t getFrequencyDistance(
	float_t frequency,
	float_t other
) {
	return abs(frequency - other);
}


/**
 * Get frequencies from a midi note
 */

//inline float_t getFromNote(
	//const NoteNumber midiNote,
	//const float_t A4Frequency = DEFAULT_A4
//) {
	//const int midi = static_cast<int>(midiNote);

	//return getFromNote( midi, A4Frequency );

//};

/**
 * Get frequencies from a midi note int
 */

inline float_t getFromNote(
	int midiNote,
	float_t A4Frequency = DEFAULT_A4
) {

	const float_t A0Frequency = getBaseFrequency( A4Frequency );

	int midiWithMin =  midiNote - 21;
	float power = powf( 2.0, (float)midiWithMin / 12 );

	float_t output = A0Frequency * power;

	return output;

};

inline float_t getNoteFromFrequency(
	float_t frequency,
	float_t A4Frequency = DEFAULT_A4
) {
	int current = 0;
	float_t distance = 100 * 100;

	for( int i = 21; i < 157; ++i ) {
		float_t note = getFromNote(i);

		float_t thisDistance = getFrequencyDistance(frequency, note);

		if( thisDistance <= distance ) {
			current = i;
			distance = thisDistance;
		}

		if( note >= frequency ) {
			break;
		}
	}

	return current - 21;
}

}; }; };
