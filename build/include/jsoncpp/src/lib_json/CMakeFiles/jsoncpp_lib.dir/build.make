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
include include/jsoncpp/src/lib_json/CMakeFiles/jsoncpp_lib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include include/jsoncpp/src/lib_json/CMakeFiles/jsoncpp_lib.dir/compiler_depend.make

# Include the progress variables for this target.
include include/jsoncpp/src/lib_json/CMakeFiles/jsoncpp_lib.dir/progress.make

# Include the compile flags for this target's objects.
include include/jsoncpp/src/lib_json/CMakeFiles/jsoncpp_lib.dir/flags.make

include/jsoncpp/src/lib_json/CMakeFiles/jsoncpp_lib.dir/json_reader.cpp.obj: include/jsoncpp/src/lib_json/CMakeFiles/jsoncpp_lib.dir/flags.make
include/jsoncpp/src/lib_json/CMakeFiles/jsoncpp_lib.dir/json_reader.cpp.obj: include/jsoncpp/src/lib_json/CMakeFiles/jsoncpp_lib.dir/includes_CXX.rsp
include/jsoncpp/src/lib_json/CMakeFiles/jsoncpp_lib.dir/json_reader.cpp.obj: E:/Lab/TinyShader/include/jsoncpp/src/lib_json/json_reader.cpp
include/jsoncpp/src/lib_json/CMakeFiles/jsoncpp_lib.dir/json_reader.cpp.obj: include/jsoncpp/src/lib_json/CMakeFiles/jsoncpp_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=E:\Lab\TinyShader\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object include/jsoncpp/src/lib_json/CMakeFiles/jsoncpp_lib.dir/json_reader.cpp.obj"
	cd /d E:\Lab\TinyShader\build\include\jsoncpp\src\lib_json && D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT include/jsoncpp/src/lib_json/CMakeFiles/jsoncpp_lib.dir/json_reader.cpp.obj -MF CMakeFiles\jsoncpp_lib.dir\json_reader.cpp.obj.d -o CMakeFiles\jsoncpp_lib.dir\json_reader.cpp.obj -c E:\Lab\TinyShader\include\jsoncpp\src\lib_json\json_reader.cpp

include/jsoncpp/src/lib_json/CMakeFiles/jsoncpp_lib.dir/json_reader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/jsoncpp_lib.dir/json_reader.cpp.i"
	cd /d E:\Lab\TinyShader\build\include\jsoncpp\src\lib_json && D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\Lab\TinyShader\include\jsoncpp\src\lib_json\json_reader.cpp > CMakeFiles\jsoncpp_lib.dir\json_reader.cpp.i

include/jsoncpp/src/lib_json/CMakeFiles/jsoncpp_lib.dir/json_reader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/jsoncpp_lib.dir/json_reader.cpp.s"
	cd /d E:\Lab\TinyShader\build\include\jsoncpp\src\lib_json && D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\Lab\TinyShader\include\jsoncpp\src\lib_json\json_reader.cpp -o CMakeFiles\jsoncpp_lib.dir\json_reader.cpp.s

include/jsoncpp/src/lib_json/CMakeFiles/jsoncpp_lib.dir/json_value.cpp.obj: include/jsoncpp/src/lib_json/CMakeFiles/jsoncpp_lib.dir/flags.make
include/jsoncpp/src/lib_json/CMakeFiles/jsoncpp_lib.dir/json_value.cpp.obj: include/jsoncpp/src/lib_json/CMakeFiles/jsoncpp_lib.dir/includes_CXX.rsp
include/jsoncpp/src/lib_json/CMakeFiles/jsoncpp_lib.dir/json_value.cpp.obj: E:/Lab/TinyShader/include/jsoncpp/src/lib_json/json_value.cpp
include/jsoncpp/src/lib_json/CMakeFiles/jsoncpp_lib.dir/json_value.cpp.obj: include/jsoncpp/src/lib_json/CMakeFiles/jsoncpp_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=E:\Lab\TinyShader\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object include/jsoncpp/src/lib_json/CMakeFiles/jsoncpp_lib.dir/json_value.cpp.obj"
	cd /d E:\Lab\TinyShader\build\include\jsoncpp\src\lib_json && D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT include/jsoncpp/src/lib_json/CMakeFiles/jsoncpp_lib.dir/json_value.cpp.obj -MF CMakeFiles\jsoncpp_lib.dir\json_value.cpp.obj.d -o CMakeFiles\jsoncpp_lib.dir\json_value.cpp.obj -c E:\Lab\TinyShader\include\jsoncpp\src\lib_json\json_value.cpp

include/jsoncpp/src/lib_json/CMakeFiles/jsoncpp_lib.dir/json_value.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/jsoncpp_lib.dir/json_value.cpp.i"
	cd /d E:\Lab\TinyShader\build\include\jsoncpp\src\lib_json && D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\Lab\TinyShader\include\jsoncpp\src\lib_json\json_value.cpp > CMakeFiles\jsoncpp_lib.dir\json_value.cpp.i

include/jsoncpp/src/lib_json/CMakeFiles/jsoncpp_lib.dir/json_value.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/jsoncpp_lib.dir/json_value.cpp.s"
	cd /d E:\Lab\TinyShader\build\include\jsoncpp\src\lib_json && D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\Lab\TinyShader\include\jsoncpp\src\lib_json\json_value.cpp -o CMakeFiles\jsoncpp_lib.dir\json_value.cpp.s

include/jsoncpp/src/lib_json/CMakeFiles/jsoncpp_lib.dir/json_writer.cpp.obj: include/jsoncpp/src/lib_json/CMakeFiles/jsoncpp_lib.dir/flags.make
include/jsoncpp/src/lib_json/CMakeFiles/jsoncpp_lib.dir/json_writer.cpp.obj: include/jsoncpp/src/lib_json/CMakeFiles/jsoncpp_lib.dir/includes_CXX.rsp
include/jsoncpp/src/lib_json/CMakeFiles/jsoncpp_lib.dir/json_writer.cpp.obj: E:/Lab/TinyShader/include/jsoncpp/src/lib_json/json_writer.cpp
include/jsoncpp/src/lib_json/CMakeFiles/jsoncpp_lib.dir/json_writer.cpp.obj: include/jsoncpp/src/lib_json/CMakeFiles/jsoncpp_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=E:\Lab\TinyShader\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object include/jsoncpp/src/lib_json/CMakeFiles/jsoncpp_lib.dir/json_writer.cpp.obj"
	cd /d E:\Lab\TinyShader\build\include\jsoncpp\src\lib_json && D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT include/jsoncpp/src/lib_json/CMakeFiles/jsoncpp_lib.dir/json_writer.cpp.obj -MF CMakeFiles\jsoncpp_lib.dir\json_writer.cpp.obj.d -o CMakeFiles\jsoncpp_lib.dir\json_writer.cpp.obj -c E:\Lab\TinyShader\include\jsoncpp\src\lib_json\json_writer.cpp

include/jsoncpp/src/lib_json/CMakeFiles/jsoncpp_lib.dir/json_writer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/jsoncpp_lib.dir/json_writer.cpp.i"
	cd /d E:\Lab\TinyShader\build\include\jsoncpp\src\lib_json && D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\Lab\TinyShader\include\jsoncpp\src\lib_json\json_writer.cpp > CMakeFiles\jsoncpp_lib.dir\json_writer.cpp.i

include/jsoncpp/src/lib_json/CMakeFiles/jsoncpp_lib.dir/json_writer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/jsoncpp_lib.dir/json_writer.cpp.s"
	cd /d E:\Lab\TinyShader\build\include\jsoncpp\src\lib_json && D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\Lab\TinyShader\include\jsoncpp\src\lib_json\json_writer.cpp -o CMakeFiles\jsoncpp_lib.dir\json_writer.cpp.s

# Object files for target jsoncpp_lib
jsoncpp_lib_OBJECTS = \
"CMakeFiles/jsoncpp_lib.dir/json_reader.cpp.obj" \
"CMakeFiles/jsoncpp_lib.dir/json_value.cpp.obj" \
"CMakeFiles/jsoncpp_lib.dir/json_writer.cpp.obj"

# External object files for target jsoncpp_lib
jsoncpp_lib_EXTERNAL_OBJECTS =

include/jsoncpp/src/lib_json/libjsoncpp.dll: include/jsoncpp/src/lib_json/CMakeFiles/jsoncpp_lib.dir/json_reader.cpp.obj
include/jsoncpp/src/lib_json/libjsoncpp.dll: include/jsoncpp/src/lib_json/CMakeFiles/jsoncpp_lib.dir/json_value.cpp.obj
include/jsoncpp/src/lib_json/libjsoncpp.dll: include/jsoncpp/src/lib_json/CMakeFiles/jsoncpp_lib.dir/json_writer.cpp.obj
include/jsoncpp/src/lib_json/libjsoncpp.dll: include/jsoncpp/src/lib_json/CMakeFiles/jsoncpp_lib.dir/build.make
include/jsoncpp/src/lib_json/libjsoncpp.dll: include/jsoncpp/src/lib_json/CMakeFiles/jsoncpp_lib.dir/linkLibs.rsp
include/jsoncpp/src/lib_json/libjsoncpp.dll: include/jsoncpp/src/lib_json/CMakeFiles/jsoncpp_lib.dir/objects1.rsp
include/jsoncpp/src/lib_json/libjsoncpp.dll: include/jsoncpp/src/lib_json/CMakeFiles/jsoncpp_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=E:\Lab\TinyShader\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX shared library libjsoncpp.dll"
	cd /d E:\Lab\TinyShader\build\include\jsoncpp\src\lib_json && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\jsoncpp_lib.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
include/jsoncpp/src/lib_json/CMakeFiles/jsoncpp_lib.dir/build: include/jsoncpp/src/lib_json/libjsoncpp.dll
.PHONY : include/jsoncpp/src/lib_json/CMakeFiles/jsoncpp_lib.dir/build

include/jsoncpp/src/lib_json/CMakeFiles/jsoncpp_lib.dir/clean:
	cd /d E:\Lab\TinyShader\build\include\jsoncpp\src\lib_json && $(CMAKE_COMMAND) -P CMakeFiles\jsoncpp_lib.dir\cmake_clean.cmake
.PHONY : include/jsoncpp/src/lib_json/CMakeFiles/jsoncpp_lib.dir/clean

include/jsoncpp/src/lib_json/CMakeFiles/jsoncpp_lib.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" E:\Lab\TinyShader E:\Lab\TinyShader\include\jsoncpp\src\lib_json E:\Lab\TinyShader\build E:\Lab\TinyShader\build\include\jsoncpp\src\lib_json E:\Lab\TinyShader\build\include\jsoncpp\src\lib_json\CMakeFiles\jsoncpp_lib.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : include/jsoncpp/src/lib_json/CMakeFiles/jsoncpp_lib.dir/depend

