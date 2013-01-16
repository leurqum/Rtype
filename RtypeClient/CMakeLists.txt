cmake_minimum_required (VERSION 2.8) 

project (RtypeClient)

include_directories ("include/")

set(EXECUTABLE_OUTPUT_PATH bin)



# Set default compile flags for GCC
if(CMAKE_COMPILER_IS_GNUCXX)
  message(STATUS "GCC detected, adding compile flags")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pedantic -Wall -Wextra")
endif(CMAKE_COMPILER_IS_GNUCXX)

file (
     GLOB_RECURSE
     src_files
     src/*.cpp
)

file (
     GLOB_RECURSE
     include_files
     include/*.h
	 ../server/Abs_Socket/ISocket.hpp
)


add_executable (
	       rtypeClient

	       ${src_files}
               ${include_files}
)



target_link_libraries (rtypeClient sfml-system sfml-window sfml-graphics sfml-network)

