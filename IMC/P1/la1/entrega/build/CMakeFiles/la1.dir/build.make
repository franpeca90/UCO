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
CMAKE_SOURCE_DIR = /home/fran/Escritorio/Universidad/IMC/P1/la1/entrega

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/fran/Escritorio/Universidad/IMC/P1/la1/entrega/build

# Include any dependencies generated for this target.
include CMakeFiles/la1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/la1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/la1.dir/flags.make

CMakeFiles/la1.dir/imc/MultilayerPerceptron.cpp.o: CMakeFiles/la1.dir/flags.make
CMakeFiles/la1.dir/imc/MultilayerPerceptron.cpp.o: ../imc/MultilayerPerceptron.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fran/Escritorio/Universidad/IMC/P1/la1/entrega/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/la1.dir/imc/MultilayerPerceptron.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/la1.dir/imc/MultilayerPerceptron.cpp.o -c /home/fran/Escritorio/Universidad/IMC/P1/la1/entrega/imc/MultilayerPerceptron.cpp

CMakeFiles/la1.dir/imc/MultilayerPerceptron.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/la1.dir/imc/MultilayerPerceptron.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/fran/Escritorio/Universidad/IMC/P1/la1/entrega/imc/MultilayerPerceptron.cpp > CMakeFiles/la1.dir/imc/MultilayerPerceptron.cpp.i

CMakeFiles/la1.dir/imc/MultilayerPerceptron.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/la1.dir/imc/MultilayerPerceptron.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/fran/Escritorio/Universidad/IMC/P1/la1/entrega/imc/MultilayerPerceptron.cpp -o CMakeFiles/la1.dir/imc/MultilayerPerceptron.cpp.s

CMakeFiles/la1.dir/la1.cpp.o: CMakeFiles/la1.dir/flags.make
CMakeFiles/la1.dir/la1.cpp.o: ../la1.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fran/Escritorio/Universidad/IMC/P1/la1/entrega/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/la1.dir/la1.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/la1.dir/la1.cpp.o -c /home/fran/Escritorio/Universidad/IMC/P1/la1/entrega/la1.cpp

CMakeFiles/la1.dir/la1.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/la1.dir/la1.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/fran/Escritorio/Universidad/IMC/P1/la1/entrega/la1.cpp > CMakeFiles/la1.dir/la1.cpp.i

CMakeFiles/la1.dir/la1.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/la1.dir/la1.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/fran/Escritorio/Universidad/IMC/P1/la1/entrega/la1.cpp -o CMakeFiles/la1.dir/la1.cpp.s

# Object files for target la1
la1_OBJECTS = \
"CMakeFiles/la1.dir/imc/MultilayerPerceptron.cpp.o" \
"CMakeFiles/la1.dir/la1.cpp.o"

# External object files for target la1
la1_EXTERNAL_OBJECTS =

la1: CMakeFiles/la1.dir/imc/MultilayerPerceptron.cpp.o
la1: CMakeFiles/la1.dir/la1.cpp.o
la1: CMakeFiles/la1.dir/build.make
la1: CMakeFiles/la1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/fran/Escritorio/Universidad/IMC/P1/la1/entrega/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable la1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/la1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/la1.dir/build: la1

.PHONY : CMakeFiles/la1.dir/build

CMakeFiles/la1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/la1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/la1.dir/clean

CMakeFiles/la1.dir/depend:
	cd /home/fran/Escritorio/Universidad/IMC/P1/la1/entrega/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/fran/Escritorio/Universidad/IMC/P1/la1/entrega /home/fran/Escritorio/Universidad/IMC/P1/la1/entrega /home/fran/Escritorio/Universidad/IMC/P1/la1/entrega/build /home/fran/Escritorio/Universidad/IMC/P1/la1/entrega/build /home/fran/Escritorio/Universidad/IMC/P1/la1/entrega/build/CMakeFiles/la1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/la1.dir/depend
