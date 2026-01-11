cmake_minimum_required(VERSION 3.20)
project(cpp-project CXX)

file(GLOB_RECURSE SRC_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")
add_executable(cpp-project ${SRC_FILES} "src/gui_utilities.cpp" "src/game_mechanics.cpp" )

find_package(glfw3 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glad CONFIG REQUIRED)
target_link_libraries(cpp-project
    PRIVATE
        glfw
        OpenGL::GL
        glad::glad
)

target_include_directories(cpp-project PUBLIC "${CMAKE_SOURCE_DIR}/include")
set_target_properties(cpp-project PROPERTIES CXX_STANDARD 23)
if(MINGW)
  target_link_libraries(cpp-project "-lstdc++exp")
endif()
