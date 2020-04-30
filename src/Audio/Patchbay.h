/**
 * Audio host
 *
 */
#pragma once

#include "Host.h"
#include "Plugin.h"
#include "PatchbayEffects.h"
#include "ControlInterface.h"
#include "PluginPortContainer.h"
#include <Util/Vector.h>


namespace Audio {


class Patchbay : public Host, public ControlInterface {

	public:

		//Virtuals
		virtual vector<Audio::Plugin*> getAllPlugins() {

			vector<Audio::Plugin*> output;

			Util::Vector::append( &output, _ActivePlugins );
			Util::Vector::append( &output, _PatchbayEffects->getRepo()->getAll<Audio::Plugin>() );

			return output;

		};

		vector<Plugin*> getActivePlugins() {

			return _ActivePlugins;

		};

		virtual void addPlugin(Plugin *) {};

		virtual void clearPlugins() {};

		/**
		 * Audio Effects
		 */

		PatchbayEffects * getEffects() {
			return _PatchbayEffects;
		}

		vector<Audio::PluginPortContainer*> getPluginPortContainers() {
			vector<Audio::Plugin*> plugins = getAllPlugins();
			vector<Audio::Plugin*>::iterator it;

			vector<Audio::PluginPortContainer*> output;

			for( it = plugins.begin(); it != plugins.end(); ++ it ) {

				Audio::Plugin * p = (Audio::Plugin*) (*it);

				vector<Audio::Port*> ports = p->getPortsFromIndex( p->getControlPorts() );
				vector<Audio::Port*>::iterator portsIt;

				for( portsIt = ports.begin(); portsIt != ports.end(); ++ portsIt ) {

					output.push_back(
						new Audio::PluginPortContainer( p, (*portsIt) )
					);

				}

			}

			return output;

		}


	protected:
		Patchbay() {}

		Patchbay( PatchbayEffects * p ) :
			_PatchbayEffects(p)
		{};

		~Patchbay() {}

		vector<Plugin*> _Plugins;

		vector<Plugin*> _ActivePlugins;

		vector<Plugin*> _ActiveEffects;

		/**
		 * Patchbay effects rack
		 */

		PatchbayEffects * _PatchbayEffects;

};

};
