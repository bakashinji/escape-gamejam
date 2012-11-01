cmake_minimum_required(VERSION 2.6)

project(ProofOfConcept)

set(CMAKE_MODULE_PATH
	/usr/lib/OGRE/cmake
	${CMAKE_SOURCE_DIR}/cmake
)

set(Boost_USE_STATIC_LIBS       ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost 1.36.0 COMPONENTS system REQUIRED)
find_package(OpenGL REQUIRED)
find_package(SDL REQUIRED)
find_package(OGRE REQUIRED)
find_package(OpenAL REQUIRED)
find_package(SndFile REQUIRED)
find_package(Lua51 REQUIRED)

set(CMAKE_CXX_FLAGS "-std=c++0x")

include_directories(
	${OpenGL_INCLUDE_DIR}
	${OGRE_INCLUDE_DIRS}
	${SDL_INCLUDE_DIR}
	${OPENAL_INCLUDE_DIR}
	${SndFile_INCLUDE_DIRS}
	${Boost_INCLUDE_DIRS}
	${LUA_INCLUDE_DIR}
#	audaspace
)

link_directories(
	${OGRE_LIBRARY_DIRS}
)

set(EXE poc)
set(SRC
	src/main.cpp
	src/GameApplication.cpp
	src/WingsOfConcept.cpp
	src/GameState.cpp
	src/MainState.cpp
	src/GameSystem.cpp
	src/RenderSystem.cpp
	src/InputSystem.cpp
	src/MessageException.cpp
	src/LuaConfiguration.cpp
	src/InputDevice.cpp
	src/SDLKeyboard.cpp
	src/SDLMouse.cpp
	src/SDLJoystick.cpp
	src/QuitAction.cpp
	src/MoveActions.cpp
	src/CombatActions.cpp
	src/GameObject.cpp
	src/Fighter.cpp
)
set(HDR
	src/GameApplication.h
	src/WingsOfConcept.h
	src/GameState.h
	src/MainState.h
	src/GameSystem.h
	src/RenderSystem.h
	src/InputSystem.h
	src/MessageException.h
	src/IConfiguration.h
	src/LuaConfiguration.h
	src/IInputAction.h
	src/InputDevice.h
	src/SDLKeyboard.h
	src/SDLMouse.h
	src/SDLJoystick.h
	src/QuitAction.h
	src/MoveActions.h
	src/CombatActions.h
	src/GameObject.h
	src/Fighter.h
)

add_executable(${EXE} ${SRC} ${HDR})

target_link_libraries(${EXE}
	${OpenGL_gl_LIBRARY}
	${OGRE_LIBRARIES}
	${SDL_LIBRARY}
	${OPENAL_LIBRARY}
	${SndFile_LIBRARIES}
	${Boost_LIBRARIES}
	${LUA_LIBRARIES}
)

