/**
 * Patchbay effects list and jack port connection
 *
 */
#pragma once

#include "Plugin.h"
#include <Audio/PluginRepository.h>
#include <Audio/ControlInterface.h>


namespace Audio {


/**
 * Main class
 */

class PatchbayEffects :
	public Audio::ControlInterface
{

	public:

		/**
		 * Get repo
		 */

		PluginRepository<Plugin> * getRepo() {

			if (_Repo == nullptr) {
				_Repo = new PluginRepository<Plugin>();
			}

			return _Repo;

		};


		/**
		 * Get control ports of active plugins
		 */

		vector<Audio::Port*> getControlPorts();


		/**
		 * Audio effects related
		 */

		virtual void addEffect( Audio::Plugin * p ) {};

		virtual void removeEffect( Audio::Plugin * p ) {};

		virtual void pauseEffect( Audio::Plugin * p ) {};

		virtual void clearEffects() {};


		/**
		 * Effect connectors
		 */

		virtual void connectEffectPorts() {};


	protected:

		PatchbayEffects() :
			_Repo( new PluginRepository<Plugin> )
		{
		}


		/**
		 * Prefix virtual
		 */

		virtual const char * getPrefix() {

			return "effects";

		};

		PluginRepository<Plugin> * _Repo = nullptr;

};

};


