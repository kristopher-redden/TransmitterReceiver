# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

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
CMAKE_COMMAND = /home/kristopher/Documents/clion-2017.2.2/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/kristopher/Documents/clion-2017.2.2/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kristopher/Documents/GitClone/TransmitterReceiver

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kristopher/Documents/GitClone/TransmitterReceiver/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/TransmitterReceiver.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/TransmitterReceiver.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TransmitterReceiver.dir/flags.make

CMakeFiles/TransmitterReceiver.dir/main.cpp.o: CMakeFiles/TransmitterReceiver.dir/flags.make
CMakeFiles/TransmitterReceiver.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kristopher/Documents/GitClone/TransmitterReceiver/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TransmitterReceiver.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TransmitterReceiver.dir/main.cpp.o -c /home/kristopher/Documents/GitClone/TransmitterReceiver/main.cpp

CMakeFiles/TransmitterReceiver.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TransmitterReceiver.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kristopher/Documents/GitClone/TransmitterReceiver/main.cpp > CMakeFiles/TransmitterReceiver.dir/main.cpp.i

CMakeFiles/TransmitterReceiver.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TransmitterReceiver.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kristopher/Documents/GitClone/TransmitterReceiver/main.cpp -o CMakeFiles/TransmitterReceiver.dir/main.cpp.s

CMakeFiles/TransmitterReceiver.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/TransmitterReceiver.dir/main.cpp.o.requires

CMakeFiles/TransmitterReceiver.dir/main.cpp.o.provides: CMakeFiles/TransmitterReceiver.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/TransmitterReceiver.dir/build.make CMakeFiles/TransmitterReceiver.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/TransmitterReceiver.dir/main.cpp.o.provides

CMakeFiles/TransmitterReceiver.dir/main.cpp.o.provides.build: CMakeFiles/TransmitterReceiver.dir/main.cpp.o


CMakeFiles/TransmitterReceiver.dir/PhysicalLayer.cpp.o: CMakeFiles/TransmitterReceiver.dir/flags.make
CMakeFiles/TransmitterReceiver.dir/PhysicalLayer.cpp.o: ../PhysicalLayer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kristopher/Documents/GitClone/TransmitterReceiver/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/TransmitterReceiver.dir/PhysicalLayer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TransmitterReceiver.dir/PhysicalLayer.cpp.o -c /home/kristopher/Documents/GitClone/TransmitterReceiver/PhysicalLayer.cpp

CMakeFiles/TransmitterReceiver.dir/PhysicalLayer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TransmitterReceiver.dir/PhysicalLayer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kristopher/Documents/GitClone/TransmitterReceiver/PhysicalLayer.cpp > CMakeFiles/TransmitterReceiver.dir/PhysicalLayer.cpp.i

CMakeFiles/TransmitterReceiver.dir/PhysicalLayer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TransmitterReceiver.dir/PhysicalLayer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kristopher/Documents/GitClone/TransmitterReceiver/PhysicalLayer.cpp -o CMakeFiles/TransmitterReceiver.dir/PhysicalLayer.cpp.s

CMakeFiles/TransmitterReceiver.dir/PhysicalLayer.cpp.o.requires:

.PHONY : CMakeFiles/TransmitterReceiver.dir/PhysicalLayer.cpp.o.requires

CMakeFiles/TransmitterReceiver.dir/PhysicalLayer.cpp.o.provides: CMakeFiles/TransmitterReceiver.dir/PhysicalLayer.cpp.o.requires
	$(MAKE) -f CMakeFiles/TransmitterReceiver.dir/build.make CMakeFiles/TransmitterReceiver.dir/PhysicalLayer.cpp.o.provides.build
.PHONY : CMakeFiles/TransmitterReceiver.dir/PhysicalLayer.cpp.o.provides

CMakeFiles/TransmitterReceiver.dir/PhysicalLayer.cpp.o.provides.build: CMakeFiles/TransmitterReceiver.dir/PhysicalLayer.cpp.o


CMakeFiles/TransmitterReceiver.dir/ApplicationLayer.cpp.o: CMakeFiles/TransmitterReceiver.dir/flags.make
CMakeFiles/TransmitterReceiver.dir/ApplicationLayer.cpp.o: ../ApplicationLayer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kristopher/Documents/GitClone/TransmitterReceiver/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/TransmitterReceiver.dir/ApplicationLayer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TransmitterReceiver.dir/ApplicationLayer.cpp.o -c /home/kristopher/Documents/GitClone/TransmitterReceiver/ApplicationLayer.cpp

CMakeFiles/TransmitterReceiver.dir/ApplicationLayer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TransmitterReceiver.dir/ApplicationLayer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kristopher/Documents/GitClone/TransmitterReceiver/ApplicationLayer.cpp > CMakeFiles/TransmitterReceiver.dir/ApplicationLayer.cpp.i

CMakeFiles/TransmitterReceiver.dir/ApplicationLayer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TransmitterReceiver.dir/ApplicationLayer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kristopher/Documents/GitClone/TransmitterReceiver/ApplicationLayer.cpp -o CMakeFiles/TransmitterReceiver.dir/ApplicationLayer.cpp.s

CMakeFiles/TransmitterReceiver.dir/ApplicationLayer.cpp.o.requires:

.PHONY : CMakeFiles/TransmitterReceiver.dir/ApplicationLayer.cpp.o.requires

CMakeFiles/TransmitterReceiver.dir/ApplicationLayer.cpp.o.provides: CMakeFiles/TransmitterReceiver.dir/ApplicationLayer.cpp.o.requires
	$(MAKE) -f CMakeFiles/TransmitterReceiver.dir/build.make CMakeFiles/TransmitterReceiver.dir/ApplicationLayer.cpp.o.provides.build
.PHONY : CMakeFiles/TransmitterReceiver.dir/ApplicationLayer.cpp.o.provides

CMakeFiles/TransmitterReceiver.dir/ApplicationLayer.cpp.o.provides.build: CMakeFiles/TransmitterReceiver.dir/ApplicationLayer.cpp.o


CMakeFiles/TransmitterReceiver.dir/DataLinkLayer.cpp.o: CMakeFiles/TransmitterReceiver.dir/flags.make
CMakeFiles/TransmitterReceiver.dir/DataLinkLayer.cpp.o: ../DataLinkLayer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kristopher/Documents/GitClone/TransmitterReceiver/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/TransmitterReceiver.dir/DataLinkLayer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TransmitterReceiver.dir/DataLinkLayer.cpp.o -c /home/kristopher/Documents/GitClone/TransmitterReceiver/DataLinkLayer.cpp

CMakeFiles/TransmitterReceiver.dir/DataLinkLayer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TransmitterReceiver.dir/DataLinkLayer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kristopher/Documents/GitClone/TransmitterReceiver/DataLinkLayer.cpp > CMakeFiles/TransmitterReceiver.dir/DataLinkLayer.cpp.i

CMakeFiles/TransmitterReceiver.dir/DataLinkLayer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TransmitterReceiver.dir/DataLinkLayer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kristopher/Documents/GitClone/TransmitterReceiver/DataLinkLayer.cpp -o CMakeFiles/TransmitterReceiver.dir/DataLinkLayer.cpp.s

CMakeFiles/TransmitterReceiver.dir/DataLinkLayer.cpp.o.requires:

.PHONY : CMakeFiles/TransmitterReceiver.dir/DataLinkLayer.cpp.o.requires

CMakeFiles/TransmitterReceiver.dir/DataLinkLayer.cpp.o.provides: CMakeFiles/TransmitterReceiver.dir/DataLinkLayer.cpp.o.requires
	$(MAKE) -f CMakeFiles/TransmitterReceiver.dir/build.make CMakeFiles/TransmitterReceiver.dir/DataLinkLayer.cpp.o.provides.build
.PHONY : CMakeFiles/TransmitterReceiver.dir/DataLinkLayer.cpp.o.provides

CMakeFiles/TransmitterReceiver.dir/DataLinkLayer.cpp.o.provides.build: CMakeFiles/TransmitterReceiver.dir/DataLinkLayer.cpp.o


# Object files for target TransmitterReceiver
TransmitterReceiver_OBJECTS = \
"CMakeFiles/TransmitterReceiver.dir/main.cpp.o" \
"CMakeFiles/TransmitterReceiver.dir/PhysicalLayer.cpp.o" \
"CMakeFiles/TransmitterReceiver.dir/ApplicationLayer.cpp.o" \
"CMakeFiles/TransmitterReceiver.dir/DataLinkLayer.cpp.o"

# External object files for target TransmitterReceiver
TransmitterReceiver_EXTERNAL_OBJECTS =

TransmitterReceiver: CMakeFiles/TransmitterReceiver.dir/main.cpp.o
TransmitterReceiver: CMakeFiles/TransmitterReceiver.dir/PhysicalLayer.cpp.o
TransmitterReceiver: CMakeFiles/TransmitterReceiver.dir/ApplicationLayer.cpp.o
TransmitterReceiver: CMakeFiles/TransmitterReceiver.dir/DataLinkLayer.cpp.o
TransmitterReceiver: CMakeFiles/TransmitterReceiver.dir/build.make
TransmitterReceiver: CMakeFiles/TransmitterReceiver.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kristopher/Documents/GitClone/TransmitterReceiver/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable TransmitterReceiver"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TransmitterReceiver.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TransmitterReceiver.dir/build: TransmitterReceiver

.PHONY : CMakeFiles/TransmitterReceiver.dir/build

CMakeFiles/TransmitterReceiver.dir/requires: CMakeFiles/TransmitterReceiver.dir/main.cpp.o.requires
CMakeFiles/TransmitterReceiver.dir/requires: CMakeFiles/TransmitterReceiver.dir/PhysicalLayer.cpp.o.requires
CMakeFiles/TransmitterReceiver.dir/requires: CMakeFiles/TransmitterReceiver.dir/ApplicationLayer.cpp.o.requires
CMakeFiles/TransmitterReceiver.dir/requires: CMakeFiles/TransmitterReceiver.dir/DataLinkLayer.cpp.o.requires

.PHONY : CMakeFiles/TransmitterReceiver.dir/requires

CMakeFiles/TransmitterReceiver.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TransmitterReceiver.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TransmitterReceiver.dir/clean

CMakeFiles/TransmitterReceiver.dir/depend:
	cd /home/kristopher/Documents/GitClone/TransmitterReceiver/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kristopher/Documents/GitClone/TransmitterReceiver /home/kristopher/Documents/GitClone/TransmitterReceiver /home/kristopher/Documents/GitClone/TransmitterReceiver/cmake-build-debug /home/kristopher/Documents/GitClone/TransmitterReceiver/cmake-build-debug /home/kristopher/Documents/GitClone/TransmitterReceiver/cmake-build-debug/CMakeFiles/TransmitterReceiver.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TransmitterReceiver.dir/depend

