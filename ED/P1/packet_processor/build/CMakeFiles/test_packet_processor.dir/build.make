# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/fran/Escritorio/Universidad/ED/P1/packet_processor

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/fran/Escritorio/Universidad/ED/P1/packet_processor/build

# Include any dependencies generated for this target.
include CMakeFiles/test_packet_processor.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test_packet_processor.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_packet_processor.dir/flags.make

CMakeFiles/test_packet_processor.dir/test_packet_processor.cpp.o: CMakeFiles/test_packet_processor.dir/flags.make
CMakeFiles/test_packet_processor.dir/test_packet_processor.cpp.o: ../test_packet_processor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fran/Escritorio/Universidad/ED/P1/packet_processor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test_packet_processor.dir/test_packet_processor.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_packet_processor.dir/test_packet_processor.cpp.o -c /home/fran/Escritorio/Universidad/ED/P1/packet_processor/test_packet_processor.cpp

CMakeFiles/test_packet_processor.dir/test_packet_processor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_packet_processor.dir/test_packet_processor.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/fran/Escritorio/Universidad/ED/P1/packet_processor/test_packet_processor.cpp > CMakeFiles/test_packet_processor.dir/test_packet_processor.cpp.i

CMakeFiles/test_packet_processor.dir/test_packet_processor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_packet_processor.dir/test_packet_processor.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/fran/Escritorio/Universidad/ED/P1/packet_processor/test_packet_processor.cpp -o CMakeFiles/test_packet_processor.dir/test_packet_processor.cpp.s

CMakeFiles/test_packet_processor.dir/packet_processor.cpp.o: CMakeFiles/test_packet_processor.dir/flags.make
CMakeFiles/test_packet_processor.dir/packet_processor.cpp.o: ../packet_processor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fran/Escritorio/Universidad/ED/P1/packet_processor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/test_packet_processor.dir/packet_processor.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_packet_processor.dir/packet_processor.cpp.o -c /home/fran/Escritorio/Universidad/ED/P1/packet_processor/packet_processor.cpp

CMakeFiles/test_packet_processor.dir/packet_processor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_packet_processor.dir/packet_processor.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/fran/Escritorio/Universidad/ED/P1/packet_processor/packet_processor.cpp > CMakeFiles/test_packet_processor.dir/packet_processor.cpp.i

CMakeFiles/test_packet_processor.dir/packet_processor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_packet_processor.dir/packet_processor.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/fran/Escritorio/Universidad/ED/P1/packet_processor/packet_processor.cpp -o CMakeFiles/test_packet_processor.dir/packet_processor.cpp.s

# Object files for target test_packet_processor
test_packet_processor_OBJECTS = \
"CMakeFiles/test_packet_processor.dir/test_packet_processor.cpp.o" \
"CMakeFiles/test_packet_processor.dir/packet_processor.cpp.o"

# External object files for target test_packet_processor
test_packet_processor_EXTERNAL_OBJECTS =

test_packet_processor: CMakeFiles/test_packet_processor.dir/test_packet_processor.cpp.o
test_packet_processor: CMakeFiles/test_packet_processor.dir/packet_processor.cpp.o
test_packet_processor: CMakeFiles/test_packet_processor.dir/build.make
test_packet_processor: CMakeFiles/test_packet_processor.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/fran/Escritorio/Universidad/ED/P1/packet_processor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable test_packet_processor"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_packet_processor.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_packet_processor.dir/build: test_packet_processor

.PHONY : CMakeFiles/test_packet_processor.dir/build

CMakeFiles/test_packet_processor.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_packet_processor.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_packet_processor.dir/clean

CMakeFiles/test_packet_processor.dir/depend:
	cd /home/fran/Escritorio/Universidad/ED/P1/packet_processor/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/fran/Escritorio/Universidad/ED/P1/packet_processor /home/fran/Escritorio/Universidad/ED/P1/packet_processor /home/fran/Escritorio/Universidad/ED/P1/packet_processor/build /home/fran/Escritorio/Universidad/ED/P1/packet_processor/build /home/fran/Escritorio/Universidad/ED/P1/packet_processor/build/CMakeFiles/test_packet_processor.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test_packet_processor.dir/depend

