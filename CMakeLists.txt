cmake_minimum_required(VERSION 3.0.0)
project(sound-synth VERSION 0.1.0)

include(ExternalProject)
include(CTest)
enable_testing()

ExternalProject_Add(project_portaudio
    GIT_REPOSITORY      https://github.com/PortAudio/portaudio.git
    PREFIX              lib/portaudio
    CONFIGURE_COMMAND   <SOURCE_DIR>/configure
    BUILD_IN_SOURCE     1
    BUILD_COMMAND       make
    INSTALL_COMMAND     echo Skipping install step for portaudio
)
ExternalProject_Get_Property(project_portaudio BINARY_DIR)
ExternalProject_Get_Property(project_portaudio SOURCE_DIR)
SET(portaudio_lib_dir "${BINARY_DIR}/lib/.libs")
SET(portaudio_inc_dir "${SOURCE_DIR}/include")

ADD_LIBRARY(portaudio STATIC IMPORTED)
SET_PROPERTY(TARGET portaudio PROPERTY IMPORTED_LOCATION "${portaudio_lib_dir}/libportaudio.a")

IF(APPLE)
   FIND_LIBRARY(CORE_AUDIO_LIBRARY CoreAudio)
   FIND_LIBRARY(AUDIO_TOOLBOX_LIBRARY AudioToolbox)
   FIND_LIBRARY(AUDIO_UNIT_LIBRARY AudioUnit)
   FIND_LIBRARY(CARBON_LIBRARY Carbon)
   SET(EXTRA_LIBS ${CORE_AUDIO_LIBRARY} ${AUDIO_TOOLBOX_LIBRARY} ${AUDIO_UNIT_LIBRARY} ${CARBON_LIBRARY})
ENDIF (APPLE)

IF(CMAKE_SYSTEM_NAME STREQUAL "Linux")
   SET(EXTRA_LIBS rt asound jack pthread)
ENDIF(CMAKE_SYSTEM_NAME STREQUAL "Linux")


file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(sound-synth main.cpp ${SRC_FILES})
target_include_directories(sound-synth PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${portaudio_inc_dir})

TARGET_LINK_LIBRARIES(sound-synth ${EXTRA_LIBS} portaudio)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
