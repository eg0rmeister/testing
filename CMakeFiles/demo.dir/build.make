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
CMAKE_SOURCE_DIR = /home/dmitry/Source/lang-23/cpp/srcfolder

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dmitry/Source/lang-23/cpp/srcfolder

# Include any dependencies generated for this target.
include CMakeFiles/demo.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/demo.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/demo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/demo.dir/flags.make

antlr4cpp_generated_src/TLexer/TLexer.interp: TLexer.g4
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/dmitry/Source/lang-23/cpp/srcfolder/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building SampleGrammarLexer with ANTLR 4.1"
	/usr/bin/java -jar /home/dmitry/Source/lang-23/cpp/antlr-4.13.1-complete.jar TLexer.g4 -o /home/dmitry/Source/lang-23/cpp/srcfolder/antlr4cpp_generated_src/TLexer -no-listener -Dlanguage=Cpp -package antlrcpptest

antlr4cpp_generated_src/TLexer/TLexer.tokens: antlr4cpp_generated_src/TLexer/TLexer.interp
	@$(CMAKE_COMMAND) -E touch_nocreate antlr4cpp_generated_src/TLexer/TLexer.tokens

antlr4cpp_generated_src/TLexer/TLexer.h: antlr4cpp_generated_src/TLexer/TLexer.interp
	@$(CMAKE_COMMAND) -E touch_nocreate antlr4cpp_generated_src/TLexer/TLexer.h

antlr4cpp_generated_src/TLexer/TLexer.cpp: antlr4cpp_generated_src/TLexer/TLexer.interp
	@$(CMAKE_COMMAND) -E touch_nocreate antlr4cpp_generated_src/TLexer/TLexer.cpp

antlr4cpp_generated_src/TParser/TParser.interp: TParser.g4
antlr4cpp_generated_src/TParser/TParser.interp: TLexer.g4
antlr4cpp_generated_src/TParser/TParser.interp: antlr4cpp_generated_src/TLexer/TLexer.interp
antlr4cpp_generated_src/TParser/TParser.interp: antlr4cpp_generated_src/TLexer/TLexer.tokens
antlr4cpp_generated_src/TParser/TParser.interp: antlr4cpp_generated_src/TLexer/TLexer.h
antlr4cpp_generated_src/TParser/TParser.interp: antlr4cpp_generated_src/TLexer/TLexer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/dmitry/Source/lang-23/cpp/srcfolder/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building SampleGrammarParser with ANTLR 4.1"
	/usr/bin/java -jar /home/dmitry/Source/lang-23/cpp/antlr-4.13.1-complete.jar TParser.g4 -o /home/dmitry/Source/lang-23/cpp/srcfolder/antlr4cpp_generated_src/TParser -no-listener -Dlanguage=Cpp -lib /home/dmitry/Source/lang-23/cpp/srcfolder/antlr4cpp_generated_src/TLexer -package antlrcpptest

antlr4cpp_generated_src/TParser/TParser.tokens: antlr4cpp_generated_src/TParser/TParser.interp
	@$(CMAKE_COMMAND) -E touch_nocreate antlr4cpp_generated_src/TParser/TParser.tokens

antlr4cpp_generated_src/TParser/TParser.h: antlr4cpp_generated_src/TParser/TParser.interp
	@$(CMAKE_COMMAND) -E touch_nocreate antlr4cpp_generated_src/TParser/TParser.h

antlr4cpp_generated_src/TParser/TParser.cpp: antlr4cpp_generated_src/TParser/TParser.interp
	@$(CMAKE_COMMAND) -E touch_nocreate antlr4cpp_generated_src/TParser/TParser.cpp

CMakeFiles/demo.dir/main.cpp.o: CMakeFiles/demo.dir/flags.make
CMakeFiles/demo.dir/main.cpp.o: main.cpp
CMakeFiles/demo.dir/main.cpp.o: CMakeFiles/demo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dmitry/Source/lang-23/cpp/srcfolder/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/demo.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/demo.dir/main.cpp.o -MF CMakeFiles/demo.dir/main.cpp.o.d -o CMakeFiles/demo.dir/main.cpp.o -c /home/dmitry/Source/lang-23/cpp/srcfolder/main.cpp

CMakeFiles/demo.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/demo.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dmitry/Source/lang-23/cpp/srcfolder/main.cpp > CMakeFiles/demo.dir/main.cpp.i

CMakeFiles/demo.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/demo.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dmitry/Source/lang-23/cpp/srcfolder/main.cpp -o CMakeFiles/demo.dir/main.cpp.s

CMakeFiles/demo.dir/antlr4cpp_generated_src/TLexer/TLexer.cpp.o: CMakeFiles/demo.dir/flags.make
CMakeFiles/demo.dir/antlr4cpp_generated_src/TLexer/TLexer.cpp.o: antlr4cpp_generated_src/TLexer/TLexer.cpp
CMakeFiles/demo.dir/antlr4cpp_generated_src/TLexer/TLexer.cpp.o: CMakeFiles/demo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dmitry/Source/lang-23/cpp/srcfolder/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/demo.dir/antlr4cpp_generated_src/TLexer/TLexer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/demo.dir/antlr4cpp_generated_src/TLexer/TLexer.cpp.o -MF CMakeFiles/demo.dir/antlr4cpp_generated_src/TLexer/TLexer.cpp.o.d -o CMakeFiles/demo.dir/antlr4cpp_generated_src/TLexer/TLexer.cpp.o -c /home/dmitry/Source/lang-23/cpp/srcfolder/antlr4cpp_generated_src/TLexer/TLexer.cpp

CMakeFiles/demo.dir/antlr4cpp_generated_src/TLexer/TLexer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/demo.dir/antlr4cpp_generated_src/TLexer/TLexer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dmitry/Source/lang-23/cpp/srcfolder/antlr4cpp_generated_src/TLexer/TLexer.cpp > CMakeFiles/demo.dir/antlr4cpp_generated_src/TLexer/TLexer.cpp.i

CMakeFiles/demo.dir/antlr4cpp_generated_src/TLexer/TLexer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/demo.dir/antlr4cpp_generated_src/TLexer/TLexer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dmitry/Source/lang-23/cpp/srcfolder/antlr4cpp_generated_src/TLexer/TLexer.cpp -o CMakeFiles/demo.dir/antlr4cpp_generated_src/TLexer/TLexer.cpp.s

CMakeFiles/demo.dir/antlr4cpp_generated_src/TParser/TParser.cpp.o: CMakeFiles/demo.dir/flags.make
CMakeFiles/demo.dir/antlr4cpp_generated_src/TParser/TParser.cpp.o: antlr4cpp_generated_src/TParser/TParser.cpp
CMakeFiles/demo.dir/antlr4cpp_generated_src/TParser/TParser.cpp.o: CMakeFiles/demo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dmitry/Source/lang-23/cpp/srcfolder/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/demo.dir/antlr4cpp_generated_src/TParser/TParser.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/demo.dir/antlr4cpp_generated_src/TParser/TParser.cpp.o -MF CMakeFiles/demo.dir/antlr4cpp_generated_src/TParser/TParser.cpp.o.d -o CMakeFiles/demo.dir/antlr4cpp_generated_src/TParser/TParser.cpp.o -c /home/dmitry/Source/lang-23/cpp/srcfolder/antlr4cpp_generated_src/TParser/TParser.cpp

CMakeFiles/demo.dir/antlr4cpp_generated_src/TParser/TParser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/demo.dir/antlr4cpp_generated_src/TParser/TParser.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dmitry/Source/lang-23/cpp/srcfolder/antlr4cpp_generated_src/TParser/TParser.cpp > CMakeFiles/demo.dir/antlr4cpp_generated_src/TParser/TParser.cpp.i

CMakeFiles/demo.dir/antlr4cpp_generated_src/TParser/TParser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/demo.dir/antlr4cpp_generated_src/TParser/TParser.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dmitry/Source/lang-23/cpp/srcfolder/antlr4cpp_generated_src/TParser/TParser.cpp -o CMakeFiles/demo.dir/antlr4cpp_generated_src/TParser/TParser.cpp.s

# Object files for target demo
demo_OBJECTS = \
"CMakeFiles/demo.dir/main.cpp.o" \
"CMakeFiles/demo.dir/antlr4cpp_generated_src/TLexer/TLexer.cpp.o" \
"CMakeFiles/demo.dir/antlr4cpp_generated_src/TParser/TParser.cpp.o"

# External object files for target demo
demo_EXTERNAL_OBJECTS =

demo: CMakeFiles/demo.dir/main.cpp.o
demo: CMakeFiles/demo.dir/antlr4cpp_generated_src/TLexer/TLexer.cpp.o
demo: CMakeFiles/demo.dir/antlr4cpp_generated_src/TParser/TParser.cpp.o
demo: CMakeFiles/demo.dir/build.make
demo: antlr4_runtime/src/antlr4_runtime/runtime/Cpp/dist/libantlr4-runtime.a
demo: CMakeFiles/demo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dmitry/Source/lang-23/cpp/srcfolder/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable demo"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/demo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/demo.dir/build: demo
.PHONY : CMakeFiles/demo.dir/build

CMakeFiles/demo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/demo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/demo.dir/clean

CMakeFiles/demo.dir/depend: antlr4cpp_generated_src/TLexer/TLexer.cpp
CMakeFiles/demo.dir/depend: antlr4cpp_generated_src/TLexer/TLexer.h
CMakeFiles/demo.dir/depend: antlr4cpp_generated_src/TLexer/TLexer.interp
CMakeFiles/demo.dir/depend: antlr4cpp_generated_src/TLexer/TLexer.tokens
CMakeFiles/demo.dir/depend: antlr4cpp_generated_src/TParser/TParser.cpp
CMakeFiles/demo.dir/depend: antlr4cpp_generated_src/TParser/TParser.h
CMakeFiles/demo.dir/depend: antlr4cpp_generated_src/TParser/TParser.interp
CMakeFiles/demo.dir/depend: antlr4cpp_generated_src/TParser/TParser.tokens
	cd /home/dmitry/Source/lang-23/cpp/srcfolder && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dmitry/Source/lang-23/cpp/srcfolder /home/dmitry/Source/lang-23/cpp/srcfolder /home/dmitry/Source/lang-23/cpp/srcfolder /home/dmitry/Source/lang-23/cpp/srcfolder /home/dmitry/Source/lang-23/cpp/srcfolder/CMakeFiles/demo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/demo.dir/depend

