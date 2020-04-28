# Audio common lib
project(liborza-common-audio CXX)


file( GLOB
    LIBORZA_AUDIO_INCLUDE_FILES
    "Config/*.h"
    "*.h"
    "*.cpp"
)

include_directories( "${CMAKE_CURRENT_BINARY_DIR}" "../" )

# Configure app data path

add_definitions(-DORZA_DATA_PATH=${ORZA_DATA_PATH})

if( "${ORZA_DATA_PATH}" STREQUAL "" )
    set( LIBORZA_DATA_PATH "${LIBORZA_ROOT_PATH}/data" )
endif()

configure_file(Config/Config.h.in Config/Config.h)

include_directories(
	${CMAKE_CURRENT_BINARY_DIR}
	"../"
)


## Building
# create liborza-gui library
add_library(liborza-common-audio STATIC ${LIBORZA_AUDIO_INCLUDE_FILES} )

set_target_properties(liborza-common-audio PROPERTIES LINKER_LANGUAGE CXX)


## Installing
# add installation for target farweller

#install(TARGETS liborza-common-audio
    #DESTINATION "${LIBORZA_LIB_PATH}"
#)

install( TARGETS
   liborza-common-audio
   EXPORT liborza-common-audio
   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)


# copy public include files
#install(FILES
    #${LIBORZA_GUI_INCLUDE_FILES}
    #DESTINATION ${LIBORZA_LIB_PATH}/liborza-common-audio)


## create export file which can be imported by other cmake projects
#install(EXPORT liborza-common-audio_export
    #NAMESPACE sample::
    #DESTINATION lib/cmake/liborza-common-audio_lib
    #)
