# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/emilyberlinghoff/Desktop/School/Year 3/CS3388/Assignment 5"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/emilyberlinghoff/Desktop/School/Year 3/CS3388/Assignment 5/build"

# Include any dependencies generated for this target.
include CMakeFiles/marching_cubes.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/marching_cubes.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/marching_cubes.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/marching_cubes.dir/flags.make

CMakeFiles/marching_cubes.dir/codegen:
.PHONY : CMakeFiles/marching_cubes.dir/codegen

CMakeFiles/marching_cubes.dir/src/main.cpp.o: CMakeFiles/marching_cubes.dir/flags.make
CMakeFiles/marching_cubes.dir/src/main.cpp.o: /Users/emilyberlinghoff/Desktop/School/Year\ 3/CS3388/Assignment\ 5/src/main.cpp
CMakeFiles/marching_cubes.dir/src/main.cpp.o: CMakeFiles/marching_cubes.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/emilyberlinghoff/Desktop/School/Year 3/CS3388/Assignment 5/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/marching_cubes.dir/src/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/marching_cubes.dir/src/main.cpp.o -MF CMakeFiles/marching_cubes.dir/src/main.cpp.o.d -o CMakeFiles/marching_cubes.dir/src/main.cpp.o -c "/Users/emilyberlinghoff/Desktop/School/Year 3/CS3388/Assignment 5/src/main.cpp"

CMakeFiles/marching_cubes.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/marching_cubes.dir/src/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/emilyberlinghoff/Desktop/School/Year 3/CS3388/Assignment 5/src/main.cpp" > CMakeFiles/marching_cubes.dir/src/main.cpp.i

CMakeFiles/marching_cubes.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/marching_cubes.dir/src/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/emilyberlinghoff/Desktop/School/Year 3/CS3388/Assignment 5/src/main.cpp" -o CMakeFiles/marching_cubes.dir/src/main.cpp.s

CMakeFiles/marching_cubes.dir/src/marching_cubes.cpp.o: CMakeFiles/marching_cubes.dir/flags.make
CMakeFiles/marching_cubes.dir/src/marching_cubes.cpp.o: /Users/emilyberlinghoff/Desktop/School/Year\ 3/CS3388/Assignment\ 5/src/marching_cubes.cpp
CMakeFiles/marching_cubes.dir/src/marching_cubes.cpp.o: CMakeFiles/marching_cubes.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/emilyberlinghoff/Desktop/School/Year 3/CS3388/Assignment 5/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/marching_cubes.dir/src/marching_cubes.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/marching_cubes.dir/src/marching_cubes.cpp.o -MF CMakeFiles/marching_cubes.dir/src/marching_cubes.cpp.o.d -o CMakeFiles/marching_cubes.dir/src/marching_cubes.cpp.o -c "/Users/emilyberlinghoff/Desktop/School/Year 3/CS3388/Assignment 5/src/marching_cubes.cpp"

CMakeFiles/marching_cubes.dir/src/marching_cubes.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/marching_cubes.dir/src/marching_cubes.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/emilyberlinghoff/Desktop/School/Year 3/CS3388/Assignment 5/src/marching_cubes.cpp" > CMakeFiles/marching_cubes.dir/src/marching_cubes.cpp.i

CMakeFiles/marching_cubes.dir/src/marching_cubes.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/marching_cubes.dir/src/marching_cubes.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/emilyberlinghoff/Desktop/School/Year 3/CS3388/Assignment 5/src/marching_cubes.cpp" -o CMakeFiles/marching_cubes.dir/src/marching_cubes.cpp.s

CMakeFiles/marching_cubes.dir/src/rendering.cpp.o: CMakeFiles/marching_cubes.dir/flags.make
CMakeFiles/marching_cubes.dir/src/rendering.cpp.o: /Users/emilyberlinghoff/Desktop/School/Year\ 3/CS3388/Assignment\ 5/src/rendering.cpp
CMakeFiles/marching_cubes.dir/src/rendering.cpp.o: CMakeFiles/marching_cubes.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/emilyberlinghoff/Desktop/School/Year 3/CS3388/Assignment 5/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/marching_cubes.dir/src/rendering.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/marching_cubes.dir/src/rendering.cpp.o -MF CMakeFiles/marching_cubes.dir/src/rendering.cpp.o.d -o CMakeFiles/marching_cubes.dir/src/rendering.cpp.o -c "/Users/emilyberlinghoff/Desktop/School/Year 3/CS3388/Assignment 5/src/rendering.cpp"

CMakeFiles/marching_cubes.dir/src/rendering.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/marching_cubes.dir/src/rendering.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/emilyberlinghoff/Desktop/School/Year 3/CS3388/Assignment 5/src/rendering.cpp" > CMakeFiles/marching_cubes.dir/src/rendering.cpp.i

CMakeFiles/marching_cubes.dir/src/rendering.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/marching_cubes.dir/src/rendering.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/emilyberlinghoff/Desktop/School/Year 3/CS3388/Assignment 5/src/rendering.cpp" -o CMakeFiles/marching_cubes.dir/src/rendering.cpp.s

CMakeFiles/marching_cubes.dir/src/camera.cpp.o: CMakeFiles/marching_cubes.dir/flags.make
CMakeFiles/marching_cubes.dir/src/camera.cpp.o: /Users/emilyberlinghoff/Desktop/School/Year\ 3/CS3388/Assignment\ 5/src/camera.cpp
CMakeFiles/marching_cubes.dir/src/camera.cpp.o: CMakeFiles/marching_cubes.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/emilyberlinghoff/Desktop/School/Year 3/CS3388/Assignment 5/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/marching_cubes.dir/src/camera.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/marching_cubes.dir/src/camera.cpp.o -MF CMakeFiles/marching_cubes.dir/src/camera.cpp.o.d -o CMakeFiles/marching_cubes.dir/src/camera.cpp.o -c "/Users/emilyberlinghoff/Desktop/School/Year 3/CS3388/Assignment 5/src/camera.cpp"

CMakeFiles/marching_cubes.dir/src/camera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/marching_cubes.dir/src/camera.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/emilyberlinghoff/Desktop/School/Year 3/CS3388/Assignment 5/src/camera.cpp" > CMakeFiles/marching_cubes.dir/src/camera.cpp.i

CMakeFiles/marching_cubes.dir/src/camera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/marching_cubes.dir/src/camera.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/emilyberlinghoff/Desktop/School/Year 3/CS3388/Assignment 5/src/camera.cpp" -o CMakeFiles/marching_cubes.dir/src/camera.cpp.s

CMakeFiles/marching_cubes.dir/src/shaders.cpp.o: CMakeFiles/marching_cubes.dir/flags.make
CMakeFiles/marching_cubes.dir/src/shaders.cpp.o: /Users/emilyberlinghoff/Desktop/School/Year\ 3/CS3388/Assignment\ 5/src/shaders.cpp
CMakeFiles/marching_cubes.dir/src/shaders.cpp.o: CMakeFiles/marching_cubes.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/emilyberlinghoff/Desktop/School/Year 3/CS3388/Assignment 5/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/marching_cubes.dir/src/shaders.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/marching_cubes.dir/src/shaders.cpp.o -MF CMakeFiles/marching_cubes.dir/src/shaders.cpp.o.d -o CMakeFiles/marching_cubes.dir/src/shaders.cpp.o -c "/Users/emilyberlinghoff/Desktop/School/Year 3/CS3388/Assignment 5/src/shaders.cpp"

CMakeFiles/marching_cubes.dir/src/shaders.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/marching_cubes.dir/src/shaders.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/emilyberlinghoff/Desktop/School/Year 3/CS3388/Assignment 5/src/shaders.cpp" > CMakeFiles/marching_cubes.dir/src/shaders.cpp.i

CMakeFiles/marching_cubes.dir/src/shaders.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/marching_cubes.dir/src/shaders.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/emilyberlinghoff/Desktop/School/Year 3/CS3388/Assignment 5/src/shaders.cpp" -o CMakeFiles/marching_cubes.dir/src/shaders.cpp.s

CMakeFiles/marching_cubes.dir/src/utils.cpp.o: CMakeFiles/marching_cubes.dir/flags.make
CMakeFiles/marching_cubes.dir/src/utils.cpp.o: /Users/emilyberlinghoff/Desktop/School/Year\ 3/CS3388/Assignment\ 5/src/utils.cpp
CMakeFiles/marching_cubes.dir/src/utils.cpp.o: CMakeFiles/marching_cubes.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/emilyberlinghoff/Desktop/School/Year 3/CS3388/Assignment 5/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/marching_cubes.dir/src/utils.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/marching_cubes.dir/src/utils.cpp.o -MF CMakeFiles/marching_cubes.dir/src/utils.cpp.o.d -o CMakeFiles/marching_cubes.dir/src/utils.cpp.o -c "/Users/emilyberlinghoff/Desktop/School/Year 3/CS3388/Assignment 5/src/utils.cpp"

CMakeFiles/marching_cubes.dir/src/utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/marching_cubes.dir/src/utils.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/emilyberlinghoff/Desktop/School/Year 3/CS3388/Assignment 5/src/utils.cpp" > CMakeFiles/marching_cubes.dir/src/utils.cpp.i

CMakeFiles/marching_cubes.dir/src/utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/marching_cubes.dir/src/utils.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/emilyberlinghoff/Desktop/School/Year 3/CS3388/Assignment 5/src/utils.cpp" -o CMakeFiles/marching_cubes.dir/src/utils.cpp.s

# Object files for target marching_cubes
marching_cubes_OBJECTS = \
"CMakeFiles/marching_cubes.dir/src/main.cpp.o" \
"CMakeFiles/marching_cubes.dir/src/marching_cubes.cpp.o" \
"CMakeFiles/marching_cubes.dir/src/rendering.cpp.o" \
"CMakeFiles/marching_cubes.dir/src/camera.cpp.o" \
"CMakeFiles/marching_cubes.dir/src/shaders.cpp.o" \
"CMakeFiles/marching_cubes.dir/src/utils.cpp.o"

# External object files for target marching_cubes
marching_cubes_EXTERNAL_OBJECTS =

marching_cubes: CMakeFiles/marching_cubes.dir/src/main.cpp.o
marching_cubes: CMakeFiles/marching_cubes.dir/src/marching_cubes.cpp.o
marching_cubes: CMakeFiles/marching_cubes.dir/src/rendering.cpp.o
marching_cubes: CMakeFiles/marching_cubes.dir/src/camera.cpp.o
marching_cubes: CMakeFiles/marching_cubes.dir/src/shaders.cpp.o
marching_cubes: CMakeFiles/marching_cubes.dir/src/utils.cpp.o
marching_cubes: CMakeFiles/marching_cubes.dir/build.make
marching_cubes: /Library/Developer/CommandLineTools/SDKs/MacOSX15.2.sdk/System/Library/Frameworks/OpenGL.framework
marching_cubes: /opt/homebrew/lib/libGLEW.2.2.0.dylib
marching_cubes: CMakeFiles/marching_cubes.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="/Users/emilyberlinghoff/Desktop/School/Year 3/CS3388/Assignment 5/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable marching_cubes"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/marching_cubes.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/marching_cubes.dir/build: marching_cubes
.PHONY : CMakeFiles/marching_cubes.dir/build

CMakeFiles/marching_cubes.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/marching_cubes.dir/cmake_clean.cmake
.PHONY : CMakeFiles/marching_cubes.dir/clean

CMakeFiles/marching_cubes.dir/depend:
	cd "/Users/emilyberlinghoff/Desktop/School/Year 3/CS3388/Assignment 5/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/emilyberlinghoff/Desktop/School/Year 3/CS3388/Assignment 5" "/Users/emilyberlinghoff/Desktop/School/Year 3/CS3388/Assignment 5" "/Users/emilyberlinghoff/Desktop/School/Year 3/CS3388/Assignment 5/build" "/Users/emilyberlinghoff/Desktop/School/Year 3/CS3388/Assignment 5/build" "/Users/emilyberlinghoff/Desktop/School/Year 3/CS3388/Assignment 5/build/CMakeFiles/marching_cubes.dir/DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/marching_cubes.dir/depend

