# - Try to find libsndfile
# Once done, this will define
#
#  SndFile_FOUND - system has libsndfile
#  SndFile_INCLUDE_DIRS - the libsndfile include directories
#  SndFile_LIBRARIES - link these to use libsndfile

# Use pkg-config to get hints about paths
find_package(PkgConfig)
if(PKG_CONFIG_FOUND)
	pkg_check_modules(SndFile_PKGCONF sndfile)
endif(PKG_CONFIG_FOUND)

# Include dir
find_path(SndFile_INCLUDE_DIRS
	NAMES sndfile.h
	PATHS ${SndFile_PKGCONF_INCLUDE_DIRS}
)

# Library
find_library(SndFile_LIBRARIES
	NAMES sndfile
	PATHS ${SndFile_PKGCONF_LIBRARY_DIRS}
)

