# project
project(liborza-common-plugin CXX)

# Main files

file( GLOB LIBORZA_PLUGIN_SEARCH_INCLUDE_FILES
    "*.cpp"
)


## Building
add_library(liborza-common-plugin STATIC ${LIBORZA_PLUGIN_SEARCH_INCLUDE_FILES} )

set_target_properties(liborza-common-plugin PROPERTIES LINKER_LANGUAGE CXX)


## Installing
# add installation for target farweller

install(TARGETS liborza-common-plugin
    DESTINATION "${LIBORZA_LIB_PATH}"
)


# LV2 Check

if( LIBORZA_HAS_LV2 )

    set( LIBORZA_PLUGIN_SEARCH_INCLUDE_DIRS
        ${LIBORZA_LV2_INCLUDE_DIRS}
        ${LIBORZA_ROOT_PATH}
        ${LIBORZA_ROOT_PATH}/lib-src/lilv
        ${LIBORZA_ROOT_PATH}/lib-src/suil
        ${LIBORZA_ROOT_PATH}/lib-src/sord
        ${LIBORZA_ROOT_PATH}/lib-src/serd
        ${LIBORZA_ROOT_PATH}/lib-src/sratom
        ".."
    )

    set( LIBORZA_PLUGIN_SEARCH_LINK_LIBRARIES
        "liborza-common-lv2"
    )

endif()


# Setup

target_link_libraries( liborza-common-plugin
    liborza-common-audio
    liborza-common-jack
    ${LIBORZA_PLUGIN_SEARCH_LINK_LIBRARIES}
)

target_include_directories( liborza-common-plugin PUBLIC
    ".."
    ${LIBORZA_PLUGIN_SEARCH_INCLUDE_DIRS}
    ${LIBORZA_SRC_PATH}
    ${CMAKE_CURRENT_BINARY_DIR}
)

install( TARGETS
   liborza-common-plugin

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
