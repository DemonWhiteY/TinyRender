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

# Utility rule file for ExperimentalTest.

# Include any custom commands dependencies for this target.
include include/jsoncpp/CMakeFiles/ExperimentalTest.dir/compiler_depend.make

# Include the progress variables for this target.
include include/jsoncpp/CMakeFiles/ExperimentalTest.dir/progress.make

include/jsoncpp/CMakeFiles/ExperimentalTest:
	cd /d E:\Lab\TinyShader\build\include\jsoncpp && D:\CMake\bin\ctest.exe -D ExperimentalTest

ExperimentalTest: include/jsoncpp/CMakeFiles/ExperimentalTest
ExperimentalTest: include/jsoncpp/CMakeFiles/ExperimentalTest.dir/build.make
.PHONY : ExperimentalTest

# Rule to build all files generated by this target.
include/jsoncpp/CMakeFiles/ExperimentalTest.dir/build: ExperimentalTest
.PHONY : include/jsoncpp/CMakeFiles/ExperimentalTest.dir/build

include/jsoncpp/CMakeFiles/ExperimentalTest.dir/clean:
	cd /d E:\Lab\TinyShader\build\include\jsoncpp && $(CMAKE_COMMAND) -P CMakeFiles\ExperimentalTest.dir\cmake_clean.cmake
.PHONY : include/jsoncpp/CMakeFiles/ExperimentalTest.dir/clean

include/jsoncpp/CMakeFiles/ExperimentalTest.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" E:\Lab\TinyShader E:\Lab\TinyShader\include\jsoncpp E:\Lab\TinyShader\build E:\Lab\TinyShader\build\include\jsoncpp E:\Lab\TinyShader\build\include\jsoncpp\CMakeFiles\ExperimentalTest.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : include/jsoncpp/CMakeFiles/ExperimentalTest.dir/depend

