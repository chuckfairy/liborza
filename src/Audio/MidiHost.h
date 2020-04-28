/**
 * Audio host
 *
 */
#pragma once

#include "Port.h"
#include <Midi/Events.h>


namespace Audio {


class MidiHost {

	public:

		MidiHost() {};
		~MidiHost() {};

		virtual void addInput( Port * ) {};

		virtual void addOutput( Port * ) {};

		virtual void sendEvent( Audio::Port * port, Orza::Midi::Event * ) {};
};

};

