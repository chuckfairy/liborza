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

		virtual void sendEvent( Port * port, Orza::Midi::Event * ) {};

		virtual Port * createInputPort(const char * name) {};
		virtual Port * createOutputPort(const char * name) {};

		virtual void clearPort(Port *) {};
};

};

