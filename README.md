# Cpp-OpenGL-CMake-Template
A template application for OpenGL and C++ using CMake

## Usage Example
Specify a generator manually like so: 
```bash
cmake -S. -Bbuild -G"MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug
cmake --build build
.\build\Debug\Application.exe
```
Or use a predefined preset <br>
For example, to use the gcc and makefiles for a debug build on windows x86-64:
```bash
cmake --preset=windows_x86-64_debug_mingw_makefiles
cmake --build build
.\build\Debug\Application.exe
```
Note: Use `cmake --list-presets` to see all available presets