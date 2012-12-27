cmake_minimum_required (VERSION 2.8) 

project (RtypeClient)

include_directories ("include/")

set(EXECUTABLE_OUTPUT_PATH bin)

add_definitions(-std=c++11) 
add_definitions(-Wall -Wextra) 

file (
     GLOB_RECURSE
     src_files
     src/*.cpp
)

file (
     GLOB_RECURSE
     include_files
     include/*.h
)

add_executable (
	       rtypeClient

	       ${src_files}
               ${include_files}
)

target_link_libraries (rtypeClient sfml-system sfml-window sfml-graphics)

