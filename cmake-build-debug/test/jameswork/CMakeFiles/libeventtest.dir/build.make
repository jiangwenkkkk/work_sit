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
include test/jameswork/CMakeFiles/libeventtest.dir/depend.make

# Include the progress variables for this target.
include test/jameswork/CMakeFiles/libeventtest.dir/progress.make

# Include the compile flags for this target's objects.
include test/jameswork/CMakeFiles/libeventtest.dir/flags.make

test/jameswork/CMakeFiles/libeventtest.dir/libevent_test.cpp.o: test/jameswork/CMakeFiles/libeventtest.dir/flags.make
test/jameswork/CMakeFiles/libeventtest.dir/libevent_test.cpp.o: ../test/jameswork/libevent_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/james/jameswork/james_clion/find_use/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/jameswork/CMakeFiles/libeventtest.dir/libevent_test.cpp.o"
	cd /Users/james/jameswork/james_clion/find_use/cmake-build-debug/test/jameswork && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libeventtest.dir/libevent_test.cpp.o -c /Users/james/jameswork/james_clion/find_use/test/jameswork/libevent_test.cpp

test/jameswork/CMakeFiles/libeventtest.dir/libevent_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libeventtest.dir/libevent_test.cpp.i"
	cd /Users/james/jameswork/james_clion/find_use/cmake-build-debug/test/jameswork && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/james/jameswork/james_clion/find_use/test/jameswork/libevent_test.cpp > CMakeFiles/libeventtest.dir/libevent_test.cpp.i

test/jameswork/CMakeFiles/libeventtest.dir/libevent_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libeventtest.dir/libevent_test.cpp.s"
	cd /Users/james/jameswork/james_clion/find_use/cmake-build-debug/test/jameswork && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/james/jameswork/james_clion/find_use/test/jameswork/libevent_test.cpp -o CMakeFiles/libeventtest.dir/libevent_test.cpp.s

# Object files for target libeventtest
libeventtest_OBJECTS = \
"CMakeFiles/libeventtest.dir/libevent_test.cpp.o"

# External object files for target libeventtest
libeventtest_EXTERNAL_OBJECTS =

test/jameswork/libeventtest: test/jameswork/CMakeFiles/libeventtest.dir/libevent_test.cpp.o
test/jameswork/libeventtest: test/jameswork/CMakeFiles/libeventtest.dir/build.make
test/jameswork/libeventtest: /usr/local/lib/libevent.a
test/jameswork/libeventtest: test/jameswork/CMakeFiles/libeventtest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/james/jameswork/james_clion/find_use/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable libeventtest"
	cd /Users/james/jameswork/james_clion/find_use/cmake-build-debug/test/jameswork && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/libeventtest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/jameswork/CMakeFiles/libeventtest.dir/build: test/jameswork/libeventtest

.PHONY : test/jameswork/CMakeFiles/libeventtest.dir/build

test/jameswork/CMakeFiles/libeventtest.dir/clean:
	cd /Users/james/jameswork/james_clion/find_use/cmake-build-debug/test/jameswork && $(CMAKE_COMMAND) -P CMakeFiles/libeventtest.dir/cmake_clean.cmake
.PHONY : test/jameswork/CMakeFiles/libeventtest.dir/clean

test/jameswork/CMakeFiles/libeventtest.dir/depend:
	cd /Users/james/jameswork/james_clion/find_use/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/james/jameswork/james_clion/find_use /Users/james/jameswork/james_clion/find_use/test/jameswork /Users/james/jameswork/james_clion/find_use/cmake-build-debug /Users/james/jameswork/james_clion/find_use/cmake-build-debug/test/jameswork /Users/james/jameswork/james_clion/find_use/cmake-build-debug/test/jameswork/CMakeFiles/libeventtest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/jameswork/CMakeFiles/libeventtest.dir/depend

