#link_directories(${PROJECT_SOURCE_DIR}/bin)

#include_directories(${PROJECT_SOURCE_DIR}/extlibs/SFML/include)
#link_libraries(sfml-system-2 sfml-window-2 sfml-graphics-2 sfml-audio-2 sfml-network-2)

set(INC ${PROJECT_SOURCE_DIR}/Trunk/include/oublietteer)
set(SRC ${PROJECT_SOURCE_DIR}/Trunk/src/oublietteer)
set(EXAMPLE_INC ${PROJECT_SOURCE_DIR}/Trunk/include/oublietteer/example)
set(EXAMPLE_SRC ${PROJECT_SOURCE_DIR}/Trunk/src/oublietteer/example)

include_directories(${PROJECT_SOURCE_DIR}/Trunk/include)

set(PROJECT_FILES
	${SRC}/Oubliette.cpp
	${INC}/Oubliette.hpp
	${SRC}/Room.cpp
	${INC}/Room.hpp
	${SRC}/Floor.cpp
	${INC}/Floor.hpp
	${SRC}/Random.cpp
	${INC}/Random.hpp
	${SRC}/Bitmap.cpp
	${INC}/Bitmap.hpp
	${SRC}/Pixel.cpp
	${INC}/Pixel.hpp
	${SRC}/MathUtilities.cpp
	${INC}/MathUtilities.hpp
	${INC}/Vector2.hpp
	${INC}/Bounds.hpp
)

set(EXAMPLE_FILES
	${EXAMPLE_SRC}/main.cpp
)

add_library(Oublietteer ${PROJECT_FILES})
link_libraries(Oublietteer)
#add_executable(OublietteerExample ${EXAMPLE_FILES})

set_property(TARGET Oublietteer PROPERTY CXX_STANDARD 14)
set_property(TARGET Oublietteer PROPERTY CXX_STANDARD_REQUIRED ON)
#set_property(TARGET OublietteerExample PROPERTY CXX_STANDARD 14)
#set_property(TARGET OublietteerExample PROPERTY CXX_STANDARD_REQUIRED ON)
