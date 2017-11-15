cmake_minimum_required(VERSION 3.8)

project(thread_test)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-static-libgcc -static-libstdc++")
file(COPY "resources" DESTINATION "${CMAKE_BINARY_DIR}")

set(SFML_ROOT "${PROJECT_SOURCE_DIR}/vendor/mingw_sfml-2.4.2")
set(SFML_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/vendor/mingw_sfml-2.4.2/include")

include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories("${PROJECT_SOURCE_DIR}/vendor/mingw_sfml-2.4.2/include/SFML")
include_directories("${PROJECT_BINARY_DIR}")

# Define sources and executable
set(EXECUTABLE_NAME "thread_test")
set(SOURCES main.cpp src/Node.cpp src/Node.h src/S.h src/S.cpp)
add_executable(${EXECUTABLE_NAME} WIN32 ${SOURCES})


set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}" ${CMAKE_MODULE_PATH})
set(SFML_STATIC_LIBRARIES TRUE)

find_package(SFML 2 REQUIRED graphics network audio window system)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)