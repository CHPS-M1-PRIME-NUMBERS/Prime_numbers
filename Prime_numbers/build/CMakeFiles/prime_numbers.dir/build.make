# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jean-didier/Bureau/Projet/Prime_numbers/Prime_numbers

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jean-didier/Bureau/Projet/Prime_numbers/Prime_numbers/build

# Include any dependencies generated for this target.
include CMakeFiles/prime_numbers.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/prime_numbers.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/prime_numbers.dir/flags.make

CMakeFiles/prime_numbers.dir/main.cpp.o: CMakeFiles/prime_numbers.dir/flags.make
CMakeFiles/prime_numbers.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jean-didier/Bureau/Projet/Prime_numbers/Prime_numbers/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/prime_numbers.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/prime_numbers.dir/main.cpp.o -c /home/jean-didier/Bureau/Projet/Prime_numbers/Prime_numbers/main.cpp

CMakeFiles/prime_numbers.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/prime_numbers.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jean-didier/Bureau/Projet/Prime_numbers/Prime_numbers/main.cpp > CMakeFiles/prime_numbers.dir/main.cpp.i

CMakeFiles/prime_numbers.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/prime_numbers.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jean-didier/Bureau/Projet/Prime_numbers/Prime_numbers/main.cpp -o CMakeFiles/prime_numbers.dir/main.cpp.s

CMakeFiles/prime_numbers.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/prime_numbers.dir/main.cpp.o.requires

CMakeFiles/prime_numbers.dir/main.cpp.o.provides: CMakeFiles/prime_numbers.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/prime_numbers.dir/build.make CMakeFiles/prime_numbers.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/prime_numbers.dir/main.cpp.o.provides

CMakeFiles/prime_numbers.dir/main.cpp.o.provides.build: CMakeFiles/prime_numbers.dir/main.cpp.o


# Object files for target prime_numbers
prime_numbers_OBJECTS = \
"CMakeFiles/prime_numbers.dir/main.cpp.o"

# External object files for target prime_numbers
prime_numbers_EXTERNAL_OBJECTS =

prime_numbers: CMakeFiles/prime_numbers.dir/main.cpp.o
prime_numbers: CMakeFiles/prime_numbers.dir/build.make
prime_numbers: primality_proba/libprimality_proba.a
prime_numbers: primality_deter/libprimality_deter.a
prime_numbers: highly_composite/libhighly_composite.a
prime_numbers: CMakeFiles/prime_numbers.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jean-didier/Bureau/Projet/Prime_numbers/Prime_numbers/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable prime_numbers"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/prime_numbers.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/prime_numbers.dir/build: prime_numbers

.PHONY : CMakeFiles/prime_numbers.dir/build

CMakeFiles/prime_numbers.dir/requires: CMakeFiles/prime_numbers.dir/main.cpp.o.requires

.PHONY : CMakeFiles/prime_numbers.dir/requires

CMakeFiles/prime_numbers.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/prime_numbers.dir/cmake_clean.cmake
.PHONY : CMakeFiles/prime_numbers.dir/clean

CMakeFiles/prime_numbers.dir/depend:
	cd /home/jean-didier/Bureau/Projet/Prime_numbers/Prime_numbers/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jean-didier/Bureau/Projet/Prime_numbers/Prime_numbers /home/jean-didier/Bureau/Projet/Prime_numbers/Prime_numbers /home/jean-didier/Bureau/Projet/Prime_numbers/Prime_numbers/build /home/jean-didier/Bureau/Projet/Prime_numbers/Prime_numbers/build /home/jean-didier/Bureau/Projet/Prime_numbers/Prime_numbers/build/CMakeFiles/prime_numbers.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/prime_numbers.dir/depend

