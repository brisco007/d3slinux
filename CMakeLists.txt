#cmake minimum version
cmake_minimum_required( VERSION 3.0 )

# project name
project( d3slinux )

#flags

#files

#include
# must include the include directories of each third party library i use
include_directories( ./include ./src )

#target
#add all the cpp files i create here 	
add_executable( library_generator ./src/main.cpp )

#external libs look at the screenshot

