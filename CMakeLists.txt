# CMake entry point.
# Note that this CMakeLists.txt in fully independent from the one in the parent directory
# (since that's the goal of this tutorial !)

# For an introduction to CMake, see
# http://www.cmake.org/cmake/help/cmake_tutorial.html (at least steps 1 and 2)

cmake_minimum_required (VERSION 3.13)

set(CMAKE_CXX_COMPILER "C:/msys64/ucrt64/bin/g++.exe")
set(CMAKE_C_COMPILER "C:/msys64/ucrt64/bin/gcc.exe")

project(world)

find_package(OpenGL REQUIRED)

# Ask the user to give the paths to GLFW, GLEW and GLM.
# On Linux this can be found automatically with pkg-config; 
# see http://stackoverflow.com/questions/6889264/cmake-flags-for-opengl-using-glew-and-glfw, for instance.

set(GLFW_LIBRARY glfw3dll)
set(GLFW_INCLUDE_PATH   "${CMAKE_CURRENT_SOURCE_DIR}/include/GLFW")
set(LIBRARY_PATH        "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(GLM_INCLUDE_PATH    "${CMAKE_CURRENT_SOURCE_DIR}/include/vendor/glm")
set(VENDOR_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include/vendor")

set(MY_HEADER_FILES
  "${CMAKE_CURRENT_SOURCE_DIR}/include/renderer/renderer.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/shader/shaderProgram.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/vertex buffer/vertexBuffer.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/index buffer/indexBuffer.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/vertex array/vertexArray.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/texture/texture.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/frame buffer/frameBuffer.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/render buffer/renderBuffer.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/cubemap/cubemap.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/minecraft/Block.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/minecraft/ColliderCube.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/minecraft/Player.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/minecraft/Camera.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/minecraft/Ray.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/minecraft/BlockManager.hpp"

  "${CMAKE_CURRENT_SOURCE_DIR}/include/vendor/imgui/imconfig.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/vendor/imgui/imgui_internal.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/vendor/imgui/imgui.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/vendor/imgui/imstb_rectpack.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/vendor/imgui/imstb_textedit.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/vendor/imgui/imstb_truetype.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/vendor/imgui/imgui_impl_glfw.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/vendor/imgui/imgui_impl_opengl3_loader.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/vendor/imgui/imgui_impl_opengl3.h"
)

set(MY_SOURCE_FILES
	"${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/minecraftMain.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/renderer/renderer.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/shader/shaderProgram.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/vertex buffer/vertexBuffer.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/index buffer/indexBuffer.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/vertex array/vertexArray.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/texture/texture.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/frame buffer/frameBuffer.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/render buffer/renderBuffer.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/cubemap/cubemap.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/minecraft/Block.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/minecraft/ColliderCube.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/minecraft/Player.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/minecraft/Camera.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/minecraft/Ray.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/minecraft/BlockManager.cpp"

  "${CMAKE_CURRENT_SOURCE_DIR}/include/vendor/imgui/imgui_demo.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/vendor/imgui/imgui_draw.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/vendor/imgui/imgui_tables.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/vendor/imgui/imgui_widgets.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/vendor/imgui/imgui.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/vendor/imgui/imgui_impl_glfw.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/vendor/imgui/imgui_impl_opengl3.cpp"
)

include_directories(
	${VENDOR_INCLUDE_PATH}
	${LIBRARY_PATH}
	${GLFW_INCLUDE_PATH}
	${GLM_INCLUDE_PATH}
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

link_directories(world ${LIBRARY_PATH})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
add_executable(world
	${MY_HEADER_FILES}
	${MY_SOURCE_FILES}
)

target_link_libraries(world
	${OPENGL_LIBRARY} # filled by "find_package(OpenGL REQUIRED)"
  ${GLFW_LIBRARY}
)