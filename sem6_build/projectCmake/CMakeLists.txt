# Specifies the minimum required cmake version
# Usually it doesn't matter which version you use,
# so write whatever works
cmake_minimum_required(VERSION 3.31)

# Sets the project name as well as some builtin cmake variables
# The purpose of this command is to let cmake know that this
# specific cmake file is the main one in your project

# This command can also be used to specify some meta information
# about the project like the version number or the languages used
project(Fibonacci)

# project(<PROJECT-NAME>
# [VERSION <major>[.<minor>[.<patch>[.<tweak>]]]]
# [LANGUAGES <language-name>...])
# project(
# Fibonacci
# VERSION 1.1.1
# LANGUAGES CXX
# )

# ## The project() command stores the version number and its components in variables
# PROJECT_VERSION, <PROJECT-NAME>_VERSION
# PROJECT_VERSION_MAJOR, <PROJECT-NAME>_VERSION_MAJOR
# PROJECT_VERSION_MINOR, <PROJECT-NAME>_VERSION_MINOR
# PROJECT_VERSION_PATCH, <PROJECT-NAME>_VERSION_PATCH
# PROJECT_VERSION_TWEAK, <PROJECT-NAME>_VERSION_TWEAK

# ######################################################################
# The next few lines will define some basic cmake targets as well
# as their properties.
# ######################################################################

# A cmake target is some step in your program's compilation
# The target ultimately consists of:

# 1 - Instructions on how to build it. These are just some
# bash/sh commands that are executed every time the
# target is built. For library or executable targets these instructions
# are generated automatically, for custom targets they are written by
# the user

# 2 - Dependencies. These are other targets which need to be
# built before this one, or files which it depends on. Most
# dependencies are automatically generated (such as an executable
# depending on its linked libraries or source files), but you can
# specify dependencies manually using add_dependencies() command

# 3 - Properties. These are all the target-specific variables that
# cmake decides to keep track of. Examples may include compilation
# flags, include directories and so on.

# Creates a new target that compiles a library with the given sources
# A library is some precompiled piece of code that may be used in
# creating other programs.
# Libraries are categorized by how they're linked to the consuming
# program The most common types of libraries are dynamic (aka shared)
# and static libraries.

# Dynamic libraries are linked to the program dynamically. What that
# means is that when you start executing a program that uses dynamic
# libraries the OS load the library file into RAM along with your
# program's file and patches the program with addresses of functions
# from that library. The process by which this is done is
# architecture-specific, but if you'd like to know more, google
# program linkage tables

# Static libraries are linked to the program statically. What that
# means is that during compilation time your library's code is copied
# into your program's code rather than loaded at runtime

# Static and dynamic libraries have their own pros and cons about
# which you can learn on your own.

# Additionally, add_library supports other types of library, about
# which you also can learn on your own
add_library(fibo SHARED src/fibo.cpp)

# By default, when using an #include "" preprocessor directive, the
# compiler is looking for the specified file:
# 1) locally (relative path to current source)
# 2) at the system header location

# Using #include <> change order of lookup:
# 1) at the system header location
# 2) locally (relative path to current source)

# For example, if main.cpp is located at ~/projects/MyProject/main.cpp
# and contains the line #include "someHeader", then the compiler will
# first look for the file ~/projects/MyProject/someHeader. If it
# doesn't find it there, it will start checking the system header
# locations such as /usr/local/include/someHeader

# List of system header locations can be expanded with the -I compiler flag or # with the target_include_directories() command.

# Include directories is an inheritable property (which is why you
# have to specify the PUBLIC, PRIVATE or INTERFACE flags), more on
# these later
target_include_directories(fibo PUBLIC include)

# Creates a new target that compiles an executable file with the given
# sources
add_executable(main main.cpp)

# Links the given library to target. The library can be a cmake
# target, a full path to a library file or just the library name (if
# the linker can locate your library automatically)
target_link_libraries(main PRIVATE fibo)

# ######################################################################
# The segment below fetches the googletest framework and then uses it
# to make tests for our fibo library
# ######################################################################

# This command functions similarly to C++'s #include directive. Given
# a module name it searches for a file named module_name.cmake in
# various locations, reads it and runs the CMake code inside.

# This way cmake code may be reused between projects or be packaged in
# a more convenient way

# Firstly it checks in the CMake builtin module directory (something
# like /usr/share/cmake-<version_num>/Modules), then the directories
# specified in the CMAKE_MODULE_PATH variable and then the cmake
# module directory (which is just a local subdirectory named cmake)

# This specific include command includes the FetchContent module,
# which contains functions for loading various dependencies from the
# internet
include(FetchContent)

# Declares a dependency named googletest, which is to be loaded from
# github using the given address. The specific version of the git
# repository is given by the GIT_TAG command, which accepts a git tag,
# git branch name or git hash
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.16.0 # master
)

# Actually loads all the previously declared dependencies.
FetchContent_MakeAvailable(googletest)

# Now that we've installed googletest we can actually use it. To do
# that we just write several tests and compile them into an executable
add_executable(
  fibo_test
  test/fibo_test.cpp
)

# Our test doesn't contain a 'main' function, so we link the library
# GTest::gtest_main, which does
target_link_libraries(
  fibo_test
  GTest::gtest_main
  fibo
)

# We include another module. This one contains functions related to
# google test
include(GoogleTest)

# Magic function defined in the GoogleTest module that does something
# if you'd like to learn more you can try and lookup the module
# yourself
gtest_discover_tests(fibo_test)

# ######################################################################
# The segment below deals with making cmake execute arbitrary commands
# to do whatever
# ######################################################################

# This command adds a custom build step that runs some code. In this
# instance we run the test we've just compiled and output its results
# into a file
add_custom_target(

  # target name [ALL] command1
  run_tests ALL fibo_test >> test_results.txt

  # Dependency list. Lists execution steps that need to be ran before
  # this one
  DEPENDS fibo_test

  # Comment. Some piece of text that is outputted whenever this target
  # is built
  COMMENT "RUNNING TESTS"

  # Byproducts. A list of files that may or may not get produced during
  # this target's build. CMake mainly uses this to know which files to
  # delete when running cmake --target clean
  BYPRODUCTS test_results.txt

  # Working directory. The directory in which the command is run.
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

# Another command to execute arbitrary code. This one is specifically
# intended for commands that generate source files
add_custom_command(

  # Output. A list of files this command is intended to produce
  OUTPUT ${CMAKE_SOURCE_DIR}/other.cpp

  # Command. A sh command that is run whenever the OUTPUT files need to
  # be generated, or when the dependencies change
  COMMAND ./generate.sh 2> error.log

  # Depends. A list of dependencies, like targets or files. Whenever the
  # dependencies change, COMMAND is rerun
  DEPENDS generate.sh

  # Byproducts. Same as custom target. The difference from OUTPUT is
  # that the command's main goal is to generate the OUTPUT, while
  # BYPRODUCTS are just artifacts that occur during execution, such as
  # error logs
  BYPRODUCTS error.log

  # Comment. Same as custom_target
  COMMENT "CREATING other.cpp"

  # Working_directory. Same as custom target
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

# Another option you could specify for add_custom_command is the
# DEPFILE option. This is a file that lists the dependencies of your
# custom command. Usually you don't generate this manually but rather
# get it as a byproduct of running whichever program you're using to
# generate your source files

# Let's use our dummy generated source for something
add_executable(other other.cpp)
