# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = "/Applications/CLion 2.app/Contents/bin/cmake/mac/bin/cmake"

# The command to remove a file.
RM = "/Applications/CLion 2.app/Contents/bin/cmake/mac/bin/cmake" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/james/jameswork/james_clion/find_use

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/james/jameswork/james_clion/find_use/cmake-build-debug

# Include any dependencies generated for this target.
include test/makefile/CMakeFiles/make_bill.dir/depend.make

# Include the progress variables for this target.
include test/makefile/CMakeFiles/make_bill.dir/progress.make

# Include the compile flags for this target's objects.
include test/makefile/CMakeFiles/make_bill.dir/flags.make

test/makefile/CMakeFiles/make_bill.dir/make_file/test_task_makefile.cpp.o: test/makefile/CMakeFiles/make_bill.dir/flags.make
test/makefile/CMakeFiles/make_bill.dir/make_file/test_task_makefile.cpp.o: ../test/makefile/make_file/test_task_makefile.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/james/jameswork/james_clion/find_use/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/makefile/CMakeFiles/make_bill.dir/make_file/test_task_makefile.cpp.o"
	cd /Users/james/jameswork/james_clion/find_use/cmake-build-debug/test/makefile && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/make_bill.dir/make_file/test_task_makefile.cpp.o -c /Users/james/jameswork/james_clion/find_use/test/makefile/make_file/test_task_makefile.cpp

test/makefile/CMakeFiles/make_bill.dir/make_file/test_task_makefile.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/make_bill.dir/make_file/test_task_makefile.cpp.i"
	cd /Users/james/jameswork/james_clion/find_use/cmake-build-debug/test/makefile && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/james/jameswork/james_clion/find_use/test/makefile/make_file/test_task_makefile.cpp > CMakeFiles/make_bill.dir/make_file/test_task_makefile.cpp.i

test/makefile/CMakeFiles/make_bill.dir/make_file/test_task_makefile.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/make_bill.dir/make_file/test_task_makefile.cpp.s"
	cd /Users/james/jameswork/james_clion/find_use/cmake-build-debug/test/makefile && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/james/jameswork/james_clion/find_use/test/makefile/make_file/test_task_makefile.cpp -o CMakeFiles/make_bill.dir/make_file/test_task_makefile.cpp.s

# Object files for target make_bill
make_bill_OBJECTS = \
"CMakeFiles/make_bill.dir/make_file/test_task_makefile.cpp.o"

# External object files for target make_bill
make_bill_EXTERNAL_OBJECTS =

test/makefile/make_bill: test/makefile/CMakeFiles/make_bill.dir/make_file/test_task_makefile.cpp.o
test/makefile/make_bill: test/makefile/CMakeFiles/make_bill.dir/build.make
test/makefile/make_bill: test/makefile/CMakeFiles/make_bill.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/james/jameswork/james_clion/find_use/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable make_bill"
	cd /Users/james/jameswork/james_clion/find_use/cmake-build-debug/test/makefile && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/make_bill.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/makefile/CMakeFiles/make_bill.dir/build: test/makefile/make_bill

.PHONY : test/makefile/CMakeFiles/make_bill.dir/build

test/makefile/CMakeFiles/make_bill.dir/clean:
	cd /Users/james/jameswork/james_clion/find_use/cmake-build-debug/test/makefile && $(CMAKE_COMMAND) -P CMakeFiles/make_bill.dir/cmake_clean.cmake
.PHONY : test/makefile/CMakeFiles/make_bill.dir/clean

test/makefile/CMakeFiles/make_bill.dir/depend:
	cd /Users/james/jameswork/james_clion/find_use/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/james/jameswork/james_clion/find_use /Users/james/jameswork/james_clion/find_use/test/makefile /Users/james/jameswork/james_clion/find_use/cmake-build-debug /Users/james/jameswork/james_clion/find_use/cmake-build-debug/test/makefile /Users/james/jameswork/james_clion/find_use/cmake-build-debug/test/makefile/CMakeFiles/make_bill.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/makefile/CMakeFiles/make_bill.dir/depend
