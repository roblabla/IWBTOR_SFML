#Change this if you need to target a specific CMake version
cmake_minimum_required(VERSION 2.6)
project(Platformer)

# Add our own modules
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
include(AddTargetProperty)
include(CopyDll)

# Enable debug symbols by default
# (you can also set it on the command line: -D CMAKE_BUILD_TYPE=Release)
if(CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE Debug)
endif()

# Set version information in a config.h file
set(Platformer_VERSION_MAJOR 1)
set(Platformer_VERSION_MINOR 0)
configure_file(
  "${PROJECT_SOURCE_DIR}/src/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
  )
include_directories("${PROJECT_BINARY_DIR}")

# Define sources and executable name
set(EXECUTABLE_NAME "Platformer")

set(SRCS src/main.cpp
         src/Game.cpp
         src/Game.hpp
         src/MenuState.cpp
         src/MenuState.hpp
         src/IState.hpp
         src/Settings.cpp
         src/Settings.hpp
         src/ResMan.cpp
         src/ResMan.hpp
         src/ScrollingStoryState.cpp
         src/ScrollingStoryState.hpp
         src/Utils.cpp
         src/Utils.hpp)

add_executable(${EXECUTABLE_NAME} ${SRCS})

# Make sure it compiles 32-bit
add_target_property(${EXECUTABLE_NAME} COMPILE_FLAGS "-m32")
add_target_property(${EXECUTABLE_NAME} LINK_FLAGS "-m32")

# MINGW : we should static-link libgcc, libstdc++ and winpthread.
# However, sfml link against those dynamically by default, and
# needs a recompilation to have them linked statically.
# This needs investigation.
# In case we're using mingw : static link the C++ libs for distribution.
# Maybe we should make this toggle-able with a flag ?
#if(MINGW)
#  add_target_property(${EXECUTABLE_NAME} LINK_FLAGS "")
# Eventually, SFML should be static as well.
#  set(SFML_STATIC_LIBRARIES TRUE)
#  add_definitions("-DSFML_STATIC")
#endif()

# Enable C++11 features.
# Eventually, we should check individual features.
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
  message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

# Static link pthread. Let's ask for pthread
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
find_package(Threads)
target_link_libraries(${EXECUTABLE_NAME} ${CMAKE_THREAD_LIBS_INIT})

#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED audio graphics window system)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
else()
  message(FATAL_ERROR "Could not find SFML 2.1")
endif()

# Add tinydir for filesystem
# Maybe we need a FindTinyDir ?
include_directories(${PROJECT_SOURCE_DIR}/thirdparty/tinydir)

# Add cereal for serialization
# TODO : Make a FindCereal.cmake to avoid the submodule dep
include_directories(${PROJECT_SOURCE_DIR}/thirdparty/cereal/include)

# Copy the ressources.
add_custom_command(TARGET ${EXECUTABLE_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E
                   copy_directory ${PROJECT_SOURCE_DIR}/res ${PROJECT_BINARY_DIR}/res)

# Copy the damn dlls.
# MinGW-only : Make the assumption that libstdc++ and such are next to the compiler.
if(MINGW)
  # Copy MinGW runtime dlls
  get_filename_component(MINGW_BIN_PATH ${CMAKE_CXX_COMPILER} DIRECTORY)
  copy_dll(${MINGW_BIN_PATH}/libstdc++-6.dll)
  copy_dll(${MINGW_BIN_PATH}/libgcc_s_dw2-1.dll ${MINGW_BIN_PATH}/libgcc_s_sjlj-1.dll)
  copy_dll(${MINGW_BIN_PATH}/libwinpthread-1.dll)
endif()

if(WIN32)
  # Copy the appropriate SFML DLLs
  set(SFML_BIN_PATH ${SFML_INCLUDE_DIR}/../bin)
  copy_dll(${SFML_BIN_PATH}/libsndfile-1.dll)
  copy_dll(${SFML_BIN_PATH}/openal32.dll)
  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    copy_dll(${SFML_BIN_PATH}/sfml-audio-d-2.dll ${SFML_BIN_PATH}/sfml-audio-2.dll)
    copy_dll(${SFML_BIN_PATH}/sfml-graphics-d-2.dll ${SFML_BIN_PATH}/sfml-graphics-2.dll)
    copy_dll(${SFML_BIN_PATH}/sfml-network-d-2.dll ${SFML_BIN_PATH}/sfml-network-2.dll)
    copy_dll(${SFML_BIN_PATH}/sfml-system-d-2.dll ${SFML_BIN_PATH}/sfml-system-2.dll)
    copy_dll(${SFML_BIN_PATH}/sfml-window-d-2.dll ${SFML_BIN_PATH}/sfml-window-2.dll)
  else()
    copy_dll(${SFML_BIN_PATH}/sfml-audio-2.dll)
    copy_dll(${SFML_BIN_PATH}/sfml-graphics-2.dll)
    copy_dll(${SFML_BIN_PATH}/sfml-network-2.dll)
    copy_dll(${SFML_BIN_PATH}/sfml-system-2.dll)
    copy_dll(${SFML_BIN_PATH}/sfml-window-2.dll)
  endif()
endif()
# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)

# CPack packaging
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING")
set(CPACK_PACKAGE_VERSION_MAJOR "${Platformer_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${Platformer_VERSION_MINOR}")
include(CPack)
