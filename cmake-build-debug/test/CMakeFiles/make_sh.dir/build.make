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
include test/CMakeFiles/make_sh.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/make_sh.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/make_sh.dir/flags.make

test/CMakeFiles/make_sh.dir/make_sh.cpp.o: test/CMakeFiles/make_sh.dir/flags.make
test/CMakeFiles/make_sh.dir/make_sh.cpp.o: ../test/make_sh.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/james/jameswork/james_clion/find_use/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/make_sh.dir/make_sh.cpp.o"
	cd /Users/james/jameswork/james_clion/find_use/cmake-build-debug/test && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/make_sh.dir/make_sh.cpp.o -c /Users/james/jameswork/james_clion/find_use/test/make_sh.cpp

test/CMakeFiles/make_sh.dir/make_sh.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/make_sh.dir/make_sh.cpp.i"
	cd /Users/james/jameswork/james_clion/find_use/cmake-build-debug/test && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/james/jameswork/james_clion/find_use/test/make_sh.cpp > CMakeFiles/make_sh.dir/make_sh.cpp.i

test/CMakeFiles/make_sh.dir/make_sh.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/make_sh.dir/make_sh.cpp.s"
	cd /Users/james/jameswork/james_clion/find_use/cmake-build-debug/test && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/james/jameswork/james_clion/find_use/test/make_sh.cpp -o CMakeFiles/make_sh.dir/make_sh.cpp.s

# Object files for target make_sh
make_sh_OBJECTS = \
"CMakeFiles/make_sh.dir/make_sh.cpp.o"

# External object files for target make_sh
make_sh_EXTERNAL_OBJECTS =

test/make_sh: test/CMakeFiles/make_sh.dir/make_sh.cpp.o
test/make_sh: test/CMakeFiles/make_sh.dir/build.make
test/make_sh: test/CMakeFiles/make_sh.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/james/jameswork/james_clion/find_use/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable make_sh"
	cd /Users/james/jameswork/james_clion/find_use/cmake-build-debug/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/make_sh.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/make_sh.dir/build: test/make_sh

.PHONY : test/CMakeFiles/make_sh.dir/build

test/CMakeFiles/make_sh.dir/clean:
	cd /Users/james/jameswork/james_clion/find_use/cmake-build-debug/test && $(CMAKE_COMMAND) -P CMakeFiles/make_sh.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/make_sh.dir/clean

test/CMakeFiles/make_sh.dir/depend:
	cd /Users/james/jameswork/james_clion/find_use/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/james/jameswork/james_clion/find_use /Users/james/jameswork/james_clion/find_use/test /Users/james/jameswork/james_clion/find_use/cmake-build-debug /Users/james/jameswork/james_clion/find_use/cmake-build-debug/test /Users/james/jameswork/james_clion/find_use/cmake-build-debug/test/CMakeFiles/make_sh.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/make_sh.dir/depend

