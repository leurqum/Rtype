cmake_minimum_required (VERSION 2.8) 

project (RtypeClient)

include_directories (${RTYPECLIENT_SOURCE_DIR})

set(EXECUTABLE_OUTPUT_PATH bin)

file (
     GLOB_RECURSE
     src_files
     src/*.cpp
)

add_executable (
	       rtypeClient

	       ${src_files}
)

target_link_libraries (rtypeClient sfml-window sfml-graphics)
