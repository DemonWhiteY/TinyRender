# Install script for directory: E:/Lab/TinyShader/include/jsoncpp/include

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/tinyshader")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "D:/mingw64/bin/objdump.exe")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/json/allocator.h;/json/assertions.h;/json/config.h;/json/forwards.h;/json/json.h;/json/json_features.h;/json/reader.h;/json/value.h;/json/version.h;/json/writer.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/json" TYPE FILE FILES
    "E:/Lab/TinyShader/include/jsoncpp/include/json/allocator.h"
    "E:/Lab/TinyShader/include/jsoncpp/include/json/assertions.h"
    "E:/Lab/TinyShader/include/jsoncpp/include/json/config.h"
    "E:/Lab/TinyShader/include/jsoncpp/include/json/forwards.h"
    "E:/Lab/TinyShader/include/jsoncpp/include/json/json.h"
    "E:/Lab/TinyShader/include/jsoncpp/include/json/json_features.h"
    "E:/Lab/TinyShader/include/jsoncpp/include/json/reader.h"
    "E:/Lab/TinyShader/include/jsoncpp/include/json/value.h"
    "E:/Lab/TinyShader/include/jsoncpp/include/json/version.h"
    "E:/Lab/TinyShader/include/jsoncpp/include/json/writer.h"
    )
endif()

