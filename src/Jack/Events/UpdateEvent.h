/**
 * Callback event for jack
 *
 */
#pragma once
#include <jack/jack.h>

#include <Util/Dispatcher.h>

namespace Jack {


/**
 * Class forwarding
 *
 */
class Patchbay;


/**
 * Main dispatch, uses plugin
 *
 */

template<typename T>
class UpdateEvent : public Util::Event {


	public:

		/**
		 * Construct
		 */

		UpdateEvent( T * p ) : _Host( p ) {}

		void run( void * o ) {
			_Host->updateJack(
				(jack_nframes_t) (uintptr_t) (jack_nframes_t * ) o
			);
		}


	private:

		T * _Host;
};

};
