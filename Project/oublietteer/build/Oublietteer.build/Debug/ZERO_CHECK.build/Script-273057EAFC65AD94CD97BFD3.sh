#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/pbrooks/Development/Personal/Oublietteer/Project/oublietteer/build
  make -f /Users/pbrooks/Development/Personal/Oublietteer/Project/oublietteer/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/pbrooks/Development/Personal/Oublietteer/Project/oublietteer/build
  make -f /Users/pbrooks/Development/Personal/Oublietteer/Project/oublietteer/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/pbrooks/Development/Personal/Oublietteer/Project/oublietteer/build
  make -f /Users/pbrooks/Development/Personal/Oublietteer/Project/oublietteer/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/pbrooks/Development/Personal/Oublietteer/Project/oublietteer/build
  make -f /Users/pbrooks/Development/Personal/Oublietteer/Project/oublietteer/build/CMakeScripts/ReRunCMake.make
fi

