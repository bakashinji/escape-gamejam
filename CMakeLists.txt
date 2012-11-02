cmake_minimum_required(VERSION 2.6)

project(Escape)

set(SRC_DIR src)

set(INC_DIRS
	${SRC_DIR}
	${SRC_DIR}/audaspace
	${SRC_DIR}/audaspace/FX
	${SRC_DIR}/audaspace/OpenAL
	${SRC_DIR}/audaspace/OpenAL
)

if(WIN32)
	set(CMAKE_MODULE_PATH "$ENV{OGRE_HOME}/CMake/;${CMAKE_MODULE_PATH}")
	set(OGRE_SAMPLES_INCLUDEPATH
		$ENV{OGRE_HOME}/Samples/include
	)
endif(WIN32)
 
if(UNIX)
	if(EXISTS "/usr/local/lib/OGRE/cmake")

	  set(CMAKE_MODULE_PATH "/usr/local/lib/OGRE/cmake/;${CMAKE_MODULE_PATH}")
	  set(OGRE_SAMPLES_INCLUDEPATH "/usr/local/share/OGRE/samples/Common/include/") # We could just *assume* that developers uses this basepath : /usr/local

	elseif(EXISTS "/usr/lib/OGRE/cmake")

	  set(CMAKE_MODULE_PATH "/usr/lib/OGRE/cmake/;${CMAKE_MODULE_PATH}")
	  set(OGRE_SAMPLES_INCLUDEPATH "/usr/share/OGRE/samples/Common/include/") # Otherwise, this one

	else ()
	  message(SEND_ERROR "Failed to find module path.")
	endif(EXISTS "/usr/local/lib/OGRE/cmake")
endif(UNIX)
 
if (CMAKE_BUILD_TYPE STREQUAL "")
  # CMake defaults to leaving CMAKE_BUILD_TYPE empty. This screws up
  # differentiation between debug and release builds.
  set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif ()
 
set(CMAKE_DEBUG_POSTFIX "_d")
 
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/dist")
 
find_package(OGRE REQUIRED)

#if(NOT "${OGRE_VERSION_NAME}" STREQUAL "Cthugha")
#  message(SEND_ERROR "You need Ogre 1.7 Cthugha to build this.")
#endif()
 
find_package(SDL REQUIRED)
 
#if(NOT SDL_FOUND)
#  message(SEND_ERROR "You need SDL to build this.")
#endif()

find_package(OIS REQUIRED)
 
if(NOT OIS_FOUND)
	message(SEND_ERROR "Failed to find OIS.")
endif()



# Find Boost
if (NOT OGRE_BUILD_PLATFORM_IPHONE)
	if (WIN32 OR APPLE)
		set(Boost_USE_STATIC_LIBS TRUE)
	else ()
		# Statically linking boost to a dynamic Ogre build doesn't work on Linux 64bit
		set(Boost_USE_STATIC_LIBS ${OGRE_STATIC})
	endif ()
	if (MINGW)
		# this is probably a bug in CMake: the boost find module tries to look for
		# boost libraries with name libboost_*, but CMake already prefixes library
		# search names with "lib". This is the workaround.
		set(CMAKE_FIND_LIBRARY_PREFIXES ${CMAKE_FIND_LIBRARY_PREFIXES} "")
	endif ()
	set(Boost_ADDITIONAL_VERSIONS "1.50" "1.44" "1.44.0" "1.42" "1.42.0" "1.41.0" "1.41" "1.40.0" "1.40" "1.39.0" "1.39" "1.38.0" "1.38" "1.37.0" "1.37" )
	# Components that need linking (NB does not include header-only components like bind)
	set(OGRE_BOOST_COMPONENTS thread date_time system)
	find_package(Boost COMPONENTS ${OGRE_BOOST_COMPONENTS} QUIET)
	if (NOT Boost_FOUND)
		# Try again with the other type of libs
		set(Boost_USE_STATIC_LIBS NOT ${Boost_USE_STATIC_LIBS})
		find_package(Boost COMPONENTS ${OGRE_BOOST_COMPONENTS} QUIET)
	endif()
	find_package(Boost QUIET)
 
	# Set up referencing of Boost
	list(APPEND INC_DIRS
		${Boost_INCLUDE_DIR}
	)
	add_definitions(-DBOOST_ALL_NO_LIB)
	set(OGRE_LIBRARIES ${OGRE_LIBRARIES} ${Boost_LIBRARIES})
endif()
  
set_target_properties(${EXE} PROPERTIES DEBUG_POSTFIX _d)
  
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/dist/bin)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/dist/media)
 
# post-build copy for win32
if(WIN32 AND NOT MINGW)
	add_custom_command( TARGET ${EXE} PRE_BUILD
		COMMAND if not exist .\\dist\\bin mkdir .\\dist\\bin )
	add_custom_command( TARGET ${EXE} POST_BUILD
		COMMAND copy \"$(TargetPath)\" .\\dist\\bin )
endif(WIN32 AND NOT MINGW)

if(MINGW OR UNIX)
	set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/dist/bin)
endif(MINGW OR UNIX)
 
if(WIN32)
 
	install(TARGETS ${EXE}
		RUNTIME DESTINATION bin
		CONFIGURATIONS All)
 
	install(DIRECTORY ${CMAKE_SOURCE_DIR}/dist/Media
		DESTINATION ./
		CONFIGURATIONS Release RelWithDebInfo Debug
	)
 
	install(FILES ${CMAKE_SOURCE_DIR}/dist/bin/plugins.cfg
		${CMAKE_SOURCE_DIR}/dist/bin/resources.cfg
		DESTINATION bin
		CONFIGURATIONS Release RelWithDebInfo
	)
 
	install(FILES ${CMAKE_SOURCE_DIR}/dist/bin/plugins_d.cfg
		${CMAKE_SOURCE_DIR}/dist/bin/resources_d.cfg
		DESTINATION bin
		CONFIGURATIONS Debug
	)
 
        # NOTE: for the 1.7.1 sdk the OIS dll is called OIS.dll instead of libOIS.dll
        # so you'll have to change that to make it work with 1.7.1
	install(FILES ${OGRE_PLUGIN_DIR_REL}/OgreMain.dll
		${OGRE_PLUGIN_DIR_REL}/RenderSystem_Direct3D9.dll
		${OGRE_PLUGIN_DIR_REL}/RenderSystem_GL.dll
		${OGRE_PLUGIN_DIR_REL}/libOIS.dll
		DESTINATION bin
		CONFIGURATIONS Release RelWithDebInfo
	)
 
	install(FILES ${OGRE_PLUGIN_DIR_DBG}/OgreMain_d.dll
		${OGRE_PLUGIN_DIR_DBG}/RenderSystem_Direct3D9_d.dll
		${OGRE_PLUGIN_DIR_DBG}/RenderSystem_GL_d.dll
		${OGRE_PLUGIN_DIR_DBG}/libOIS_d.dll
		DESTINATION bin
		CONFIGURATIONS Debug
	)
 
   # as of sdk 1.7.2 we need to copy the boost dll's as well
   # because they're not linked statically (it worked with 1.7.1 though)
   install(FILES ${Boost_DATE_TIME_LIBRARY_RELEASE}
      ${Boost_THREAD_LIBRARY_RELEASE}
      DESTINATION bin
      CONFIGURATIONS Release RelWithDebInfo
   )
 
   install(FILES ${Boost_DATE_TIME_LIBRARY_DEBUG}
      ${Boost_THREAD_LIBRARY_DEBUG}
      DESTINATION bin
      CONFIGURATIONS Debug
   )
endif(WIN32)

if(UNIX)
 
	install(TARGETS ${EXE}
		RUNTIME DESTINATION bin
		CONFIGURATIONS All)
 
	install(DIRECTORY ${CMAKE_SOURCE_DIR}/dist/media
		DESTINATION ./
		CONFIGURATIONS Release RelWithDebInfo Debug
	)
 
	install(FILES ${CMAKE_SOURCE_DIR}/dist/bin/plugins.cfg
		${CMAKE_SOURCE_DIR}/dist/bin/resources.cfg
		DESTINATION bin
		CONFIGURATIONS Release RelWithDebInfo Debug
	)
 
endif(UNIX)
set(CMAKE_MODULE_PATH
	/usr/lib/OGRE/cmake
	${CMAKE_SOURCE_DIR}/cmake
)

#find_package(OGREBULLET REQUIRED)
#if(NOT OGREBULLET_FOUND)
#	message(SEND_ERROR "Failed to find ogrebullet!")
#endif()

#set(Boost_USE_STATIC_LIBS       ON)
#set(Boost_USE_STATIC_RUNTIME    OFF)
#find_package(Boost 1.36.0 COMPONENTS system REQUIRED)
find_package(OpenGL REQUIRED)
find_package(OpenAL REQUIRED)
find_package(SndFile REQUIRED)
find_package(Lua51 REQUIRED)

# set(CMAKE_CXX_FLAGS "-std=c++0x")

list(APPEND INC_DIRS
	${OpenGL_INCLUDE_DIR}
	${OGRE_INCLUDE_DIRS}
	${SDL_INCLUDE_DIR}
	${OPENAL_INCLUDE_DIR}
	${SndFile_INCLUDE_DIRS}
	${LUA_INCLUDE_DIR}
)

include_directories(${INC_DIRS})

link_directories(
	${OGRE_LIBRARY_DIRS}
)

set(EXE escape)
set(SRC
	${SRC_DIR}/main.cpp
	${SRC_DIR}/GameApplication.cpp
	${SRC_DIR}/Escape.cpp
	${SRC_DIR}/GameState.cpp
	${SRC_DIR}/MainState.cpp
	${SRC_DIR}/GameSystem.cpp
	${SRC_DIR}/RenderSystem.cpp
	${SRC_DIR}/InputSystem.cpp
	${SRC_DIR}/MessageException.cpp
	${SRC_DIR}/LuaConfiguration.cpp
	${SRC_DIR}/InputDevice.cpp
	${SRC_DIR}/SDLKeyboard.cpp
	${SRC_DIR}/SDLMouse.cpp
	${SRC_DIR}/SDLJoystick.cpp
	${SRC_DIR}/QuitAction.cpp
	${SRC_DIR}/MoveActions.cpp
	${SRC_DIR}/GameObject.cpp
)
set(HDR
	${SRC_DIR}/unique_ptr.h
	${SRC_DIR}/GameApplication.h
	${SRC_DIR}/Escape.h
	${SRC_DIR}/GameState.h
	${SRC_DIR}/MainState.h
	${SRC_DIR}/GameSystem.h
	${SRC_DIR}/RenderSystem.h
	${SRC_DIR}/InputSystem.h
	${SRC_DIR}/MessageException.h
	${SRC_DIR}/IConfiguration.h
	${SRC_DIR}/LuaConfiguration.h
	${SRC_DIR}/IInputAction.h
	${SRC_DIR}/InputDevice.h
	${SRC_DIR}/SDLKeyboard.h
	${SRC_DIR}/SDLMouse.h
	${SRC_DIR}/SDLJoystick.h
	${SRC_DIR}/QuitAction.h
	${SRC_DIR}/MoveActions.h
	${SRC_DIR}/GameObject.h
)

# audaspace source
list(APPEND SRC
	${SRC_DIR}/audaspace/AUD_AnimateableProperty.cpp
	${SRC_DIR}/audaspace/AUD_Buffer.cpp
	${SRC_DIR}/audaspace/AUD_BufferReader.cpp
	${SRC_DIR}/audaspace/AUD_C-API.cpp
	${SRC_DIR}/audaspace/AUD_ChannelMapperFactory.cpp
	${SRC_DIR}/audaspace/AUD_ChannelMapperReader.cpp
	${SRC_DIR}/audaspace/AUD_ConverterFactory.cpp
	${SRC_DIR}/audaspace/AUD_ConverterFunctions.cpp
	${SRC_DIR}/audaspace/AUD_ConverterReader.cpp
	${SRC_DIR}/audaspace/AUD_FileFactory.cpp
	${SRC_DIR}/audaspace/AUD_FileWriter.cpp
	${SRC_DIR}/audaspace/AUD_JOSResampleFactory.cpp
	${SRC_DIR}/audaspace/AUD_JOSResampleReader.cpp
	${SRC_DIR}/audaspace/AUD_LinearResampleFactory.cpp
	${SRC_DIR}/audaspace/AUD_LinearResampleReader.cpp
	${SRC_DIR}/audaspace/AUD_Mixer.cpp
	${SRC_DIR}/audaspace/AUD_MixerFactory.cpp
	${SRC_DIR}/audaspace/AUD_NULLDevice.cpp
	${SRC_DIR}/audaspace/AUD_ReadDevice.cpp
	${SRC_DIR}/audaspace/AUD_ReferenceHandler.cpp
	${SRC_DIR}/audaspace/AUD_ResampleReader.cpp
	${SRC_DIR}/audaspace/AUD_SequencerEntry.cpp
	${SRC_DIR}/audaspace/AUD_SequencerFactory.cpp
	${SRC_DIR}/audaspace/AUD_SequencerHandle.cpp
	${SRC_DIR}/audaspace/AUD_SequencerReader.cpp
	${SRC_DIR}/audaspace/AUD_SilenceFactory.cpp
	${SRC_DIR}/audaspace/AUD_SilenceReader.cpp
	${SRC_DIR}/audaspace/AUD_SinusFactory.cpp
	${SRC_DIR}/audaspace/AUD_SinusReader.cpp
	${SRC_DIR}/audaspace/AUD_SoftwareDevice.cpp
	${SRC_DIR}/audaspace/AUD_StreamBufferFactory.cpp
	${SRC_DIR}/audaspace/FX/AUD_AccumulatorFactory.cpp
	${SRC_DIR}/audaspace/FX/AUD_BaseIIRFilterReader.cpp
	${SRC_DIR}/audaspace/FX/AUD_ButterworthFactory.cpp
	${SRC_DIR}/audaspace/FX/AUD_CallbackIIRFilterReader.cpp
	${SRC_DIR}/audaspace/FX/AUD_DelayFactory.cpp
	${SRC_DIR}/audaspace/FX/AUD_DelayReader.cpp
	${SRC_DIR}/audaspace/FX/AUD_DoubleFactory.cpp
	${SRC_DIR}/audaspace/FX/AUD_DoubleReader.cpp
	${SRC_DIR}/audaspace/FX/AUD_DynamicIIRFilterFactory.cpp
	${SRC_DIR}/audaspace/FX/AUD_DynamicIIRFilterReader.cpp
	${SRC_DIR}/audaspace/FX/AUD_EffectFactory.cpp
	${SRC_DIR}/audaspace/FX/AUD_EffectReader.cpp
	${SRC_DIR}/audaspace/FX/AUD_EnvelopeFactory.cpp
	${SRC_DIR}/audaspace/FX/AUD_FaderFactory.cpp
	${SRC_DIR}/audaspace/FX/AUD_FaderReader.cpp
	${SRC_DIR}/audaspace/FX/AUD_HighpassFactory.cpp
	${SRC_DIR}/audaspace/FX/AUD_IIRFilterFactory.cpp
	${SRC_DIR}/audaspace/FX/AUD_IIRFilterReader.cpp
	${SRC_DIR}/audaspace/FX/AUD_LimiterFactory.cpp
	${SRC_DIR}/audaspace/FX/AUD_LimiterReader.cpp
	${SRC_DIR}/audaspace/FX/AUD_LoopFactory.cpp
	${SRC_DIR}/audaspace/FX/AUD_LoopReader.cpp
	${SRC_DIR}/audaspace/FX/AUD_LowpassFactory.cpp
	${SRC_DIR}/audaspace/FX/AUD_PingPongFactory.cpp
	${SRC_DIR}/audaspace/FX/AUD_PitchFactory.cpp
	${SRC_DIR}/audaspace/FX/AUD_PitchReader.cpp
	${SRC_DIR}/audaspace/FX/AUD_RectifyFactory.cpp
	${SRC_DIR}/audaspace/FX/AUD_ReverseFactory.cpp
	${SRC_DIR}/audaspace/FX/AUD_ReverseReader.cpp
	${SRC_DIR}/audaspace/FX/AUD_SquareFactory.cpp
	${SRC_DIR}/audaspace/FX/AUD_SumFactory.cpp
	${SRC_DIR}/audaspace/FX/AUD_SuperposeFactory.cpp
	${SRC_DIR}/audaspace/FX/AUD_SuperposeReader.cpp
	${SRC_DIR}/audaspace/FX/AUD_VolumeFactory.cpp
	${SRC_DIR}/audaspace/OpenAL/AUD_OpenALDevice.cpp
	${SRC_DIR}/audaspace/sndfile/AUD_SndFileFactory.cpp
	${SRC_DIR}/audaspace/sndfile/AUD_SndFileReader.cpp
	${SRC_DIR}/audaspace/sndfile/AUD_SndFileWriter.cpp
)

# audaspace header
list(APPEND HDR
	${SRC_DIR}/audaspace/AUD_3DMath.h
	${SRC_DIR}/audaspace/AUD_AnimateableProperty.h
	${SRC_DIR}/audaspace/AUD_Buffer.h
	${SRC_DIR}/audaspace/AUD_BufferReader.h
	${SRC_DIR}/audaspace/AUD_C-API.h
	${SRC_DIR}/audaspace/AUD_ChannelMapperFactory.h
	${SRC_DIR}/audaspace/AUD_ChannelMapperReader.h
	${SRC_DIR}/audaspace/AUD_ConverterFactory.h
	${SRC_DIR}/audaspace/AUD_ConverterFunctions.h
	${SRC_DIR}/audaspace/AUD_ConverterReader.h
	${SRC_DIR}/audaspace/AUD_FileFactory.h
	${SRC_DIR}/audaspace/AUD_FileWriter.h
	${SRC_DIR}/audaspace/AUD_I3DDevice.h
	${SRC_DIR}/audaspace/AUD_I3DHandle.h
	${SRC_DIR}/audaspace/AUD_IDevice.h
	${SRC_DIR}/audaspace/AUD_IFactory.h
	${SRC_DIR}/audaspace/AUD_IHandle.h
	${SRC_DIR}/audaspace/AUD_ILockable.h
	${SRC_DIR}/audaspace/AUD_IReader.h
	${SRC_DIR}/audaspace/AUD_IWriter.h
	${SRC_DIR}/audaspace/AUD_JOSResampleFactory.h
	${SRC_DIR}/audaspace/AUD_JOSResampleReader.h
	${SRC_DIR}/audaspace/AUD_LinearResampleFactory.h
	${SRC_DIR}/audaspace/AUD_LinearResampleReader.h
	${SRC_DIR}/audaspace/AUD_MixerFactory.h
	${SRC_DIR}/audaspace/AUD_Mixer.h
	${SRC_DIR}/audaspace/AUD_MutexLock.h
	${SRC_DIR}/audaspace/AUD_NULLDevice.h
	${SRC_DIR}/audaspace/AUD_PyInit.h
	${SRC_DIR}/audaspace/AUD_ReadDevice.h
	${SRC_DIR}/audaspace/AUD_Reference.h
	${SRC_DIR}/audaspace/AUD_ResampleFactory.h
	${SRC_DIR}/audaspace/AUD_ResampleReader.h
	${SRC_DIR}/audaspace/AUD_SequencerEntry.h
	${SRC_DIR}/audaspace/AUD_SequencerFactory.h
	${SRC_DIR}/audaspace/AUD_SequencerHandle.h
	${SRC_DIR}/audaspace/AUD_SequencerReader.h
	${SRC_DIR}/audaspace/AUD_SilenceFactory.h
	${SRC_DIR}/audaspace/AUD_SilenceReader.h
	${SRC_DIR}/audaspace/AUD_SinusFactory.h
	${SRC_DIR}/audaspace/AUD_SinusReader.h
	${SRC_DIR}/audaspace/AUD_SoftwareDevice.h
	${SRC_DIR}/audaspace/AUD_Space.h
	${SRC_DIR}/audaspace/AUD_StreamBufferFactory.h
	${SRC_DIR}/audaspace/FX/AUD_AccumulatorFactory.h
	${SRC_DIR}/audaspace/FX/AUD_BaseIIRFilterReader.h
	${SRC_DIR}/audaspace/FX/AUD_ButterworthFactory.h
	${SRC_DIR}/audaspace/FX/AUD_CallbackIIRFilterReader.h
	${SRC_DIR}/audaspace/FX/AUD_DelayFactory.h
	${SRC_DIR}/audaspace/FX/AUD_DelayReader.h
	${SRC_DIR}/audaspace/FX/AUD_DoubleFactory.h
	${SRC_DIR}/audaspace/FX/AUD_DoubleReader.h
	${SRC_DIR}/audaspace/FX/AUD_DynamicIIRFilterFactory.h
	${SRC_DIR}/audaspace/FX/AUD_DynamicIIRFilterReader.h
	${SRC_DIR}/audaspace/FX/AUD_EffectFactory.h
	${SRC_DIR}/audaspace/FX/AUD_EffectReader.h
	${SRC_DIR}/audaspace/FX/AUD_EnvelopeFactory.h
	${SRC_DIR}/audaspace/FX/AUD_FaderFactory.h
	${SRC_DIR}/audaspace/FX/AUD_FaderReader.h
	${SRC_DIR}/audaspace/FX/AUD_HighpassFactory.h
	${SRC_DIR}/audaspace/FX/AUD_IIRFilterFactory.h
	${SRC_DIR}/audaspace/FX/AUD_IIRFilterReader.h
	${SRC_DIR}/audaspace/FX/AUD_LimiterFactory.h
	${SRC_DIR}/audaspace/FX/AUD_LimiterReader.h
	${SRC_DIR}/audaspace/FX/AUD_LoopFactory.h
	${SRC_DIR}/audaspace/FX/AUD_LoopReader.h
	${SRC_DIR}/audaspace/FX/AUD_LowpassFactory.h
	${SRC_DIR}/audaspace/FX/AUD_PingPongFactory.h
	${SRC_DIR}/audaspace/FX/AUD_PitchFactory.h
	${SRC_DIR}/audaspace/FX/AUD_PitchReader.h
	${SRC_DIR}/audaspace/FX/AUD_RectifyFactory.h
	${SRC_DIR}/audaspace/FX/AUD_ReverseFactory.h
	${SRC_DIR}/audaspace/FX/AUD_ReverseReader.h
	${SRC_DIR}/audaspace/FX/AUD_SquareFactory.h
	${SRC_DIR}/audaspace/FX/AUD_SumFactory.h
	${SRC_DIR}/audaspace/FX/AUD_SuperposeFactory.h
	${SRC_DIR}/audaspace/FX/AUD_SuperposeReader.h
	${SRC_DIR}/audaspace/FX/AUD_VolumeFactory.h
	${SRC_DIR}/audaspace/OpenAL/AUD_OpenALDevice.h
	${SRC_DIR}/audaspace/sndfile/AUD_SndFileFactory.h
	${SRC_DIR}/audaspace/sndfile/AUD_SndFileReader.h
	${SRC_DIR}/audaspace/sndfile/AUD_SndFileWriter.h
)

add_executable(${EXE} WIN32 ${SRC} ${HDR})

target_link_libraries(${EXE}
	${OpenGL_gl_LIBRARY}
	${OGRE_LIBRARIES}
	${SDL_LIBRARY}
	${OPENAL_LIBRARY}
	${SndFile_LIBRARIES}
	${Boost_LIBRARIES}
	${LUA_LIBRARIES}
)

