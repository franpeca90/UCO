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
CMAKE_SOURCE_DIR = /home/fran/Escritorio/Universidad/FSIV/P10

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/fran/Escritorio/Universidad/FSIV/P10/build

# Include any dependencies generated for this target.
include CMakeFiles/train_val.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/train_val.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/train_val.dir/flags.make

CMakeFiles/train_val.dir/train_val.cpp.o: CMakeFiles/train_val.dir/flags.make
CMakeFiles/train_val.dir/train_val.cpp.o: ../train_val.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fran/Escritorio/Universidad/FSIV/P10/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/train_val.dir/train_val.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/train_val.dir/train_val.cpp.o -c /home/fran/Escritorio/Universidad/FSIV/P10/train_val.cpp

CMakeFiles/train_val.dir/train_val.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/train_val.dir/train_val.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/fran/Escritorio/Universidad/FSIV/P10/train_val.cpp > CMakeFiles/train_val.dir/train_val.cpp.i

CMakeFiles/train_val.dir/train_val.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/train_val.dir/train_val.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/fran/Escritorio/Universidad/FSIV/P10/train_val.cpp -o CMakeFiles/train_val.dir/train_val.cpp.s

CMakeFiles/train_val.dir/common_code.cpp.o: CMakeFiles/train_val.dir/flags.make
CMakeFiles/train_val.dir/common_code.cpp.o: ../common_code.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fran/Escritorio/Universidad/FSIV/P10/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/train_val.dir/common_code.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/train_val.dir/common_code.cpp.o -c /home/fran/Escritorio/Universidad/FSIV/P10/common_code.cpp

CMakeFiles/train_val.dir/common_code.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/train_val.dir/common_code.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/fran/Escritorio/Universidad/FSIV/P10/common_code.cpp > CMakeFiles/train_val.dir/common_code.cpp.i

CMakeFiles/train_val.dir/common_code.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/train_val.dir/common_code.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/fran/Escritorio/Universidad/FSIV/P10/common_code.cpp -o CMakeFiles/train_val.dir/common_code.cpp.s

CMakeFiles/train_val.dir/metrics.cpp.o: CMakeFiles/train_val.dir/flags.make
CMakeFiles/train_val.dir/metrics.cpp.o: ../metrics.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fran/Escritorio/Universidad/FSIV/P10/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/train_val.dir/metrics.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/train_val.dir/metrics.cpp.o -c /home/fran/Escritorio/Universidad/FSIV/P10/metrics.cpp

CMakeFiles/train_val.dir/metrics.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/train_val.dir/metrics.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/fran/Escritorio/Universidad/FSIV/P10/metrics.cpp > CMakeFiles/train_val.dir/metrics.cpp.i

CMakeFiles/train_val.dir/metrics.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/train_val.dir/metrics.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/fran/Escritorio/Universidad/FSIV/P10/metrics.cpp -o CMakeFiles/train_val.dir/metrics.cpp.s

# Object files for target train_val
train_val_OBJECTS = \
"CMakeFiles/train_val.dir/train_val.cpp.o" \
"CMakeFiles/train_val.dir/common_code.cpp.o" \
"CMakeFiles/train_val.dir/metrics.cpp.o"

# External object files for target train_val
train_val_EXTERNAL_OBJECTS =

train_val: CMakeFiles/train_val.dir/train_val.cpp.o
train_val: CMakeFiles/train_val.dir/common_code.cpp.o
train_val: CMakeFiles/train_val.dir/metrics.cpp.o
train_val: CMakeFiles/train_val.dir/build.make
train_val: /usr/lib/x86_64-linux-gnu/libopencv_stitching.so.4.5.3
train_val: /usr/lib/x86_64-linux-gnu/libopencv_alphamat.so.4.5.3
train_val: /usr/lib/x86_64-linux-gnu/libopencv_aruco.so.4.5.3
train_val: /usr/lib/x86_64-linux-gnu/libopencv_barcode.so.4.5.3
train_val: /usr/lib/x86_64-linux-gnu/libopencv_bgsegm.so.4.5.3
train_val: /usr/lib/x86_64-linux-gnu/libopencv_bioinspired.so.4.5.3
train_val: /usr/lib/x86_64-linux-gnu/libopencv_ccalib.so.4.5.3
train_val: /usr/lib/x86_64-linux-gnu/libopencv_dnn_objdetect.so.4.5.3
train_val: /usr/lib/x86_64-linux-gnu/libopencv_dnn_superres.so.4.5.3
train_val: /usr/lib/x86_64-linux-gnu/libopencv_dpm.so.4.5.3
train_val: /usr/lib/x86_64-linux-gnu/libopencv_face.so.4.5.3
train_val: /usr/lib/x86_64-linux-gnu/libopencv_freetype.so.4.5.3
train_val: /usr/lib/x86_64-linux-gnu/libopencv_fuzzy.so.4.5.3
train_val: /usr/lib/x86_64-linux-gnu/libopencv_hdf.so.4.5.3
train_val: /usr/lib/x86_64-linux-gnu/libopencv_hfs.so.4.5.3
train_val: /usr/lib/x86_64-linux-gnu/libopencv_img_hash.so.4.5.3
train_val: /usr/lib/x86_64-linux-gnu/libopencv_intensity_transform.so.4.5.3
train_val: /usr/lib/x86_64-linux-gnu/libopencv_line_descriptor.so.4.5.3
train_val: /usr/lib/x86_64-linux-gnu/libopencv_mcc.so.4.5.3
train_val: /usr/lib/x86_64-linux-gnu/libopencv_quality.so.4.5.3
train_val: /usr/lib/x86_64-linux-gnu/libopencv_rapid.so.4.5.3
train_val: /usr/lib/x86_64-linux-gnu/libopencv_reg.so.4.5.3
train_val: /usr/lib/x86_64-linux-gnu/libopencv_rgbd.so.4.5.3
train_val: /usr/lib/x86_64-linux-gnu/libopencv_saliency.so.4.5.3
train_val: /usr/lib/x86_64-linux-gnu/libopencv_shape.so.4.5.3
train_val: /usr/lib/x86_64-linux-gnu/libopencv_stereo.so.4.5.3
train_val: /usr/lib/x86_64-linux-gnu/libopencv_structured_light.so.4.5.3
train_val: /usr/lib/x86_64-linux-gnu/libopencv_superres.so.4.5.3
train_val: /usr/lib/x86_64-linux-gnu/libopencv_surface_matching.so.4.5.3
train_val: /usr/lib/x86_64-linux-gnu/libopencv_tracking.so.4.5.3
train_val: /usr/lib/x86_64-linux-gnu/libopencv_videostab.so.4.5.3
train_val: /usr/lib/x86_64-linux-gnu/libopencv_viz.so.4.5.3
train_val: /usr/lib/x86_64-linux-gnu/libopencv_wechat_qrcode.so.4.5.3
train_val: /usr/lib/x86_64-linux-gnu/libopencv_xobjdetect.so.4.5.3
train_val: /usr/lib/x86_64-linux-gnu/libopencv_xphoto.so.4.5.3
train_val: /usr/lib/x86_64-linux-gnu/libopencv_highgui.so.4.5.3
train_val: /usr/lib/x86_64-linux-gnu/libopencv_datasets.so.4.5.3
train_val: /usr/lib/x86_64-linux-gnu/libopencv_plot.so.4.5.3
train_val: /usr/lib/x86_64-linux-gnu/libopencv_text.so.4.5.3
train_val: /usr/lib/x86_64-linux-gnu/libopencv_ml.so.4.5.3
train_val: /usr/lib/x86_64-linux-gnu/libopencv_phase_unwrapping.so.4.5.3
train_val: /usr/lib/x86_64-linux-gnu/libopencv_optflow.so.4.5.3
train_val: /usr/lib/x86_64-linux-gnu/libopencv_ximgproc.so.4.5.3
train_val: /usr/lib/x86_64-linux-gnu/libopencv_video.so.4.5.3
train_val: /usr/lib/x86_64-linux-gnu/libopencv_videoio.so.4.5.3
train_val: /usr/lib/x86_64-linux-gnu/libopencv_dnn.so.4.5.3
train_val: /usr/lib/x86_64-linux-gnu/libopencv_imgcodecs.so.4.5.3
train_val: /usr/lib/x86_64-linux-gnu/libopencv_objdetect.so.4.5.3
train_val: /usr/lib/x86_64-linux-gnu/libopencv_calib3d.so.4.5.3
train_val: /usr/lib/x86_64-linux-gnu/libopencv_features2d.so.4.5.3
train_val: /usr/lib/x86_64-linux-gnu/libopencv_flann.so.4.5.3
train_val: /usr/lib/x86_64-linux-gnu/libopencv_photo.so.4.5.3
train_val: /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so.4.5.3
train_val: /usr/lib/x86_64-linux-gnu/libopencv_core.so.4.5.3
train_val: CMakeFiles/train_val.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/fran/Escritorio/Universidad/FSIV/P10/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable train_val"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/train_val.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/train_val.dir/build: train_val

.PHONY : CMakeFiles/train_val.dir/build

CMakeFiles/train_val.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/train_val.dir/cmake_clean.cmake
.PHONY : CMakeFiles/train_val.dir/clean

CMakeFiles/train_val.dir/depend:
	cd /home/fran/Escritorio/Universidad/FSIV/P10/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/fran/Escritorio/Universidad/FSIV/P10 /home/fran/Escritorio/Universidad/FSIV/P10 /home/fran/Escritorio/Universidad/FSIV/P10/build /home/fran/Escritorio/Universidad/FSIV/P10/build /home/fran/Escritorio/Universidad/FSIV/P10/build/CMakeFiles/train_val.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/train_val.dir/depend

