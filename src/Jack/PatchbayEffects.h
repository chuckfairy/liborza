/**
 * Patchbay effects list and jack port connection
 *
 */
#pragma once

#include <jack/jack.h>

#include <Audio/Patchbay.h>
#include <Audio/ControlInterface.h>

#include "Host.h"
#include "Plugin.h"
#include "StereoHostInterface.h"
#include "PatchbayEffectsOutput.h"


namespace Jack {


/**
 * Class forwards
 */

class Server;


/**
 * Main class
 */

class PatchbayEffects :
	public Audio::Patchbay,
	public Audio::PatchbayEffects,
	public StereoHostInterface
{

	public:

		explicit PatchbayEffects( Server * );

		explicit PatchbayEffects( jack_client_t * );


		/**
		 * Getters
		 */

		PatchbayEffectsOutput * getPatchbayOutput() {

			return _Output;

		};


		/**
		 * Get control ports of active plugins
		 */

		vector<Audio::Port*> getControlPorts();


		/**
		 * Audio effects related
		 */

		void addEffect( Audio::Plugin * );

		void removeEffect( Audio::Plugin * );

		void pauseEffect( Audio::Plugin * );

		void clearEffects();


		/**
		 * Effect connectors
		 */

		void connectEffectPorts();


		/**
		 * Main jack updates
		 */

		void updateJack( jack_nframes_t );

		void updateJackBufferSize( jack_nframes_t );

		void updateJackLatency( jack_latency_callback_mode_t );


		/**
		 * Server set callbacks
		 */

		void setServerCallbacks();


		/**
		 * Redirect overwrite over hostinterface
		 */

		void redirectInput( jack_nframes_t );


		/**
		 * Virtuals
		 */
		bool connectInputTo( const char * out) {
			return StereoHostInterface::connectInputTo(out);
		};

		bool connectInputTo( const char * out1, const char * out2) {
			return StereoHostInterface::connectInputTo(out1, out2);
		};

		bool connectOutputTo( const char * out) {
			return StereoHostInterface::connectOutputTo(out);
		};

		bool connectOutputTo( const char * out1, const char * out2) {
			return StereoHostInterface::connectOutputTo(out1, out2);
		};

	protected:

		/**
		 * Prefix virtual
		 */

		const char * getPrefix() {

			return "effects";

		};


	private:

		Server * _Server;

		PatchbayEffectsOutput * _Output;

		void redirectEffects( jack_nframes_t );

		void disconnectEffectPorts();

};

};

