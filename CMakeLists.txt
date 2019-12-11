cmake_minimum_required(VERSION 3.10)

project(CartoGraph)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++14")

include_directories(src)
file(GLOB SOURCES "src/*.cpp")

# Find CGAL and CGAL Qt5
find_package(CGAL)

# Find CGAL and CGAL Qt5
#find_package(CGAL COMPONENTS Qt5)

# Find Qt5 itself
#find_package(Qt5 QUIET COMPONENTS Xml Script OpenGL Gui Svg)


add_executable( carto_exe ${SOURCES} )

target_link_libraries(carto_exe CGAL::CGAL)

