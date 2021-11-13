cmake_minimum_required(VERSION 3.12.0)
project(sound-synth VERSION 0.1.0)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY artifacts)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY artifacts)

# Find and update submodules
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
        option(GIT_SUBMODULE "Check submodules during build" ON)
        if(GIT_SUBMODULE)
                message(STATUS "Submodule update")
                execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                                RESULT_VARIABLE GIT_SUBMOD_RESULT)
                if(NOT GIT_SUBMOD_RESULT EQUAL "0")
                        message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}")
                endif()
        endif()
endif()

add_subdirectory(external/portaudio EXCLUDE_FROM_ALL)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(${PROJECT_NAME} main.cpp ${SRC_FILES})

target_include_directories(${PROJECT_NAME}
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include 
        PUBLIC external/portaudio/include)

target_link_directories(${PROJECT_NAME}
        PRIVATE build/external/portaudio)

target_link_libraries(${PROJECT_NAME} PortAudio)

