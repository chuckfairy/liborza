#Src test

# test project
project(liborza-tests CXX)

#Setup CMake to run tests
enable_testing()



## LADSPA Inactive ATM ###

#add_executable( ladspalist LADSPA.cpp )

# We have to link
#target_link_libraries( ladspalist
    #PUBLIC liborza-common
#)

#target_include_directories( ladspalist PUBLIC "../src/common" )

#install( TARGETS
   #ladspalist

   #RUNTIME DESTINATION bin
   #LIBRARY DESTINATION lib
   #ARCHIVE DESTINATION lib
#)
####


#Prep ourselves for compiling boost
find_package(Boost COMPONENTS unit_test_framework REQUIRED)
include_directories (${Boost_INCLUDE_DIRS})

#I like to keep test files in a separate source directory called test
file(GLOB TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    Midi/*.cpp
    Jack/*.cpp
    JSON/*.cpp
    CLI/*.cpp
)

#Run through each source
foreach(testSrc ${TEST_SRCS})
    #Extract the filename without an extension (NAME_WE)
    get_filename_component(testName ${testSrc} NAME_WE)

    #Add compile target
    add_executable(${testName} ${testSrc})

    #link to Boost libraries AND your targets and dependencies
    target_link_libraries(${testName} ${Boost_LIBRARIES}
        jack
        liborza-common-lv2 liborza-common
        liborza-common-audio
        liborza-common-jack
        liborza-common-lv2
    )

    target_include_directories( ${testName}
        PUBLIC
        "${LIBORZA_ROOT_PATH}/src"
        "${LIBORZA_ROOT_PATH}/lib-src"
        "${LIBORZA_ROOT_PATH}/lib-src/sratom"
        "${LIBORZA_ROOT_PATH}/lib-src/sord"
    )

    #I like to move testing binaries into a testBin directory
    set_target_properties(${testName} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/testBin)

    #Finally add it to test execution -
    #Notice the WORKING_DIRECTORY and COMMAND
    add_test(NAME ${testName}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/testBin
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/testBin/${testName} )
endforeach(testSrc)
