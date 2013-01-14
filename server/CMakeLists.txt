cmake_minimum_required (VERSION 2.8) 

project (RtypeServer)

include_directories("./src/include/", "./Abs_Socket/", "./Abs_Thread_mutex/")

# Set default compile flags for GCC
if(UNIX)
  message(STATUS "GCC detected, adding compile flags")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")
  add_executable(
    RtypeServer
    ./src/source/IAUnit.cpp
    ./src/source/HumainUnit.cpp
    ./src/source/Bullet.cpp
    ./src/source/BasicWeapon.cpp
    ./src/source/LifePowerUp.cpp
    ./src/source/MovingObstacle.cpp
    ./src/source/Obstacle.cpp
    ./src/source/Player.cpp
    ./src/source/RectangleCollisionDefinition.cpp
    ./src/source/Unit.cpp
    ./src/source/Game.cpp
    ./src/source/Server.cpp
    ./src/source/InterpretPackage.cpp
    ./Abs_Socket/UServerSocket.cpp
    ./Abs_Socket/USocket.cpp
    ./Abs_Socket/main.cpp
    ./Abs_Thread_mutex/UMutex.cpp
    ./Abs_Thread_mutex/UThread.cpp
    )
  target_link_libraries (RtypeServer pthread)

endif(UNIX)

if(WIN32)
  add_executable(
    RtypeServer
    ./src/source/IAUnit.cpp
    ./src/source/HumainUnit.cpp
    ./src/source/Bullet.cpp
    ./src/source/BasicWeapon.cpp
    ./src/source/LifePowerUp.cpp
    ./src/source/MovingObstacle.cpp
    ./src/source/Obstacle.cpp
    ./src/source/Player.cpp
    ./src/source/RectangleCollisionDefinition.cpp
    ./src/source/Unit.cpp
    ./src/source/Game.cpp
    ./src/source/Server.cpp
    ./src/source/InterpretPackage.cpp
    ./Abs_Socket/WServerSocket.cpp
    ./Abs_Socket/WSocket.cpp
    ./Abs_Socket/main.cpp
    ./Abs_Thread_mutex/WMutex.cpp
    ./Abs_Thread_mutex/CWThread.cpp
    )
endif(WIN32)
