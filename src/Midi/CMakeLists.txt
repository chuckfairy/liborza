
# midi configuration

set( counter 21 )
set( LIBORZA_MIDI_NUMBER_MAX 150 )

set( LIBORZA_MIDI_CONTROL_MIN 14 )
set( LIBORZA_MIDI_CONTROL_MAX 31 )

set( LIBORZA_MIDI_LETER_NAMES
    "A"
    "As"
    "B"
    "C"
    "Cs"
    "D"
    "Ds"
    "E"
    "F"
    "Fs"
    "G"
    "Gs"
)

set( LIBORZA_MIDI_NAMES_DEFINITION "" )
set( LIBORZA_MIDI_NAMES_ARRAY "" )
set( LIBORZA_MIDI_NAME_LAST "" )

foreach( octave RANGE 10 )

    # midi name

    foreach( midi_name ${LIBORZA_MIDI_LETER_NAMES} )

        # Name def

        set( note_name "${midi_name}${octave}" )

        if( ${counter} MATCHES "${LIBORZA_MIDI_NUMBER_MAX}" )
            break()
        endif()

        set( note_definition_name "\t${note_name} = ${counter},\n" )

        set( LIBORZA_MIDI_NAMES_ARRAY "${LIBORZA_MIDI_NAMES_ARRAY}${note_definition_name}" )

        MATH( EXPR counter "${counter} + 1" )

        set( LIBORZA_MIDI_NAME_LAST "${note_name}" )

    endforeach()

endforeach()

configure_file( Note.h.in Note.h)


# Frequency config

set( LIBORZA_FREQUENCY_DEFAULT_A4 "440" )

configure_file( Config/Frequency.h.in Config/Frequency.h)


# Midi Control config

set( LIBORZA_MIDI_CONTROLS_DEFINITION "" )

foreach( control_num RANGE ${LIBORZA_MIDI_CONTROL_MIN} ${LIBORZA_MIDI_CONTROL_MAX} )

    set( control_definition_name "\tCONTROL_${control_num} = ${control_num},\n" )

    set( LIBORZA_MIDI_CONTROLS_DEFINITION "${LIBORZA_MIDI_CONTROLS_DEFINITION}${control_definition_name}" )

endforeach()

configure_file( Control.h.in Control.h)
