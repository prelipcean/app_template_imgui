cmake_minimum_required(VERSION 3.22)

#---------------------------------------------------
# Set CMake policies
cmake_policy(VERSION 3.21)
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW) # option() honors normal variables
#---------------------------------------------------

# Project configuration
project(
  "AppTemplate"
  VERSION 1.0.0
  LANGUAGES C CXX
)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set default build type to Release if not specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# Platform-specific messages
if (UNIX)
  message(STATUS "Unix system detected")
else()
  message(STATUS "Windows system detected")
endif()

# Compiler-specific options
if (MSVC)
  add_compile_options(/W4 /WX) # Enable warnings as errors for MSVC
else()
  add_compile_options(-Wall -Wfatal-errors) # Enable warnings for GCC/Clang
endif()

# Source and include directories
set(imgui_external_SOURCE_DIR imgui)
set(implot_external_SOURCE_DIR implot)

# Create a list with source files
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

# Create a list with include directories
set(LIST_INC
  inc
  inc/render
  fmt/include
  glfw/include
  ${imgui_external_SOURCE_DIR}
  ${imgui_external_SOURCE_DIR}/backends
  ${implot_external_SOURCE_DIR}
)
list(LENGTH LIST_INC LIST_INC_LEN)
message(STATUS "Length of list LIST_INC is: ${LIST_INC_LEN}")

# Add fmt library
add_subdirectory(fmt EXCLUDE_FROM_ALL)

# Find and link OpenGL
# Note for Linux: You may need to install the OpenGL development package (e.g., libgl1-mesa-dev)
find_package(OpenGL REQUIRED)

# Configure GLFW
# Note for Linux: You may need to install the GLFW development package (e.g., libglfw3-dev 
# OR libwayland-dev libxkbcommon-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(glfw EXCLUDE_FROM_ALL)

# Add executable
if(WIN32)
  add_executable(${PROJECT_NAME} WIN32
    ${LIST_SRC}
  )
else()
  add_executable(${PROJECT_NAME}
    ${LIST_SRC}
  )
endif()

# Include directories
target_include_directories(${PROJECT_NAME} PUBLIC
  ${LIST_INC}
)

# Add compile definitions (if needed)
add_compile_definitions(
  # Add any necessary preprocessor definitions here
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt-header-only)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)

# Platform-specific dependencies
if(UNIX)
  target_link_libraries(${PROJECT_NAME} PRIVATE dl pthread) # Add Linux-specific libraries
endif()

# Installation rules
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/resources DESTINATION share/${PROJECT_NAME}) # Example for resources
