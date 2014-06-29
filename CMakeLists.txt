#Change this if you need to target a specific CMake version
cmake_minimum_required(VERSION 2.6)
project(Platformer)

# Enable debug symbols by default
if(CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE Debug)
endif()
# (you can also set it on the command line: -D CMAKE_BUILD_TYPE=Release)

# Set version information in a config.h file
set(Platformer_VERSION_MAJOR 1)
set(Platformer_VERSION_MINOR 0)
configure_file(
  "${PROJECT_SOURCE_DIR}/src/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
  )
include_directories("${PROJECT_BINARY_DIR}")

# Define sources and executable
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
         src/ResMan.hpp)

add_executable(${EXECUTABLE_NAME} ${SRCS})

# Make sure it compiles 32-bit
set_target_properties(${EXECUTABLE_NAME} PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")

# Enable C++11 features
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

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
  # Copy the damn DLLs...
else()
  message(FATAL_ERROR "Could not find SFML 2.1")
endif()

# Add included cereal deps
# TODO : Make a FindCereal.cmake to avoid the submodule dep
include_directories(${PROJECT_SOURCE_DIR}/thirdparty/cereal/include)

# Copy the ressources.
add_custom_command(TARGET ${EXECUTABLE_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E
                    copy_directory ${PROJECT_SOURCE_DIR}/res ${PROJECT_BINARY_DIR}/res)

# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)

# CPack packaging
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING")
set(CPACK_PACKAGE_VERSION_MAJOR "${Platformer_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${Platformer_VERSION_MINOR}")
include(CPack)
