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
include test/CMakeFiles/test_host_ip.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/test_host_ip.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/test_host_ip.dir/flags.make

test/CMakeFiles/test_host_ip.dir/test_host_ip.cpp.o: test/CMakeFiles/test_host_ip.dir/flags.make
test/CMakeFiles/test_host_ip.dir/test_host_ip.cpp.o: ../test/test_host_ip.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/james/jameswork/james_clion/find_use/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/test_host_ip.dir/test_host_ip.cpp.o"
	cd /Users/james/jameswork/james_clion/find_use/cmake-build-debug/test && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_host_ip.dir/test_host_ip.cpp.o -c /Users/james/jameswork/james_clion/find_use/test/test_host_ip.cpp

test/CMakeFiles/test_host_ip.dir/test_host_ip.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_host_ip.dir/test_host_ip.cpp.i"
	cd /Users/james/jameswork/james_clion/find_use/cmake-build-debug/test && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/james/jameswork/james_clion/find_use/test/test_host_ip.cpp > CMakeFiles/test_host_ip.dir/test_host_ip.cpp.i

test/CMakeFiles/test_host_ip.dir/test_host_ip.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_host_ip.dir/test_host_ip.cpp.s"
	cd /Users/james/jameswork/james_clion/find_use/cmake-build-debug/test && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/james/jameswork/james_clion/find_use/test/test_host_ip.cpp -o CMakeFiles/test_host_ip.dir/test_host_ip.cpp.s

# Object files for target test_host_ip
test_host_ip_OBJECTS = \
"CMakeFiles/test_host_ip.dir/test_host_ip.cpp.o"

# External object files for target test_host_ip
test_host_ip_EXTERNAL_OBJECTS =

test/test_host_ip: test/CMakeFiles/test_host_ip.dir/test_host_ip.cpp.o
test/test_host_ip: test/CMakeFiles/test_host_ip.dir/build.make
test/test_host_ip: test/CMakeFiles/test_host_ip.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/james/jameswork/james_clion/find_use/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_host_ip"
	cd /Users/james/jameswork/james_clion/find_use/cmake-build-debug/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_host_ip.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/test_host_ip.dir/build: test/test_host_ip

.PHONY : test/CMakeFiles/test_host_ip.dir/build

test/CMakeFiles/test_host_ip.dir/clean:
	cd /Users/james/jameswork/james_clion/find_use/cmake-build-debug/test && $(CMAKE_COMMAND) -P CMakeFiles/test_host_ip.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/test_host_ip.dir/clean

test/CMakeFiles/test_host_ip.dir/depend:
	cd /Users/james/jameswork/james_clion/find_use/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/james/jameswork/james_clion/find_use /Users/james/jameswork/james_clion/find_use/test /Users/james/jameswork/james_clion/find_use/cmake-build-debug /Users/james/jameswork/james_clion/find_use/cmake-build-debug/test /Users/james/jameswork/james_clion/find_use/cmake-build-debug/test/CMakeFiles/test_host_ip.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/test_host_ip.dir/depend

