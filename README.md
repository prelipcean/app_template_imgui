# app_template_imgui
C++ ImGUI template for small applications

# Run cmake under windows with custom C/C++ compiler
```shell
mkdir build

cmake -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_C_COMPILER:FILEPATH=C:\TDM-GCC-64\bin\gcc.exe -DCMAKE_CXX_COMPILER:FILEPATH=C:\TDM-GCC-64\bin\g++.exe --no-warn-unused-cli -S . -B build -G "MinGW Makefiles"

cd build

mingw32-make
```