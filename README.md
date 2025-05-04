# app_template_imgui

A C++ template for creating small applications using [Dear ImGui](https://github.com/ocornut/imgui), [GLFW](https://www.glfw.org/), and [OpenGL](https://www.opengl.org/).

---

## Overview

This project provides a starting point for building graphical applications with Dear ImGui. It includes:

- Pre-configured CMake build system.
- Integration with GLFW and OpenGL.
- Example source files to get started quickly.

---

## Prerequisites

Before building the project, ensure you have the following installed:

- **CMake** (version 3.22 or higher)
- A C++ compiler supporting C++20 (e.g., GCC, Clang, MSVC)
- **OpenGL** development libraries
- **GLFW** (included as a submodule)
- **fmt** (included as a submodule)

---

## Building

### Step 1: Create a Build Directory

Run the following command to create a build directory:

```shell
mkdir build
```

### Step 2: Run CMake

Run CMake from the root directory with your desired C/C++ compiler and generator. Below are some examples:

Example 1: Using TDM-GCC on Windows

```shell
cmake -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_C_COMPILER:FILEPATH=C:\\TDM-GCC-64\\bin\\gcc.exe -DCMAKE_CXX_COMPILER:FILEPATH=C:\\TDM-GCC-64\\bin\\g++.exe --no-warn-unused-cli -S . -B build -G "MinGW Makefiles"
```

Example 2: Using MSYS2 with clang on Windows

```shell
cmake -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_C_COMPILER:FILEPATH=C:\\msys64\\clangarm64\\bin\\clang.exe -DCMAKE_CXX_COMPILER:FILEPATH=C:\\msys64\\clangarm64\\bin\\clang++.exe --no-warn-unused-cli -S . -B build -G "Unix Makefiles"
```

Example 3: Using GCC on Linux

```shell
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -S . -B build -G "Unix Makefiles"
```

Example 4: Using Ninja

```shell
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -S . -B build -G "Ninja"
```

### Step 3: Change to the Build Directory

Navigate to the build directory:

```shell
cd build
```

### Step 4: Build the Project

Run the appropriate build command based on your generator:
**For MinGW Makefiles (Windows):**

```shell
mingw32-make
```

**For Unix Makefiles:**

```shell
make
```

**For Ninja:**

```shell
ninja
```

### Step 5: Run the Executable

After building, the executable will be located in the build directory. Run it as follows:
**On Windows:**

```shell
AppTemplate.exe
```

**On Linux/macOS:**

```shell
./AppTemplate
```

## Troubleshooting

**CMake Errors**: Ensure the correct paths to your compiler are specified in the `cmake` command.
**Missing Dependencies**: Verify that all required libraries (e.g., OpenGL, GLFW) are installed.
**Build Failures**: Check the output for missing files or incorrect paths.

## Acknowledgments

- [Dear ImGui](https://github.com/ocornut/imgui)
- [GLFW](https://www.glfw.org/)
- [OpenGL](https://www.opengl.org/)
- [fmt](https://github.com/fmtlib/fmt)
