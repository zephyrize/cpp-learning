# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/sophia/Documents/cpp-learning/practice-1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sophia/Documents/cpp-learning/practice-1/build

# Include any dependencies generated for this target.
include CMakeFiles/my_cmake_exe.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/my_cmake_exe.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/my_cmake_exe.dir/flags.make

CMakeFiles/my_cmake_exe.dir/src/main.cpp.o: CMakeFiles/my_cmake_exe.dir/flags.make
CMakeFiles/my_cmake_exe.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sophia/Documents/cpp-learning/practice-1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/my_cmake_exe.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_cmake_exe.dir/src/main.cpp.o -c /home/sophia/Documents/cpp-learning/practice-1/src/main.cpp

CMakeFiles/my_cmake_exe.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_cmake_exe.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sophia/Documents/cpp-learning/practice-1/src/main.cpp > CMakeFiles/my_cmake_exe.dir/src/main.cpp.i

CMakeFiles/my_cmake_exe.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_cmake_exe.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sophia/Documents/cpp-learning/practice-1/src/main.cpp -o CMakeFiles/my_cmake_exe.dir/src/main.cpp.s

CMakeFiles/my_cmake_exe.dir/src/shape.cpp.o: CMakeFiles/my_cmake_exe.dir/flags.make
CMakeFiles/my_cmake_exe.dir/src/shape.cpp.o: ../src/shape.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sophia/Documents/cpp-learning/practice-1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/my_cmake_exe.dir/src/shape.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_cmake_exe.dir/src/shape.cpp.o -c /home/sophia/Documents/cpp-learning/practice-1/src/shape.cpp

CMakeFiles/my_cmake_exe.dir/src/shape.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_cmake_exe.dir/src/shape.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sophia/Documents/cpp-learning/practice-1/src/shape.cpp > CMakeFiles/my_cmake_exe.dir/src/shape.cpp.i

CMakeFiles/my_cmake_exe.dir/src/shape.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_cmake_exe.dir/src/shape.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sophia/Documents/cpp-learning/practice-1/src/shape.cpp -o CMakeFiles/my_cmake_exe.dir/src/shape.cpp.s

CMakeFiles/my_cmake_exe.dir/src/rectangle.cpp.o: CMakeFiles/my_cmake_exe.dir/flags.make
CMakeFiles/my_cmake_exe.dir/src/rectangle.cpp.o: ../src/rectangle.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sophia/Documents/cpp-learning/practice-1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/my_cmake_exe.dir/src/rectangle.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_cmake_exe.dir/src/rectangle.cpp.o -c /home/sophia/Documents/cpp-learning/practice-1/src/rectangle.cpp

CMakeFiles/my_cmake_exe.dir/src/rectangle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_cmake_exe.dir/src/rectangle.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sophia/Documents/cpp-learning/practice-1/src/rectangle.cpp > CMakeFiles/my_cmake_exe.dir/src/rectangle.cpp.i

CMakeFiles/my_cmake_exe.dir/src/rectangle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_cmake_exe.dir/src/rectangle.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sophia/Documents/cpp-learning/practice-1/src/rectangle.cpp -o CMakeFiles/my_cmake_exe.dir/src/rectangle.cpp.s

CMakeFiles/my_cmake_exe.dir/src/circle.cpp.o: CMakeFiles/my_cmake_exe.dir/flags.make
CMakeFiles/my_cmake_exe.dir/src/circle.cpp.o: ../src/circle.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sophia/Documents/cpp-learning/practice-1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/my_cmake_exe.dir/src/circle.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_cmake_exe.dir/src/circle.cpp.o -c /home/sophia/Documents/cpp-learning/practice-1/src/circle.cpp

CMakeFiles/my_cmake_exe.dir/src/circle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_cmake_exe.dir/src/circle.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sophia/Documents/cpp-learning/practice-1/src/circle.cpp > CMakeFiles/my_cmake_exe.dir/src/circle.cpp.i

CMakeFiles/my_cmake_exe.dir/src/circle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_cmake_exe.dir/src/circle.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sophia/Documents/cpp-learning/practice-1/src/circle.cpp -o CMakeFiles/my_cmake_exe.dir/src/circle.cpp.s

CMakeFiles/my_cmake_exe.dir/src/color.cpp.o: CMakeFiles/my_cmake_exe.dir/flags.make
CMakeFiles/my_cmake_exe.dir/src/color.cpp.o: ../src/color.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sophia/Documents/cpp-learning/practice-1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/my_cmake_exe.dir/src/color.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_cmake_exe.dir/src/color.cpp.o -c /home/sophia/Documents/cpp-learning/practice-1/src/color.cpp

CMakeFiles/my_cmake_exe.dir/src/color.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_cmake_exe.dir/src/color.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sophia/Documents/cpp-learning/practice-1/src/color.cpp > CMakeFiles/my_cmake_exe.dir/src/color.cpp.i

CMakeFiles/my_cmake_exe.dir/src/color.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_cmake_exe.dir/src/color.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sophia/Documents/cpp-learning/practice-1/src/color.cpp -o CMakeFiles/my_cmake_exe.dir/src/color.cpp.s

CMakeFiles/my_cmake_exe.dir/src/shape_container.cpp.o: CMakeFiles/my_cmake_exe.dir/flags.make
CMakeFiles/my_cmake_exe.dir/src/shape_container.cpp.o: ../src/shape_container.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sophia/Documents/cpp-learning/practice-1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/my_cmake_exe.dir/src/shape_container.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_cmake_exe.dir/src/shape_container.cpp.o -c /home/sophia/Documents/cpp-learning/practice-1/src/shape_container.cpp

CMakeFiles/my_cmake_exe.dir/src/shape_container.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_cmake_exe.dir/src/shape_container.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sophia/Documents/cpp-learning/practice-1/src/shape_container.cpp > CMakeFiles/my_cmake_exe.dir/src/shape_container.cpp.i

CMakeFiles/my_cmake_exe.dir/src/shape_container.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_cmake_exe.dir/src/shape_container.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sophia/Documents/cpp-learning/practice-1/src/shape_container.cpp -o CMakeFiles/my_cmake_exe.dir/src/shape_container.cpp.s

CMakeFiles/my_cmake_exe.dir/src/file_manager.cpp.o: CMakeFiles/my_cmake_exe.dir/flags.make
CMakeFiles/my_cmake_exe.dir/src/file_manager.cpp.o: ../src/file_manager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sophia/Documents/cpp-learning/practice-1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/my_cmake_exe.dir/src/file_manager.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_cmake_exe.dir/src/file_manager.cpp.o -c /home/sophia/Documents/cpp-learning/practice-1/src/file_manager.cpp

CMakeFiles/my_cmake_exe.dir/src/file_manager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_cmake_exe.dir/src/file_manager.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sophia/Documents/cpp-learning/practice-1/src/file_manager.cpp > CMakeFiles/my_cmake_exe.dir/src/file_manager.cpp.i

CMakeFiles/my_cmake_exe.dir/src/file_manager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_cmake_exe.dir/src/file_manager.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sophia/Documents/cpp-learning/practice-1/src/file_manager.cpp -o CMakeFiles/my_cmake_exe.dir/src/file_manager.cpp.s

# Object files for target my_cmake_exe
my_cmake_exe_OBJECTS = \
"CMakeFiles/my_cmake_exe.dir/src/main.cpp.o" \
"CMakeFiles/my_cmake_exe.dir/src/shape.cpp.o" \
"CMakeFiles/my_cmake_exe.dir/src/rectangle.cpp.o" \
"CMakeFiles/my_cmake_exe.dir/src/circle.cpp.o" \
"CMakeFiles/my_cmake_exe.dir/src/color.cpp.o" \
"CMakeFiles/my_cmake_exe.dir/src/shape_container.cpp.o" \
"CMakeFiles/my_cmake_exe.dir/src/file_manager.cpp.o"

# External object files for target my_cmake_exe
my_cmake_exe_EXTERNAL_OBJECTS =

my_cmake_exe: CMakeFiles/my_cmake_exe.dir/src/main.cpp.o
my_cmake_exe: CMakeFiles/my_cmake_exe.dir/src/shape.cpp.o
my_cmake_exe: CMakeFiles/my_cmake_exe.dir/src/rectangle.cpp.o
my_cmake_exe: CMakeFiles/my_cmake_exe.dir/src/circle.cpp.o
my_cmake_exe: CMakeFiles/my_cmake_exe.dir/src/color.cpp.o
my_cmake_exe: CMakeFiles/my_cmake_exe.dir/src/shape_container.cpp.o
my_cmake_exe: CMakeFiles/my_cmake_exe.dir/src/file_manager.cpp.o
my_cmake_exe: CMakeFiles/my_cmake_exe.dir/build.make
my_cmake_exe: CMakeFiles/my_cmake_exe.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sophia/Documents/cpp-learning/practice-1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable my_cmake_exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/my_cmake_exe.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/my_cmake_exe.dir/build: my_cmake_exe

.PHONY : CMakeFiles/my_cmake_exe.dir/build

CMakeFiles/my_cmake_exe.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/my_cmake_exe.dir/cmake_clean.cmake
.PHONY : CMakeFiles/my_cmake_exe.dir/clean

CMakeFiles/my_cmake_exe.dir/depend:
	cd /home/sophia/Documents/cpp-learning/practice-1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sophia/Documents/cpp-learning/practice-1 /home/sophia/Documents/cpp-learning/practice-1 /home/sophia/Documents/cpp-learning/practice-1/build /home/sophia/Documents/cpp-learning/practice-1/build /home/sophia/Documents/cpp-learning/practice-1/build/CMakeFiles/my_cmake_exe.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/my_cmake_exe.dir/depend

