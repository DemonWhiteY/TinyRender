# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.30

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = D:\CMake\bin\cmake.exe

# The command to remove a file.
RM = D:\CMake\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = E:\Lab\TinyShader

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = E:\Lab\TinyShader\build

# Include any dependencies generated for this target.
include include/jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include include/jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/compiler_depend.make

# Include the progress variables for this target.
include include/jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/progress.make

# Include the compile flags for this target's objects.
include include/jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/flags.make

include/jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/jsontest.cpp.obj: include/jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/flags.make
include/jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/jsontest.cpp.obj: include/jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/includes_CXX.rsp
include/jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/jsontest.cpp.obj: E:/Lab/TinyShader/include/jsoncpp/src/test_lib_json/jsontest.cpp
include/jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/jsontest.cpp.obj: include/jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=E:\Lab\TinyShader\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object include/jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/jsontest.cpp.obj"
	cd /d E:\Lab\TinyShader\build\include\jsoncpp\src\test_lib_json && D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT include/jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/jsontest.cpp.obj -MF CMakeFiles\jsoncpp_test.dir\jsontest.cpp.obj.d -o CMakeFiles\jsoncpp_test.dir\jsontest.cpp.obj -c E:\Lab\TinyShader\include\jsoncpp\src\test_lib_json\jsontest.cpp

include/jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/jsontest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/jsoncpp_test.dir/jsontest.cpp.i"
	cd /d E:\Lab\TinyShader\build\include\jsoncpp\src\test_lib_json && D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\Lab\TinyShader\include\jsoncpp\src\test_lib_json\jsontest.cpp > CMakeFiles\jsoncpp_test.dir\jsontest.cpp.i

include/jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/jsontest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/jsoncpp_test.dir/jsontest.cpp.s"
	cd /d E:\Lab\TinyShader\build\include\jsoncpp\src\test_lib_json && D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\Lab\TinyShader\include\jsoncpp\src\test_lib_json\jsontest.cpp -o CMakeFiles\jsoncpp_test.dir\jsontest.cpp.s

include/jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/fuzz.cpp.obj: include/jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/flags.make
include/jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/fuzz.cpp.obj: include/jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/includes_CXX.rsp
include/jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/fuzz.cpp.obj: E:/Lab/TinyShader/include/jsoncpp/src/test_lib_json/fuzz.cpp
include/jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/fuzz.cpp.obj: include/jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=E:\Lab\TinyShader\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object include/jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/fuzz.cpp.obj"
	cd /d E:\Lab\TinyShader\build\include\jsoncpp\src\test_lib_json && D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT include/jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/fuzz.cpp.obj -MF CMakeFiles\jsoncpp_test.dir\fuzz.cpp.obj.d -o CMakeFiles\jsoncpp_test.dir\fuzz.cpp.obj -c E:\Lab\TinyShader\include\jsoncpp\src\test_lib_json\fuzz.cpp

include/jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/fuzz.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/jsoncpp_test.dir/fuzz.cpp.i"
	cd /d E:\Lab\TinyShader\build\include\jsoncpp\src\test_lib_json && D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\Lab\TinyShader\include\jsoncpp\src\test_lib_json\fuzz.cpp > CMakeFiles\jsoncpp_test.dir\fuzz.cpp.i

include/jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/fuzz.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/jsoncpp_test.dir/fuzz.cpp.s"
	cd /d E:\Lab\TinyShader\build\include\jsoncpp\src\test_lib_json && D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\Lab\TinyShader\include\jsoncpp\src\test_lib_json\fuzz.cpp -o CMakeFiles\jsoncpp_test.dir\fuzz.cpp.s

include/jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/main.cpp.obj: include/jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/flags.make
include/jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/main.cpp.obj: include/jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/includes_CXX.rsp
include/jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/main.cpp.obj: E:/Lab/TinyShader/include/jsoncpp/src/test_lib_json/main.cpp
include/jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/main.cpp.obj: include/jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=E:\Lab\TinyShader\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object include/jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/main.cpp.obj"
	cd /d E:\Lab\TinyShader\build\include\jsoncpp\src\test_lib_json && D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT include/jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/main.cpp.obj -MF CMakeFiles\jsoncpp_test.dir\main.cpp.obj.d -o CMakeFiles\jsoncpp_test.dir\main.cpp.obj -c E:\Lab\TinyShader\include\jsoncpp\src\test_lib_json\main.cpp

include/jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/jsoncpp_test.dir/main.cpp.i"
	cd /d E:\Lab\TinyShader\build\include\jsoncpp\src\test_lib_json && D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\Lab\TinyShader\include\jsoncpp\src\test_lib_json\main.cpp > CMakeFiles\jsoncpp_test.dir\main.cpp.i

include/jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/jsoncpp_test.dir/main.cpp.s"
	cd /d E:\Lab\TinyShader\build\include\jsoncpp\src\test_lib_json && D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\Lab\TinyShader\include\jsoncpp\src\test_lib_json\main.cpp -o CMakeFiles\jsoncpp_test.dir\main.cpp.s

# Object files for target jsoncpp_test
jsoncpp_test_OBJECTS = \
"CMakeFiles/jsoncpp_test.dir/jsontest.cpp.obj" \
"CMakeFiles/jsoncpp_test.dir/fuzz.cpp.obj" \
"CMakeFiles/jsoncpp_test.dir/main.cpp.obj"

# External object files for target jsoncpp_test
jsoncpp_test_EXTERNAL_OBJECTS =

include/jsoncpp/src/test_lib_json/jsoncpp_test.exe: include/jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/jsontest.cpp.obj
include/jsoncpp/src/test_lib_json/jsoncpp_test.exe: include/jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/fuzz.cpp.obj
include/jsoncpp/src/test_lib_json/jsoncpp_test.exe: include/jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/main.cpp.obj
include/jsoncpp/src/test_lib_json/jsoncpp_test.exe: include/jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/build.make
include/jsoncpp/src/test_lib_json/jsoncpp_test.exe: include/jsoncpp/src/lib_json/libjsoncpp.dll.a
include/jsoncpp/src/test_lib_json/jsoncpp_test.exe: include/jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/linkLibs.rsp
include/jsoncpp/src/test_lib_json/jsoncpp_test.exe: include/jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/objects1.rsp
include/jsoncpp/src/test_lib_json/jsoncpp_test.exe: include/jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=E:\Lab\TinyShader\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable jsoncpp_test.exe"
	cd /d E:\Lab\TinyShader\build\include\jsoncpp\src\test_lib_json && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\jsoncpp_test.dir\link.txt --verbose=$(VERBOSE)
	cd /d E:\Lab\TinyShader\build\include\jsoncpp\src\test_lib_json && .\jsoncpp_test.exe

# Rule to build all files generated by this target.
include/jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/build: include/jsoncpp/src/test_lib_json/jsoncpp_test.exe
.PHONY : include/jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/build

include/jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/clean:
	cd /d E:\Lab\TinyShader\build\include\jsoncpp\src\test_lib_json && $(CMAKE_COMMAND) -P CMakeFiles\jsoncpp_test.dir\cmake_clean.cmake
.PHONY : include/jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/clean

include/jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" E:\Lab\TinyShader E:\Lab\TinyShader\include\jsoncpp\src\test_lib_json E:\Lab\TinyShader\build E:\Lab\TinyShader\build\include\jsoncpp\src\test_lib_json E:\Lab\TinyShader\build\include\jsoncpp\src\test_lib_json\CMakeFiles\jsoncpp_test.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : include/jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/depend

