#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/pbrooks/Development/Personal/Oublietteer/Project/oublietteer/build
  /usr/local/Cellar/cmake/3.23.2/bin/cmake -DBUILD_TYPE=$CONFIGURATION$EFFECTIVE_PLATFORM_NAME -P cmake_install.cmake
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/pbrooks/Development/Personal/Oublietteer/Project/oublietteer/build
  /usr/local/Cellar/cmake/3.23.2/bin/cmake -DBUILD_TYPE=$CONFIGURATION$EFFECTIVE_PLATFORM_NAME -P cmake_install.cmake
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/pbrooks/Development/Personal/Oublietteer/Project/oublietteer/build
  /usr/local/Cellar/cmake/3.23.2/bin/cmake -DBUILD_TYPE=$CONFIGURATION$EFFECTIVE_PLATFORM_NAME -P cmake_install.cmake
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/pbrooks/Development/Personal/Oublietteer/Project/oublietteer/build
  /usr/local/Cellar/cmake/3.23.2/bin/cmake -DBUILD_TYPE=$CONFIGURATION$EFFECTIVE_PLATFORM_NAME -P cmake_install.cmake
fi

