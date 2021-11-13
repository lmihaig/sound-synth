cmake_minimum_required(VERSION 3.0.0)
project(sound-synth VERSION 0.1.0)

include(CTest)
enable_testing()


add_subdirectory(external/portaudio EXCLUDE_FROM_ALL)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(${PROJECT_NAME} main.cpp ${SRC_FILES})

target_include_directories(${PROJECT_NAME}
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include 
        PUBLIC external/portaudio/include)

target_link_directories(${PROJECT_NAME}
        PRIVATE external/portaudio)

target_link_libraries(${PROJECT_NAME} PortAudio)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
