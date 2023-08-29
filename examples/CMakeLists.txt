message(STATUS "Examples: CXXFLAGS: ${CMAKE_CXX_FLAGS}")

list(APPEND GUM_LIBRARIES ${CMAKE_THREAD_LIBS_INIT})

 
        list(APPEND GUM_LIBRARIES ${PROJECT_NAME}) 
        if(GUMESSENTIALS_FOUND)
            list(APPEND GUM_LIBRARIES ${GUMESSENTIALS_LIBRARIES})
        else()
            message(FATAL_ERROR Library for GUMESSENTIALS cannot not found)
        endif() 
        if(GUMMATHS_FOUND)
            list(APPEND GUM_LIBRARIES ${GUMMATHS_LIBRARIES})
        else()
            message(FATAL_ERROR Library for GUMMATHS cannot not found)
        endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src/)
 
    if(GUMESSENTIALS_FOUND)
            include_directories(${GUMESSENTIALS_INCLUDE_DIRS})
        else()
            message(FATAL_ERROR Library for GUMESSENTIALS cannot not found)
        endif() 
    if(GUMMATHS_FOUND)
            include_directories(${GUMMATHS_INCLUDE_DIRS})
        else()
            message(FATAL_ERROR Library for GUMMATHS cannot not found)
        endif()

link_directories(${CMAKE_BINARY_DIR}/src/)

add_definitions(-DEXAMPLES_PATH=\"${CMAKE_SOURCE_DIR}/examples\")

set(EXAMPLE_FILE_LIST )

foreach(EXAMPLE ${EXAMPLE_FILE_LIST})
    message(STATUS "Adding target ${EXAMPLE}")
    add_executable(Example_${EXAMPLE} "./${EXAMPLE}.cpp")
    target_link_libraries(Example_${EXAMPLE} "${GUM_LIBRARIES}")
endforeach()
