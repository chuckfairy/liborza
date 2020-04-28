/**
 * Abstract server
 *
 */
#pragma once

#include <Util/Dispatcher.h>
#include "ControlInterface.h"
#include "Patchbay.h"

#include "MidiHost.h"

namespace Audio {


class Server : public Util::Dispatcher, public ControlInterface {

	public:

		virtual void start() {};

		virtual void stop() {};

		virtual bool connect() { return false; };

		virtual MidiHost * getMidiHost() {};

		Patchbay * getPatchbay() {
			return _Patchbay;
		};

	protected:

		Server() {};
		~Server() {};

		const char * _name;
		const char * _clientName;

		Patchbay * _Patchbay;

};

};
