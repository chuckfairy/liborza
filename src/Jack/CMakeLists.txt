project(liborza-common-jack CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")

find_package( JACK )
#find_package( liborza-common )
set_package_properties( JACK PROPERTIES TYPE REQUIRED PURPOSE "Enables JACK plugin" )


file( GLOB
    LIBORZA_JACK_INCLUDE_FILES
    "../Midi/*.cpp"
    "*.cpp"
    "*.h"
    "Events/*.cpp"
    "Resource/*.cpp"
)


## Building
# create liborza-backend-common library
add_library( liborza-common-jack STATIC ${LIBORZA_JACK_INCLUDE_FILES} )


target_link_libraries( liborza-common-jack PUBLIC
    #asound
    liborza-common-audio
    jack
)

include_directories( liborza-common-jack INSTALL_INTERFACE "../" )

set_target_properties( liborza-common-jack PROPERTIES LINKER_LANGUAGE CXX )

#install(TARGETS liborza-common-jack EXPORT liborza-common-jack-export
    #RUNTIME DESTINATION bin
    #ARCHIVE DESTINATION lib
    #LIBRARY DESTINATION lib
    #DESTINATION "${LIBORZA_LIB_PATH}"
    #INCLUDES DESTINATION include
#)

#set_target_properties(liborza-common-jack PROPERTIES INSTALL_RPATH_USE_LINK_PATH TRUE)

install( TARGETS
   liborza-common-jack
   EXPORT liborza-common-jack
   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
