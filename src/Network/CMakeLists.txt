# network common lib
project(liborza-common-network CXX)


file( GLOB
    LIBORZA_NETWORK_INCLUDE_FILES
    "*.cpp"
)

include_directories( "${CMAKE_CURRENT_BINARY_DIR}" "../" )


## Building
# create liborza-gui library
add_library(liborza-common-network STATIC ${LIBORZA_NETWORK_INCLUDE_FILES} )

target_link_libraries(liborza-common-network PUBLIC iw)

set_target_properties(liborza-common-network PROPERTIES LINKER_LANGUAGE CXX)


install( TARGETS
   liborza-common-network
   EXPORT liborza-common-network
   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
