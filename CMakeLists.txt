cmake_minimum_required(VERSION 3.22)

#---------------------------------------------------
cmake_policy(VERSION 3.21)
#New policy : option() honors normal variables (if defined earlier in CMakeLists).
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
#---------------------------------------------------

project(
  "AppTemplate"
  VERSION 1.0.0
  LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (UNIX)
  message(STATUS "Unix system")
else()
  message(STATUS "Windows system")
endif()

# add_compile_options must be before add_executable
# Show all warnings and treat warnings as errors
# add_compile_options(-Werror -Wall)
# Show all warnings but don't treat them as errors
add_compile_options(-Wall -Wfatal-errors)


set(imgui_external_SOURCE_DIR imgui)
set(implot_external_SOURCE_DIR implot)

# Create a list with name LIST_SRC for source files
set(LIST_SRC
  src/main.cpp
  src/render/render.cpp
  ${imgui_external_SOURCE_DIR}/imgui.cpp
	${imgui_external_SOURCE_DIR}/imgui_draw.cpp
	${imgui_external_SOURCE_DIR}/imgui_tables.cpp
	${imgui_external_SOURCE_DIR}/imgui_widgets.cpp
	${imgui_external_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
  ${imgui_external_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
  ${implot_external_SOURCE_DIR}/implot.cpp
  ${implot_external_SOURCE_DIR}/implot_items.cpp
)
list(LENGTH LIST_SRC LIST_SRC_LEN)
message(STATUS "Length of list LIST_SRC is: ${LIST_SRC_LEN}")

# Create a list with name LIST_INC for include files
set(LIST_INC
  inc
  inc//render
  fmt/include
  glfw/include
  ${imgui_external_SOURCE_DIR}
  ${imgui_external_SOURCE_DIR}/backends
  ${implot_external_SOURCE_DIR}
)
list(LENGTH LIST_INC LIST_INC_LEN)
message(STATUS "Length of list LIST_INC is: ${LIST_INC_LEN}")

# add_subdirectory(fmt)
add_subdirectory(fmt EXCLUDE_FROM_ALL)

# First install dependencies $ sudo apt-get install libgl1-mesa-dev
find_package(OpenGL REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# First install dependencies $ sudo apt install libwayland-dev libxkbcommon-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev
add_subdirectory(glfw EXCLUDE_FROM_ALL)

add_executable(${PROJECT_NAME}
  ${LIST_SRC}
)

target_include_directories(${PROJECT_NAME} PUBLIC
  ${LIST_INC}
)

add_compile_definitions(
  #DEFINES
)

# target_link_libraries(${PROJECT_NAME} fmt::fmt)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt-header-only)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)
