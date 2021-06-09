cmake_minimum_required(VERSION 3.5)

project(TCD_COMMUNITY LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(TCD_COMMUNITY main.cpp hardwarecontrol.cpp dbus_reader.cpp)
include_directories(${DBUS_INCLUDE_DIRS})
link_directories(${DBUS_LIBRARY_DIRS})


# Declaration of package required
find_package(PkgConfig)
pkg_check_modules(YAMLCPP REQUIRED yaml-cpp>=0.5)
pkg_check_modules(DBUS dbus-1) # This calls pkgconfig with appropriate arguments


target_link_libraries(TCD_COMMUNITY ${YAMLCPP_LIBRARIES})
target_link_libraries(TCD_COMMUNITY ${DBUS_LIBRARIES})
target_link_libraries(TCD_COMMUNITY pthread)

