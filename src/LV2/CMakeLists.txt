# LV2 cmake

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set( AUTOGEN_TARGET_DEPENDS ON )

# project
project(liborza-common-lv2 CXX)

#find_package( JACK )
find_package( Qt5Widgets REQUIRED )
find_package( Qt5Core REQUIRED )
find_package( Lilv REQUIRED )

find_package( Sord REQUIRED )
find_package( Serd REQUIRED )
find_package( Suil REQUIRED )
find_package( Sratom REQUIRED )


message( "${LIBORZA_ROOT_PATH}/lib-src/lilv/src/" )

#set( LIBORZA_LV2_INCLUDE_FILES )
file( GLOB LIBORZA_LV2_INCLUDE_FILES
    ${SRATOM_INCLUDE_FILES}
    ${SORD_INCLUDE_FILES}
    ${SERD_INCLUDE_FILES}
    ${SUIL_INCLUDE_FILES}
    ${LILV_INCLUDE_FILES}
    ${LIBORZA_JACK_INCLUDE_FILES}
    "include/*.h"
    "include/symap.c"
    "include/lv2_evbuf.c"
    "include/symap.c"
    "include/zix_thread.c"
    "Resource/*"
    "Events/JackLatencyEvent.cpp"
    "Events/JackBufferEvent.cpp"
    "Host.cpp"
    "Search.cpp"
    "JackCallbackEvent.cpp"
    "Plugin.cpp"
    "PluginWorker.cpp"
    "PluginState.cpp"
    "PluginPreset.cpp"
    "UI.cpp"
    "UI/PresetDropdown.cpp"
)


## Building
# create liborza-common-lv2 library
add_library(liborza-common-lv2 STATIC ${LIBORZA_LV2_INCLUDE_FILES} )

set_target_properties(liborza-common-lv2 PROPERTIES LINKER_LANGUAGE CXX)


## Installing
# add installation for target farweller

install(TARGETS liborza-common-lv2
    DESTINATION "${LIBORZA_LIB_PATH}"
)

set( LIBORZA_LV2_INCLUDE_DIRS
    ${LILV_INCLUDE_DIRS}
    ${SRATOM_INCLUDE_DIRS}
    ${SORD_INCLUDE_DIRS}
    ${SERD_INCLUDE_DIRS}
    ${SUIL_INCLUDE_DIRS}
)

include_directories( ${LIBORZA_LV2_INCLUDE_DIRS} )

target_link_libraries( liborza-common-lv2
    jack
    liborza-common-jack
    pthread
    pcre
    dl
    Qt5::Widgets Qt5::Core
)

target_include_directories( liborza-common-lv2 PUBLIC
	".."
	${CMAKE_CURRENT_BINARY_DIR}
	"${LIBORZA_LIB_PATH}/lilv"
	"${LIBORZA_LIB_PATH}/suil"
)

install( TARGETS
   liborza-common-lv2

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
