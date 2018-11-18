link_directories(${PROJECT_SOURCE_DIR}/bin)

include_directories(${PROJECT_SOURCE_DIR}/extlibs/SFML/include)
link_libraries(sfml-system-2 sfml-window-2 sfml-graphics-2 sfml-audio-2 sfml-network-2)

set(INC ${PROJECT_SOURCE_DIR}/include/oublietteer)
set(SRC ${PROJECT_SOURCE_DIR}/src/oublietteer)
set(EXAMPLE_INC ${PROJECT_SOURCE_DIR}/include/oublietteer/example)
set(EXAMPLE_SRC ${PROJECT_SOURCE_DIR}/src/oublietteer/example)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(PROJECT_FILES
	${SRC}/Oubliette.cpp
	${INC}/Oubliette.hpp
)

set(EXAMPLE_FILES
	${EXAMPLE_SRC}/main.cpp
)

add_library(Oublietteer ${PROJECT_FILES})
link_libraries(Oublietteer)
add_executable(OublietteerExample ${EXAMPLE_FILES})

set_property(TARGET Oublietteer PROPERTY CXX_STANDARD 14)
set_property(TARGET Oublietteer PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET OublietteerExample PROPERTY CXX_STANDARD 14)
set_property(TARGET OublietteerExample PROPERTY CXX_STANDARD_REQUIRED ON)
