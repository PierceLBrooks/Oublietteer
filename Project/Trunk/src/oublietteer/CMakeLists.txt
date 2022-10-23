set(INC ${PROJECT_SOURCE_DIR}/include/oublietteer)
set(SRC ${PROJECT_SOURCE_DIR}/src/oublietteer)

include_directories(${PROJECT_SOURCE_DIR}/include)

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

add_library(oublietteer ${PROJECT_FILES})
link_libraries(oublietteer)

set_property(TARGET oublietteer PROPERTY CXX_STANDARD 14)
set_property(TARGET oublietteer PROPERTY CXX_STANDARD_REQUIRED ON)

