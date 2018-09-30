# Common lib
project(liborza-common CXX)


# Main config

set( ORZA_DATA_PATH "../data" )

configure_file(Config/Config.h.in Config/Config.h)

configure_file(Config/PluginTypes.h.in Config/PluginTypes.h)


#set( LIBORZA_GUI_INCLUDE_FILES )
file( GLOB
    LIBORZA_COMMON_INCLUDE_FILES
    "*.cpp"
    "*.h"

    "Util/Dispatcher.h"

    "Audio/Plugin.cpp"
    "Audio/Plugin.h"
    "Audio/Search.cpp"
    "Audio/Search.h"
    "Audio/Port.h"

    "Midi/Device.h"

)


## Building
# create liborza-gui library
add_library( liborza-common SHARED ${LIBORZA_COMMON_INCLUDE_FILES} )

target_link_libraries( liborza-common dl )

#target_include_directories( liborza-common PUBLIC LV2 )

target_link_libraries( liborza-common )

target_include_directories( liborza-common PUBLIC )

set_target_properties(liborza-common PROPERTIES LINKER_LANGUAGE CXX)


## Installing
# add installation for target farweller

install( TARGETS
   liborza-common
   EXPORT liborza-common
   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)

add_subdirectory( Audio )
add_subdirectory( Jack )
add_subdirectory( LV2 )
add_subdirectory( Midi )
add_subdirectory( Network )
add_subdirectory( PluginSearch )
