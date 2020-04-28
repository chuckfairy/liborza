/**
 * Jack midi host
 */
#include "Midi.h"
#include "Server.h"
#include "Port.h"

#include <Midi/Events.h>

using Orza::Midi::ControlNumber;
using Orza::Midi::CONTROL_NUMBER_MIN;
using Orza::Midi::CONTROL_NUMBER_MAX;

namespace Jack {

/**
 * Forwarding
 */

class Server;


/**
 * Main class
 */

Midi::Midi( Server * s ) : Host( s ) {

    _Server = s;

};


/**
 * Consts
 */

const char * Midi::ALL_EVENTS = "all";

const int Midi::EVENT_CONTROL_CHANGE = 0xb0;
const int Midi::EVENT_NOTE_ON = 0x90;
const int Midi::EVENT_NOTE_OFF = 0x80;


/**
 * Get ports by input type JackPortIsOutput
 */

vector<Port> Midi::getMidiPorts() {

    return _Server->getAudio()->getPortsByType( JackPortIsOutput, JACK_DEFAULT_MIDI_TYPE );

};


/**
 * Get midi control ports
 */

vector<MidiControlPort*> Midi::getMidiControlPorts() {

    vector<MidiControlPort*> ports;

    //@TODO fix return to be port pointers or move midi ports to repo

    static vector<Port> jackPorts = getMidiPorts();

    vector<Port>::iterator it;

    //ports loop

    for( int size = 0; size < jackPorts.size(); ++ size ) {

        Port * p = static_cast<Port*>(&jackPorts[ size ]);

        //Loop control numbers

        for( int itNum = CONTROL_NUMBER_MIN; itNum <= CONTROL_NUMBER_MAX; ++ itNum ) {

            ControlNumber num = static_cast<ControlNumber>( itNum );

            ports.push_back( new MidiControlPort( p, num ) );

        }

    }

    return ports;

};


/**
 * Main port adders
 */

void Midi::addInput( jack_port_t * port ) {

    _inputPorts.push_back( port );

    vector<jack_port_t*>::iterator it;

    for( it = _outputPorts.begin(); it != _outputPorts.end(); ++ it ) {

        std::cout << "MIDI ADDING MIDI \n\n";

        std::cout <<
            jack_port_name( *it )
            << " "
            << jack_port_name( port )
        ;

        connectJackPort(
            jack_port_name( *it ),
            jack_port_name( port )
        );

    }

};

void Midi::addOutput( jack_port_t * port ) {

    _outputPorts.push_back( port );

    vector<jack_port_t*>::iterator it;

    for( it = _inputPorts.begin(); it != _inputPorts.end(); ++ it ) {

        connectJackPort(
            jack_port_name( port ),
            jack_port_name( *it )
        );

    }

};


/**
 * Midi default connect from main port getter
 */

void Midi::connectDefaults() {

    vector<Port> ports = getMidiPorts();

    if( ports.empty() ) { return; }

    int size = ports.size();

    while( -- size ) {

        addOutput( ports[ size ].jack_port );

    }

};


/**
 * Update
 */

void Midi::update( jack_nframes_t nframes ) {

    updateEvents( nframes );

};


/**
 * Update midi events and listeners
 */

void Midi::updateEvents( jack_nframes_t nframes ) {

    vector<jack_port_t*>::iterator it;

    for( it = _outputPorts.begin(); it != _outputPorts.end(); ++ it ) {

        updateEventPort( nframes, (*it) );

    }

};


/**
 * Update midi events if any for a port
 */

void Midi::updateEventPort( jack_nframes_t nframes, jack_port_t * port ) {

    void * buf = jack_port_get_buffer( port, nframes );

    if( ! buf ) { return; }

    for( uint32_t i = 0; i < jack_midi_get_event_count( buf ); ++ i ) {

        jack_midi_event_t jackEvent;
        int recevied = jack_midi_event_get( &jackEvent, buf, i );

        //Create check event

        if( recevied != 0 ) { continue; }


        MidiEvent * event = new MidiEvent( &jackEvent );

        if( event->type == Orza::Midi::EVENT_UNKNOWN ) { continue; }


        //Handle event

        handleEvent( event );

        dispatch( jack_port_name( port ), (void*) (event) );

    }

};


/**
 * Send orza midi event to jack
 */
void Midi::sendEvent( Audio::Port * port, Orza::Midi::Event * event ) {

	Jack::Port * jackPort = (Jack::Port*) port;

	void* port_buf = jack_port_get_buffer(jackPort->jack_port, event->frames);

	//Create buffer
	unsigned char * buffer = jack_midi_event_reserve(
		port_buf,
		event->frames,
		3
	);

	switch (event->type) {
		case Orza::Midi::EVENT_NOTE_ON:
			buffer[2] = event->velocity;
			buffer[1] = event->pitch;
			buffer[0] = EVENT_NOTE_ON;
			break;

		case Orza::Midi::EVENT_NOTE_OFF:
			buffer[2] = event->velocity;
			buffer[1] = event->pitch;
			buffer[0] = EVENT_NOTE_OFF;
			break;

		case Orza::Midi::EVENT_CONTROL_CHANGE:
			buffer[2] = event->controlValue;
			buffer[1] = event->controlNumber;
			buffer[0] = EVENT_CONTROL_CHANGE;
			break;

		default:
			break;
	}
};


/**
 * Port creation
 */

Audio::Port * Midi::createInputPort(const char * name) {
	Port * port = (Port*) createPort(name);

	port->jack_port = jack_port_register(
		_jackClient,
		name,
		JACK_DEFAULT_MIDI_TYPE,
		JackPortIsInput,
		0
	);

	return port;
};

Audio::Port * Midi::createOutputPort(const char * name) {
	Port * port = (Port*) createPort(name);

	port->jack_port = jack_port_register(
		_jackClient,
		name,
		JACK_DEFAULT_MIDI_TYPE,
		JackPortIsOutput,
		0
	);

	return port;
};


Audio::Port * Midi::createPort(const char * name) {
	Port * port = new Port();

	port->isAudio = false;
	port->isInput = true;
	port->nameString = name;
	port->name = port->nameString.c_str();

	return port;

};

void Midi::clearPort(Audio::Port * port) {
	Jack::Port * jackPort = (Jack::Port*) port;
	void* port_buf = jack_port_get_buffer(jackPort->jack_port, 1);
	jack_midi_clear_buffer(port_buf);
}



/**
 * Handle event
 */

void Midi::handleEvent( MidiEvent * event ) {

    void * mesg = (void *) event;

    dispatch( ALL_EVENTS, event );

    dispatch( event->getTypeName(), event );

};

};
