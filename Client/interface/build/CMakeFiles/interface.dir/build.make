# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/sofia/Algo/Messenger/Client/interface

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sofia/Algo/Messenger/Client/interface/build

# Include any dependencies generated for this target.
include CMakeFiles/interface.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/interface.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/interface.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/interface.dir/flags.make

CMakeFiles/interface.dir/interface_autogen/mocs_compilation.cpp.o: CMakeFiles/interface.dir/flags.make
CMakeFiles/interface.dir/interface_autogen/mocs_compilation.cpp.o: interface_autogen/mocs_compilation.cpp
CMakeFiles/interface.dir/interface_autogen/mocs_compilation.cpp.o: CMakeFiles/interface.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sofia/Algo/Messenger/Client/interface/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/interface.dir/interface_autogen/mocs_compilation.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/interface.dir/interface_autogen/mocs_compilation.cpp.o -MF CMakeFiles/interface.dir/interface_autogen/mocs_compilation.cpp.o.d -o CMakeFiles/interface.dir/interface_autogen/mocs_compilation.cpp.o -c /home/sofia/Algo/Messenger/Client/interface/build/interface_autogen/mocs_compilation.cpp

CMakeFiles/interface.dir/interface_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/interface.dir/interface_autogen/mocs_compilation.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sofia/Algo/Messenger/Client/interface/build/interface_autogen/mocs_compilation.cpp > CMakeFiles/interface.dir/interface_autogen/mocs_compilation.cpp.i

CMakeFiles/interface.dir/interface_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/interface.dir/interface_autogen/mocs_compilation.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sofia/Algo/Messenger/Client/interface/build/interface_autogen/mocs_compilation.cpp -o CMakeFiles/interface.dir/interface_autogen/mocs_compilation.cpp.s

CMakeFiles/interface.dir/main.cpp.o: CMakeFiles/interface.dir/flags.make
CMakeFiles/interface.dir/main.cpp.o: ../main.cpp
CMakeFiles/interface.dir/main.cpp.o: CMakeFiles/interface.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sofia/Algo/Messenger/Client/interface/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/interface.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/interface.dir/main.cpp.o -MF CMakeFiles/interface.dir/main.cpp.o.d -o CMakeFiles/interface.dir/main.cpp.o -c /home/sofia/Algo/Messenger/Client/interface/main.cpp

CMakeFiles/interface.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/interface.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sofia/Algo/Messenger/Client/interface/main.cpp > CMakeFiles/interface.dir/main.cpp.i

CMakeFiles/interface.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/interface.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sofia/Algo/Messenger/Client/interface/main.cpp -o CMakeFiles/interface.dir/main.cpp.s

CMakeFiles/interface.dir/mainwindow.cpp.o: CMakeFiles/interface.dir/flags.make
CMakeFiles/interface.dir/mainwindow.cpp.o: ../mainwindow.cpp
CMakeFiles/interface.dir/mainwindow.cpp.o: CMakeFiles/interface.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sofia/Algo/Messenger/Client/interface/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/interface.dir/mainwindow.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/interface.dir/mainwindow.cpp.o -MF CMakeFiles/interface.dir/mainwindow.cpp.o.d -o CMakeFiles/interface.dir/mainwindow.cpp.o -c /home/sofia/Algo/Messenger/Client/interface/mainwindow.cpp

CMakeFiles/interface.dir/mainwindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/interface.dir/mainwindow.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sofia/Algo/Messenger/Client/interface/mainwindow.cpp > CMakeFiles/interface.dir/mainwindow.cpp.i

CMakeFiles/interface.dir/mainwindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/interface.dir/mainwindow.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sofia/Algo/Messenger/Client/interface/mainwindow.cpp -o CMakeFiles/interface.dir/mainwindow.cpp.s

CMakeFiles/interface.dir/registration.cpp.o: CMakeFiles/interface.dir/flags.make
CMakeFiles/interface.dir/registration.cpp.o: ../registration.cpp
CMakeFiles/interface.dir/registration.cpp.o: CMakeFiles/interface.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sofia/Algo/Messenger/Client/interface/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/interface.dir/registration.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/interface.dir/registration.cpp.o -MF CMakeFiles/interface.dir/registration.cpp.o.d -o CMakeFiles/interface.dir/registration.cpp.o -c /home/sofia/Algo/Messenger/Client/interface/registration.cpp

CMakeFiles/interface.dir/registration.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/interface.dir/registration.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sofia/Algo/Messenger/Client/interface/registration.cpp > CMakeFiles/interface.dir/registration.cpp.i

CMakeFiles/interface.dir/registration.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/interface.dir/registration.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sofia/Algo/Messenger/Client/interface/registration.cpp -o CMakeFiles/interface.dir/registration.cpp.s

CMakeFiles/interface.dir/autorization.cpp.o: CMakeFiles/interface.dir/flags.make
CMakeFiles/interface.dir/autorization.cpp.o: ../autorization.cpp
CMakeFiles/interface.dir/autorization.cpp.o: CMakeFiles/interface.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sofia/Algo/Messenger/Client/interface/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/interface.dir/autorization.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/interface.dir/autorization.cpp.o -MF CMakeFiles/interface.dir/autorization.cpp.o.d -o CMakeFiles/interface.dir/autorization.cpp.o -c /home/sofia/Algo/Messenger/Client/interface/autorization.cpp

CMakeFiles/interface.dir/autorization.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/interface.dir/autorization.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sofia/Algo/Messenger/Client/interface/autorization.cpp > CMakeFiles/interface.dir/autorization.cpp.i

CMakeFiles/interface.dir/autorization.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/interface.dir/autorization.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sofia/Algo/Messenger/Client/interface/autorization.cpp -o CMakeFiles/interface.dir/autorization.cpp.s

CMakeFiles/interface.dir/home/sofia/Algo/Messenger/Client/Client.cpp.o: CMakeFiles/interface.dir/flags.make
CMakeFiles/interface.dir/home/sofia/Algo/Messenger/Client/Client.cpp.o: /home/sofia/Algo/Messenger/Client/Client.cpp
CMakeFiles/interface.dir/home/sofia/Algo/Messenger/Client/Client.cpp.o: CMakeFiles/interface.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sofia/Algo/Messenger/Client/interface/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/interface.dir/home/sofia/Algo/Messenger/Client/Client.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/interface.dir/home/sofia/Algo/Messenger/Client/Client.cpp.o -MF CMakeFiles/interface.dir/home/sofia/Algo/Messenger/Client/Client.cpp.o.d -o CMakeFiles/interface.dir/home/sofia/Algo/Messenger/Client/Client.cpp.o -c /home/sofia/Algo/Messenger/Client/Client.cpp

CMakeFiles/interface.dir/home/sofia/Algo/Messenger/Client/Client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/interface.dir/home/sofia/Algo/Messenger/Client/Client.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sofia/Algo/Messenger/Client/Client.cpp > CMakeFiles/interface.dir/home/sofia/Algo/Messenger/Client/Client.cpp.i

CMakeFiles/interface.dir/home/sofia/Algo/Messenger/Client/Client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/interface.dir/home/sofia/Algo/Messenger/Client/Client.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sofia/Algo/Messenger/Client/Client.cpp -o CMakeFiles/interface.dir/home/sofia/Algo/Messenger/Client/Client.cpp.s

# Object files for target interface
interface_OBJECTS = \
"CMakeFiles/interface.dir/interface_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/interface.dir/main.cpp.o" \
"CMakeFiles/interface.dir/mainwindow.cpp.o" \
"CMakeFiles/interface.dir/registration.cpp.o" \
"CMakeFiles/interface.dir/autorization.cpp.o" \
"CMakeFiles/interface.dir/home/sofia/Algo/Messenger/Client/Client.cpp.o"

# External object files for target interface
interface_EXTERNAL_OBJECTS =

interface: CMakeFiles/interface.dir/interface_autogen/mocs_compilation.cpp.o
interface: CMakeFiles/interface.dir/main.cpp.o
interface: CMakeFiles/interface.dir/mainwindow.cpp.o
interface: CMakeFiles/interface.dir/registration.cpp.o
interface: CMakeFiles/interface.dir/autorization.cpp.o
interface: CMakeFiles/interface.dir/home/sofia/Algo/Messenger/Client/Client.cpp.o
interface: CMakeFiles/interface.dir/build.make
interface: /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3
interface: /usr/lib/x86_64-linux-gnu/libQt5Gui.so.5.15.3
interface: /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.15.3
interface: CMakeFiles/interface.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sofia/Algo/Messenger/Client/interface/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable interface"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/interface.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/interface.dir/build: interface
.PHONY : CMakeFiles/interface.dir/build

CMakeFiles/interface.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/interface.dir/cmake_clean.cmake
.PHONY : CMakeFiles/interface.dir/clean

CMakeFiles/interface.dir/depend:
	cd /home/sofia/Algo/Messenger/Client/interface/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sofia/Algo/Messenger/Client/interface /home/sofia/Algo/Messenger/Client/interface /home/sofia/Algo/Messenger/Client/interface/build /home/sofia/Algo/Messenger/Client/interface/build /home/sofia/Algo/Messenger/Client/interface/build/CMakeFiles/interface.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/interface.dir/depend

