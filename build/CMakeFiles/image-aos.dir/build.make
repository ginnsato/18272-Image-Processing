# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/ginnsato/VisualStudioProjects/CS250-Project1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/ginnsato/VisualStudioProjects/CS250-Project1/build

# Include any dependencies generated for this target.
include CMakeFiles/image-aos.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/image-aos.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/image-aos.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/image-aos.dir/flags.make

CMakeFiles/image-aos.dir/image-aos/main-aos.cpp.o: CMakeFiles/image-aos.dir/flags.make
CMakeFiles/image-aos.dir/image-aos/main-aos.cpp.o: /Users/ginnsato/VisualStudioProjects/CS250-Project1/image-aos/main-aos.cpp
CMakeFiles/image-aos.dir/image-aos/main-aos.cpp.o: CMakeFiles/image-aos.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ginnsato/VisualStudioProjects/CS250-Project1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/image-aos.dir/image-aos/main-aos.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/image-aos.dir/image-aos/main-aos.cpp.o -MF CMakeFiles/image-aos.dir/image-aos/main-aos.cpp.o.d -o CMakeFiles/image-aos.dir/image-aos/main-aos.cpp.o -c /Users/ginnsato/VisualStudioProjects/CS250-Project1/image-aos/main-aos.cpp

CMakeFiles/image-aos.dir/image-aos/main-aos.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/image-aos.dir/image-aos/main-aos.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ginnsato/VisualStudioProjects/CS250-Project1/image-aos/main-aos.cpp > CMakeFiles/image-aos.dir/image-aos/main-aos.cpp.i

CMakeFiles/image-aos.dir/image-aos/main-aos.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/image-aos.dir/image-aos/main-aos.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ginnsato/VisualStudioProjects/CS250-Project1/image-aos/main-aos.cpp -o CMakeFiles/image-aos.dir/image-aos/main-aos.cpp.s

# Object files for target image-aos
image__aos_OBJECTS = \
"CMakeFiles/image-aos.dir/image-aos/main-aos.cpp.o"

# External object files for target image-aos
image__aos_EXTERNAL_OBJECTS =

image-aos: CMakeFiles/image-aos.dir/image-aos/main-aos.cpp.o
image-aos: CMakeFiles/image-aos.dir/build.make
image-aos: libcommon.a
image-aos: libaos.a
image-aos: CMakeFiles/image-aos.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/ginnsato/VisualStudioProjects/CS250-Project1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable image-aos"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/image-aos.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/image-aos.dir/build: image-aos
.PHONY : CMakeFiles/image-aos.dir/build

CMakeFiles/image-aos.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/image-aos.dir/cmake_clean.cmake
.PHONY : CMakeFiles/image-aos.dir/clean

CMakeFiles/image-aos.dir/depend:
	cd /Users/ginnsato/VisualStudioProjects/CS250-Project1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/ginnsato/VisualStudioProjects/CS250-Project1 /Users/ginnsato/VisualStudioProjects/CS250-Project1 /Users/ginnsato/VisualStudioProjects/CS250-Project1/build /Users/ginnsato/VisualStudioProjects/CS250-Project1/build /Users/ginnsato/VisualStudioProjects/CS250-Project1/build/CMakeFiles/image-aos.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/image-aos.dir/depend

