# dependencies/CMakeLists.txt

# fmt
find_package(fmt QUIET)
if (NOT fmt_FOUND)
    add_subdirectory(fmt)
endif()

# raylib
find_package(raylib QUIET)
if (NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            raylib
            GIT_REPOSITORY https://github.com/raysan5/raylib.git
            GIT_TAG 5.0
            GIT_SHALLOW 1
    )
    FetchContent_MakeAvailable(raylib)
endif()

# raylib-cpp
find_package(raylib_cpp QUIET)
if (NOT raylib_cpp_FOUND)
    if (NOT DEFINED RAYLIB_CPP_VERSION)
        set(RAYLIB_CPP_VERSION v5.0.1)
    endif()
    include(FetchContent)
    FetchContent_Declare(
            raylib_cpp
            GIT_REPOSITORY https://github.com/RobLoach/raylib-cpp.git
            GIT_TAG ${RAYLIB_CPP_VERSION}
    )
    FetchContent_MakeAvailable(raylib_cpp)
endif()

file(GLOB IMGUI_FILES ${CMAKE_CURRENT_SOURCE_DIR}/imgui/*.h ${CMAKE_CURRENT_SOURCE_DIR}/imgui/*.cpp)
file(GLOB RLIMGUI_FILES ${CMAKE_CURRENT_SOURCE_DIR}/rlImgui/*.h ${CMAKE_CURRENT_SOURCE_DIR}/rlImgui/*.cpp)

# Propagate these variables to the parent scope
set(IMGUI_FILES ${IMGUI_FILES} PARENT_SCOPE)
set(RLIMGUI_FILES ${RLIMGUI_FILES} PARENT_SCOPE)
