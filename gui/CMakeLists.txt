cmake_minimum_required(VERSION 3.17)
project(zappy_gui)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_GENERATOR "Unix Makefiles")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    add_definitions(-DASSETS=\"./gui/assets/\")
else ()
    add_definitions(-DASSETS=\"${CMAKE_SOURCE_DIR}/assets/\")
endif ()

include_directories(includes)
include_directories(dependencies/imgui)
include_directories(dependencies/rlImgui)
add_subdirectory(dependencies)

file(GLOB_RECURSE SOURCES
        ${CMAKE_SOURCE_DIR}/sources/*.cpp
        ${CMAKE_SOURCE_DIR}/includes/*.hpp
)

# main executable

add_executable(${PROJECT_NAME} ${SOURCES} ${IMGUI_FILES} ${RLIMGUI_FILES})
target_link_libraries(${PROJECT_NAME} PUBLIC raylib raylib_cpp fmt)

# tests

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    list (APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/criterion")
    find_package(Criterion REQUIRED)

    file (GLOB_RECURSE TESTS_SOURCES
            ${CMAKE_SOURCE_DIR}/tests/*.cpp
    )
    list(FILTER SOURCES EXCLUDE REGEX ".*sources/main.cpp")

    add_executable(tests ${SOURCES} ${IMGUI_FILES} ${RLIMGUI_FILES} ${TESTS_SOURCES})
    target_link_libraries(tests PUBLIC ${CRITERION_LIBRARIES} raylib raylib_cpp)

    add_test (tests tests)

    target_compile_options(tests PRIVATE --coverage)
    target_link_libraries(tests PRIVATE --coverage)
endif ()

