# app_template_imgui
C++ ImGUI template for small applications

## Building
- Create build directory
```shell
mkdir build
```
- Run CMake from root directory with desired C/C++ compiler and desired generator
```shell
cmake -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_C_COMPILER:FILEPATH=C:\\TDM-GCC-64\\bin\\gcc.exe -DCMAKE_CXX_COMPILER:FILEPATH=C:\\TDM-GCC-64\\bin\\g++.exe --no-warn-unused-cli -S . -B build -G "MinGW Makefiles"
```
- Change directory to build directory
```shell
cd build
```
- Run make command to build the executable
```shell
mingw32-make
```
- Execute
```shell
./AppTemplate.exe
```