# Install script for directory: /Users/pbrooks/Development/Personal/Oublietteer/Project/oublietteer/src/oublietteer

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/Users/pbrooks/Development/Personal/Oublietteer/Project/install/targets/oublietteer/release")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
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

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/objdump")
endif()

set(CMAKE_BINARY_DIR "/Users/pbrooks/Development/Personal/Oublietteer/Project/oublietteer/build")

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/pbrooks/Development/Personal/Oublietteer/Project/oublietteer/build/src/oublietteer/Debug/liboublietteer.a")
    if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liboublietteer.a" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liboublietteer.a")
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liboublietteer.a")
    endif()
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/pbrooks/Development/Personal/Oublietteer/Project/oublietteer/build/src/oublietteer/Release/liboublietteer.a")
    if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liboublietteer.a" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liboublietteer.a")
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liboublietteer.a")
    endif()
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/pbrooks/Development/Personal/Oublietteer/Project/oublietteer/build/src/oublietteer/MinSizeRel/liboublietteer.a")
    if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liboublietteer.a" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liboublietteer.a")
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liboublietteer.a")
    endif()
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/pbrooks/Development/Personal/Oublietteer/Project/oublietteer/build/src/oublietteer/RelWithDebInfo/liboublietteer.a")
    if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liboublietteer.a" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liboublietteer.a")
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liboublietteer.a")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/Users/pbrooks/Development/Personal/Oublietteer/Project/install/targets/oublietteer/release/include/oublietteer/Oubliette.hpp;/Users/pbrooks/Development/Personal/Oublietteer/Project/install/targets/oublietteer/release/include/oublietteer/Room.hpp;/Users/pbrooks/Development/Personal/Oublietteer/Project/install/targets/oublietteer/release/include/oublietteer/Floor.hpp;/Users/pbrooks/Development/Personal/Oublietteer/Project/install/targets/oublietteer/release/include/oublietteer/Random.hpp;/Users/pbrooks/Development/Personal/Oublietteer/Project/install/targets/oublietteer/release/include/oublietteer/Bitmap.hpp;/Users/pbrooks/Development/Personal/Oublietteer/Project/install/targets/oublietteer/release/include/oublietteer/Pixel.hpp;/Users/pbrooks/Development/Personal/Oublietteer/Project/install/targets/oublietteer/release/include/oublietteer/MathUtilities.hpp;/Users/pbrooks/Development/Personal/Oublietteer/Project/install/targets/oublietteer/release/include/oublietteer/Vector2.hpp;/Users/pbrooks/Development/Personal/Oublietteer/Project/install/targets/oublietteer/release/include/oublietteer/Bounds.hpp")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/Users/pbrooks/Development/Personal/Oublietteer/Project/install/targets/oublietteer/release/include/oublietteer" TYPE FILE FILES
    "/Users/pbrooks/Development/Personal/Oublietteer/Project/oublietteer/include/oublietteer/Oubliette.hpp"
    "/Users/pbrooks/Development/Personal/Oublietteer/Project/oublietteer/include/oublietteer/Room.hpp"
    "/Users/pbrooks/Development/Personal/Oublietteer/Project/oublietteer/include/oublietteer/Floor.hpp"
    "/Users/pbrooks/Development/Personal/Oublietteer/Project/oublietteer/include/oublietteer/Random.hpp"
    "/Users/pbrooks/Development/Personal/Oublietteer/Project/oublietteer/include/oublietteer/Bitmap.hpp"
    "/Users/pbrooks/Development/Personal/Oublietteer/Project/oublietteer/include/oublietteer/Pixel.hpp"
    "/Users/pbrooks/Development/Personal/Oublietteer/Project/oublietteer/include/oublietteer/MathUtilities.hpp"
    "/Users/pbrooks/Development/Personal/Oublietteer/Project/oublietteer/include/oublietteer/Vector2.hpp"
    "/Users/pbrooks/Development/Personal/Oublietteer/Project/oublietteer/include/oublietteer/Bounds.hpp"
    )
endif()

