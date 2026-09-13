cmake_minimum_required(VERSION 3.14...3.30)

project(Engine_Game LANGUAGES CXX C)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

## Install glfw
FetchContent_Declare(
    glfw3
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
    )
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable( glfw3 )

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.14.1
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(spdlog)

add_library(illengine STATIC 
    src/Engine.cpp
    src/GraphicsManager.cpp
)

set_target_properties(illengine PROPERTIES CXX_STANDARD 20)
target_include_directories(illengine PUBLIC src)

target_link_libraries(illengine PUBLIC glfw )
target_link_libraries(illengine PRIVATE spdlog::spdlog)
if (WIN32)
    target_link_libraries(illengine PRIVATE winmm)
endif()

add_executable( helloworld demo/helloworld.cpp )
set_target_properties(helloworld PROPERTIES CXX_STANDARD 20)
target_link_libraries(helloworld PRIVATE illengine)
