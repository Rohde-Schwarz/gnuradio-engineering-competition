# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_COMMAND = /home/zhiwei/clion-2017.1.1/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/zhiwei/clion-2017.1.1/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/zhiwei/WorkSpace/gnuradio

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zhiwei/WorkSpace/gnuradio/cmake-build-debug

# Include any dependencies generated for this target.
include gnuradio-runtime/lib/pmt/CMakeFiles/gr_pmt_test.dir/depend.make

# Include the progress variables for this target.
include gnuradio-runtime/lib/pmt/CMakeFiles/gr_pmt_test.dir/progress.make

# Include the compile flags for this target's objects.
include gnuradio-runtime/lib/pmt/CMakeFiles/gr_pmt_test.dir/flags.make

gnuradio-runtime/lib/pmt/CMakeFiles/gr_pmt_test.dir/test_pmt.cc.o: gnuradio-runtime/lib/pmt/CMakeFiles/gr_pmt_test.dir/flags.make
gnuradio-runtime/lib/pmt/CMakeFiles/gr_pmt_test.dir/test_pmt.cc.o: ../gnuradio-runtime/lib/pmt/test_pmt.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhiwei/WorkSpace/gnuradio/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object gnuradio-runtime/lib/pmt/CMakeFiles/gr_pmt_test.dir/test_pmt.cc.o"
	cd /home/zhiwei/WorkSpace/gnuradio/cmake-build-debug/gnuradio-runtime/lib/pmt && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gr_pmt_test.dir/test_pmt.cc.o -c /home/zhiwei/WorkSpace/gnuradio/gnuradio-runtime/lib/pmt/test_pmt.cc

gnuradio-runtime/lib/pmt/CMakeFiles/gr_pmt_test.dir/test_pmt.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gr_pmt_test.dir/test_pmt.cc.i"
	cd /home/zhiwei/WorkSpace/gnuradio/cmake-build-debug/gnuradio-runtime/lib/pmt && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhiwei/WorkSpace/gnuradio/gnuradio-runtime/lib/pmt/test_pmt.cc > CMakeFiles/gr_pmt_test.dir/test_pmt.cc.i

gnuradio-runtime/lib/pmt/CMakeFiles/gr_pmt_test.dir/test_pmt.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gr_pmt_test.dir/test_pmt.cc.s"
	cd /home/zhiwei/WorkSpace/gnuradio/cmake-build-debug/gnuradio-runtime/lib/pmt && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhiwei/WorkSpace/gnuradio/gnuradio-runtime/lib/pmt/test_pmt.cc -o CMakeFiles/gr_pmt_test.dir/test_pmt.cc.s

gnuradio-runtime/lib/pmt/CMakeFiles/gr_pmt_test.dir/test_pmt.cc.o.requires:

.PHONY : gnuradio-runtime/lib/pmt/CMakeFiles/gr_pmt_test.dir/test_pmt.cc.o.requires

gnuradio-runtime/lib/pmt/CMakeFiles/gr_pmt_test.dir/test_pmt.cc.o.provides: gnuradio-runtime/lib/pmt/CMakeFiles/gr_pmt_test.dir/test_pmt.cc.o.requires
	$(MAKE) -f gnuradio-runtime/lib/pmt/CMakeFiles/gr_pmt_test.dir/build.make gnuradio-runtime/lib/pmt/CMakeFiles/gr_pmt_test.dir/test_pmt.cc.o.provides.build
.PHONY : gnuradio-runtime/lib/pmt/CMakeFiles/gr_pmt_test.dir/test_pmt.cc.o.provides

gnuradio-runtime/lib/pmt/CMakeFiles/gr_pmt_test.dir/test_pmt.cc.o.provides.build: gnuradio-runtime/lib/pmt/CMakeFiles/gr_pmt_test.dir/test_pmt.cc.o


# Object files for target gr_pmt_test
gr_pmt_test_OBJECTS = \
"CMakeFiles/gr_pmt_test.dir/test_pmt.cc.o"

# External object files for target gr_pmt_test
gr_pmt_test_EXTERNAL_OBJECTS =

gnuradio-runtime/lib/pmt/gr_pmt_test: gnuradio-runtime/lib/pmt/CMakeFiles/gr_pmt_test.dir/test_pmt.cc.o
gnuradio-runtime/lib/pmt/gr_pmt_test: gnuradio-runtime/lib/pmt/CMakeFiles/gr_pmt_test.dir/build.make
gnuradio-runtime/lib/pmt/gr_pmt_test: gnuradio-runtime/lib/pmt/libtest-gnuradio-pmt.so
gnuradio-runtime/lib/pmt/gr_pmt_test: gnuradio-runtime/lib/libgnuradio-runtime-3.7.12git.so.0.0.0
gnuradio-runtime/lib/pmt/gr_pmt_test: volk/lib/libvolk.so.1.3
gnuradio-runtime/lib/pmt/gr_pmt_test: /usr/lib/x86_64-linux-gnu/liborc-0.4.so
gnuradio-runtime/lib/pmt/gr_pmt_test: gnuradio-runtime/lib/pmt/libgnuradio-pmt-3.7.12git.so.0.0.0
gnuradio-runtime/lib/pmt/gr_pmt_test: /usr/lib/x86_64-linux-gnu/libcppunit.so
gnuradio-runtime/lib/pmt/gr_pmt_test: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
gnuradio-runtime/lib/pmt/gr_pmt_test: /usr/lib/x86_64-linux-gnu/libboost_program_options.so
gnuradio-runtime/lib/pmt/gr_pmt_test: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
gnuradio-runtime/lib/pmt/gr_pmt_test: /usr/lib/x86_64-linux-gnu/libboost_system.so
gnuradio-runtime/lib/pmt/gr_pmt_test: /usr/lib/x86_64-linux-gnu/libboost_regex.so
gnuradio-runtime/lib/pmt/gr_pmt_test: /usr/lib/x86_64-linux-gnu/libboost_thread.so
gnuradio-runtime/lib/pmt/gr_pmt_test: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
gnuradio-runtime/lib/pmt/gr_pmt_test: /usr/lib/x86_64-linux-gnu/libboost_atomic.so
gnuradio-runtime/lib/pmt/gr_pmt_test: /usr/lib/liblog4cpp.so
gnuradio-runtime/lib/pmt/gr_pmt_test: gnuradio-runtime/lib/pmt/CMakeFiles/gr_pmt_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zhiwei/WorkSpace/gnuradio/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable gr_pmt_test"
	cd /home/zhiwei/WorkSpace/gnuradio/cmake-build-debug/gnuradio-runtime/lib/pmt && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gr_pmt_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
gnuradio-runtime/lib/pmt/CMakeFiles/gr_pmt_test.dir/build: gnuradio-runtime/lib/pmt/gr_pmt_test

.PHONY : gnuradio-runtime/lib/pmt/CMakeFiles/gr_pmt_test.dir/build

gnuradio-runtime/lib/pmt/CMakeFiles/gr_pmt_test.dir/requires: gnuradio-runtime/lib/pmt/CMakeFiles/gr_pmt_test.dir/test_pmt.cc.o.requires

.PHONY : gnuradio-runtime/lib/pmt/CMakeFiles/gr_pmt_test.dir/requires

gnuradio-runtime/lib/pmt/CMakeFiles/gr_pmt_test.dir/clean:
	cd /home/zhiwei/WorkSpace/gnuradio/cmake-build-debug/gnuradio-runtime/lib/pmt && $(CMAKE_COMMAND) -P CMakeFiles/gr_pmt_test.dir/cmake_clean.cmake
.PHONY : gnuradio-runtime/lib/pmt/CMakeFiles/gr_pmt_test.dir/clean

gnuradio-runtime/lib/pmt/CMakeFiles/gr_pmt_test.dir/depend:
	cd /home/zhiwei/WorkSpace/gnuradio/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zhiwei/WorkSpace/gnuradio /home/zhiwei/WorkSpace/gnuradio/gnuradio-runtime/lib/pmt /home/zhiwei/WorkSpace/gnuradio/cmake-build-debug /home/zhiwei/WorkSpace/gnuradio/cmake-build-debug/gnuradio-runtime/lib/pmt /home/zhiwei/WorkSpace/gnuradio/cmake-build-debug/gnuradio-runtime/lib/pmt/CMakeFiles/gr_pmt_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : gnuradio-runtime/lib/pmt/CMakeFiles/gr_pmt_test.dir/depend

