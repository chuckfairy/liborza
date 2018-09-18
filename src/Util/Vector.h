/**
 * Vector helpers
 */
#pragma once

#include <algorithm>
#include <vector>

using std::vector;

namespace Util { namespace Vector {

/**
 * Append vector to vector
 */
template<typename T>
inline void append( vector<T> * source, vector<T> dest ) {

	source->insert( std::end( *source ), std::begin( dest ), std::end( dest ) );

};

template<typename T>
inline bool has( vector<T> * items, T item ) {

	return (
		std::find( items->begin(), items->end(), item )  != items->end()
	);

};

template<typename T>
inline void remove( vector<T> * items, T removal ) {

	items->erase(
		std::remove( items->begin(), items->end(), removal ),
		items->end()
	);

};

}; };
