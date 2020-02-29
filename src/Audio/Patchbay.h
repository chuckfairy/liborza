/**
 * Audio host
 *
 */
#pragma once

#include "Host.h"
#include "Plugin.h"
#include "PatchbayEffects.h"


namespace Audio {


class Patchbay : public Host {

    public:

        vector<Plugin*> getActivePlugins() {

            return _ActivePlugins;

        };

        /**
         * Audio Effects
         */

        PatchbayEffects * getEffects() {
			return _PatchbayEffects;
		}


    protected:

        vector<Plugin*> _Plugins;

        vector<Plugin*> _ActivePlugins;

        vector<Plugin*> _ActiveEffects;


        /**
         * Patchbay effects rack
         */

        PatchbayEffects * _PatchbayEffects;

};

};
