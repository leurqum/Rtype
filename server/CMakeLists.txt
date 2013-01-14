cmake_minimum_required (VERSION 2.8) 

project (RtypeServer)

include_directories("./src/include/", "./Abs_Socket/", "./Abs_Thread_mutex/")

file (
     GLOB_RECURSE
     src_files_unix
     ./Abs_Socket/USocket.hpp
     ./Abs_Socket/UServerSocket.hpp
     ./Abs_Socket/USocket.cpp
     ./Abs_Socket/UServerSocket.cpp

     ./Abs_Thread_mutex/UThread.cpp
     ./Abs_Thread_mutex/UMutex.cpp
     ./Abs_Thread_mutex/UMutex.hpp
     ./Abs_Thread_mutex/UThread.hpp

)

file (
     GLOB_RECURSE
     src_files_win
     ./Abs_Thread_mutex/WMutex.cpp
     ./Abs_Thread_mutex/CWThread.cpp
     ./Abs_Thread_mutex/WMutex.h
     ./Abs_Thread_mutex/CWThread.h

     ./Abs_Socket/WSocket.hpp
     ./Abs_Socket/WSocket.cpp
     ./Abs_Socket/WServerSocket.hpp
     ./Abs_Socket/WServerSocket.cpp
)

file (
     GLOB_RECURSE
     src_files_common
     ./src/include/Bullet.hpp
     ./src/include/ICollisionDefinition.hpp
     ./src/include/CommandManager.hpp
     ./src/include/IWeapon.hpp
     ./src/include/Player.hpp
     ./src/include/InterpretPackage.hpp
     ./src/include/IAUnit.hpp
     ./src/include/HumainUnit.hpp
     ./src/include/Server.hpp
     ./src/include/RectangleCollisionDefinition.hpp
     ./src/include/Obstacle.hpp
     ./src/include/Game.hpp
     ./src/include/Unit.hpp
     ./src/include/BasicWeapon.hpp
     ./src/include/MovingObstacle.hpp
     ./src/include/LifePowerUp.hpp
     ./src/source/MovingObstacle.cpp
     ./src/source/InterpretPackage.cpp
     ./src/source/LifePowerUp.cpp
     ./src/source/Player.cpp
     ./src/source/Unit.cpp
     ./src/source/BasicWeapon.cpp
     ./src/source/RectangleCollisionDefinition.cpp
     ./src/source/Server.cpp
     ./src/source/CommandManager.cpp
     ./src/source/IAUnit.cpp
     ./src/source/HumainUnit.cpp
     ./src/source/Game.cpp
     ./src/source/Bullet.cpp
     ./src/source/Obstacle.cpp
     ./Abs_Thread_mutex/IThread.h
     ./Abs_Thread_mutex/IMutex.h
     ./Abs_Socket/ISocket.hpp
     ./Abs_Socket/IServerSocket.hpp
     ./Abs_Socket/portaSocket.hpp
     ./Abs_Socket/main.cpp
)

file (
     GLOB_RECURSE
     src_files_client_test
	 ./clientTest.cpp
)

# Set default compile flags for GCC
if(UNIX)
  message(STATUS "GCC detected, adding compile flags")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -g")
  add_executable(
    RtypeServer
    ${src_files_unix}
    ${src_files_common}
  )
  target_link_libraries (RtypeServer pthread)

endif(UNIX)

if(WIN32)
  add_executable(
    RtypeServer
    ${src_files_win}
    ${src_files_common}
    )
endif(WIN32)
