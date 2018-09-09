/**
 * Latency event for jack
 *
 */
#pragma once

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

class LatencyEvent : public Util::Event {

    private:

        Patchbay * _Patchbay;


    public:

        /**
         * Construct
         */

        LatencyEvent( Patchbay * p ) : _Patchbay( p ) {};

        void run( void * o );

};

};
