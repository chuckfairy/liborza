/**
 * Loaded plugins search grab
 */
#pragma once

#include <Audio/Plugin.h>
#include <Audio/Search.h>

using std::vector;

using Audio::Plugin;
using Audio::Search;

namespace Orza { namespace PluginSearch {

/**
 * Main class
 */

class LoadedPlugins {

    public:

        LoadedPlugins() {};

        /**
         * API
         */

        static void load();

        static void update();

        static vector<Plugin*> getAllGlobal();

        static void addSearch( Search * );

        static LoadedPlugins * getInstance();


        /**
         * Class methods
         */

        vector<Plugin*> getAll();

        vector<Plugin*> getMidiInstruments();

        vector<Plugin*> getAudioEffects();

        Plugin * getById( const char * id );


        /**
         * Search getters
         */
        static vector<Search*> getAllSearches();


    private:

        void addVector( vector<Plugin*> source, vector<Plugin*> dest );

        static vector<Plugin*> ALL_PLUGINS;

        static vector<Search*> PLUGIN_SEARCHS;

        static LoadedPlugins * RESOURCE;

};

}; };
