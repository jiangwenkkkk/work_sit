# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/james/jameswork/james_clion/find_use

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/james/jameswork/james_clion/find_use/cmake-build-debug

# Include any dependencies generated for this target.
include sh/jameswork/CMakeFiles/tcp_cli.dir/depend.make

# Include the progress variables for this target.
include sh/jameswork/CMakeFiles/tcp_cli.dir/progress.make

# Include the compile flags for this target's objects.
include sh/jameswork/CMakeFiles/tcp_cli.dir/flags.make

sh/jameswork/CMakeFiles/tcp_cli.dir/cli.cpp.o: sh/jameswork/CMakeFiles/tcp_cli.dir/flags.make
sh/jameswork/CMakeFiles/tcp_cli.dir/cli.cpp.o: ../sh/jameswork/cli.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/james/jameswork/james_clion/find_use/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object sh/jameswork/CMakeFiles/tcp_cli.dir/cli.cpp.o"
	cd /Users/james/jameswork/james_clion/find_use/cmake-build-debug/sh/jameswork && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tcp_cli.dir/cli.cpp.o -c /Users/james/jameswork/james_clion/find_use/sh/jameswork/cli.cpp

sh/jameswork/CMakeFiles/tcp_cli.dir/cli.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tcp_cli.dir/cli.cpp.i"
	cd /Users/james/jameswork/james_clion/find_use/cmake-build-debug/sh/jameswork && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/james/jameswork/james_clion/find_use/sh/jameswork/cli.cpp > CMakeFiles/tcp_cli.dir/cli.cpp.i

sh/jameswork/CMakeFiles/tcp_cli.dir/cli.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tcp_cli.dir/cli.cpp.s"
	cd /Users/james/jameswork/james_clion/find_use/cmake-build-debug/sh/jameswork && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/james/jameswork/james_clion/find_use/sh/jameswork/cli.cpp -o CMakeFiles/tcp_cli.dir/cli.cpp.s

# Object files for target tcp_cli
tcp_cli_OBJECTS = \
"CMakeFiles/tcp_cli.dir/cli.cpp.o"

# External object files for target tcp_cli
tcp_cli_EXTERNAL_OBJECTS =

sh/jameswork/tcp_cli: sh/jameswork/CMakeFiles/tcp_cli.dir/cli.cpp.o
sh/jameswork/tcp_cli: sh/jameswork/CMakeFiles/tcp_cli.dir/build.make
sh/jameswork/tcp_cli: sh/jameswork/CMakeFiles/tcp_cli.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/james/jameswork/james_clion/find_use/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable tcp_cli"
	cd /Users/james/jameswork/james_clion/find_use/cmake-build-debug/sh/jameswork && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tcp_cli.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
sh/jameswork/CMakeFiles/tcp_cli.dir/build: sh/jameswork/tcp_cli

.PHONY : sh/jameswork/CMakeFiles/tcp_cli.dir/build

sh/jameswork/CMakeFiles/tcp_cli.dir/clean:
	cd /Users/james/jameswork/james_clion/find_use/cmake-build-debug/sh/jameswork && $(CMAKE_COMMAND) -P CMakeFiles/tcp_cli.dir/cmake_clean.cmake
.PHONY : sh/jameswork/CMakeFiles/tcp_cli.dir/clean

sh/jameswork/CMakeFiles/tcp_cli.dir/depend:
	cd /Users/james/jameswork/james_clion/find_use/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/james/jameswork/james_clion/find_use /Users/james/jameswork/james_clion/find_use/sh/jameswork /Users/james/jameswork/james_clion/find_use/cmake-build-debug /Users/james/jameswork/james_clion/find_use/cmake-build-debug/sh/jameswork /Users/james/jameswork/james_clion/find_use/cmake-build-debug/sh/jameswork/CMakeFiles/tcp_cli.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : sh/jameswork/CMakeFiles/tcp_cli.dir/depend

