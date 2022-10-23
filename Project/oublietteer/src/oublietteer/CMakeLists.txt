set(INC ${PROJECT_SOURCE_DIR}/include/oublietteer)
set(SRC ${PROJECT_SOURCE_DIR}/src/oublietteer)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(SRC_FILES
	${SRC}/Oubliette.cpp
	${SRC}/Room.cpp
	${SRC}/Floor.cpp
	${SRC}/Random.cpp
	${SRC}/Bitmap.cpp
	${SRC}/Pixel.cpp
	${SRC}/MathUtilities.cpp
)

set(INC_FILES
	${INC}/Oubliette.hpp
	${INC}/Room.hpp
	${INC}/Floor.hpp
	${INC}/Random.hpp
	${INC}/Bitmap.hpp
	${INC}/Pixel.hpp
	${INC}/MathUtilities.hpp
	${INC}/Vector2.hpp
	${INC}/Bounds.hpp
)

set(PROJECT_FILES ${SRC_FILES} ${INC_FILES})

add_library(oublietteer ${PROJECT_FILES})

install(TARGETS oublietteer)
install(FILES ${INC_FILES} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/oublietteer)

set_property(TARGET oublietteer PROPERTY CXX_STANDARD 14)
set_property(TARGET oublietteer PROPERTY CXX_STANDARD_REQUIRED ON)

