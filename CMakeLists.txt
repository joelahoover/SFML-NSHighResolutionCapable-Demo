cmake_minimum_required(VERSION 3.0)
project(Skeleton)

# Allow our project modules
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules" ${CMAKE_MODULE_PATH})

# Enable debug symbols by default
if(CMAKE_BUILD_TYPE STREQUAL "")
	set(CMAKE_BUILD_TYPE Debug)
endif()

# Set version information in config.h
set(VERSION_MAJOR 0)
set(VERSION_MINOR 0)

# -----------------------------------------
#  Setup the main code
# -----------------------------------------

set(SOURCE_LIBRARY Skeleton_lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")

add_subdirectory(source)
add_subdirectory(include)
if(APPLE)
	add_subdirectory(osx)
endif()


include_directories(
	${PROJECT_SOURCE_DIR}/source	# Regular includes
	${PROJECT_SOURCE_DIR}/include	# Global includes
	${PROJECT_SOURCE_DIR}/extlibs	# External libraries includes
	${PROJECT_BINARY_DIR}/include	# CMake generated includes
)

set(PROJECT_LIBRARIES "")

# -----------------------------------------
#  Find external libraries
# -----------------------------------------

# Find SFML
find_package(SFML 2 REQUIRED system window graphics audio)
if(SFML_FOUND)
	include_directories(${SFML_INCLUDE_DIR})
	list(APPEND PROJECT_LIBRARIES ${SFML_LIBRARIES})
else()
	message(FATAL_ERROR "Unable to find SFML")
endif()

# Find OS X libraries
if(APPLE)
	# Add Foundation
	find_library(FOUNDATION_LIBRARY Foundation)
	list(APPEND PROJECT_LIBRARIES ${FOUNDATION_LIBRARY})
endif()

# -----------------------------------------
#  Setup the source library
# -----------------------------------------

add_library(${SOURCE_LIBRARY} ${PROJECT_SOURCES})

# -----------------------------------------
#  Setup the True bundle
# -----------------------------------------

add_executable(True MACOSX_BUNDLE ${PROJECT_MAIN})
target_link_libraries(True ${PROJECT_LIBRARIES} ${SOURCE_LIBRARY})

if(APPLE)
	set(MAKE_INSTALL_NAME_DIR @rpath)
	set_target_properties(True PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/osx/Info_True.plist.in)

	# Copy the assets and levels into the bundle
	set(BUNDLE_PATH ${CMAKE_CURRENT_BINARY_DIR}/True.app)
	install(DIRECTORY ${PROJECT_SOURCE_DIR}/resources/ DESTINATION ${BUNDLE_PATH}/Contents/Resources)

	# Make the bundle drag-n-drop
	get_filename_component(SFML_LIBRARY_DIR ${SFML_SYSTEM_LIBRARY} DIRECTORY)
	set(LIBRARIES_DIR ${THOR_LIBRARY_DIR};${SFML_LIBRARY_DIR})
	# Copy freetype manually, since it otherwise just causes problems (I think because it internally uses
	# @executable_path instead of @rpath)
	install(DIRECTORY ${SFML_LIBRARY_DIR}/freetype.framework DESTINATION ${BUNDLE_PATH}/Contents/Frameworks)
	# Let BundleUtilities do everything else automatically
	install(CODE "
		include(BundleUtilities)
		fixup_bundle(\"${BUNDLE_PATH}\" \"\" \"${LIBRARIES_DIR}\")
		" COMPONENT Runtime
	)
endif()

# -----------------------------------------
#  Setup the False bundle
# -----------------------------------------

add_executable(False MACOSX_BUNDLE ${PROJECT_MAIN})
target_link_libraries(False ${PROJECT_LIBRARIES} ${SOURCE_LIBRARY})

if(APPLE)
	set(MAKE_INSTALL_NAME_DIR @rpath)
	set_target_properties(False PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/osx/Info_False.plist.in)

	# Copy the assets and levels into the bundle
	set(BUNDLE_PATH ${CMAKE_CURRENT_BINARY_DIR}/False.app)
	install(DIRECTORY ${PROJECT_SOURCE_DIR}/resources/ DESTINATION ${BUNDLE_PATH}/Contents/Resources)

	# Make the bundle drag-n-drop
	get_filename_component(SFML_LIBRARY_DIR ${SFML_SYSTEM_LIBRARY} DIRECTORY)
	set(LIBRARIES_DIR ${THOR_LIBRARY_DIR};${SFML_LIBRARY_DIR})
	# Copy freetype manually, since it otherwise just causes problems (I think because it internally uses
	# @executable_path instead of @rpath)
	install(DIRECTORY ${SFML_LIBRARY_DIR}/freetype.framework DESTINATION ${BUNDLE_PATH}/Contents/Frameworks)
	# Let BundleUtilities do everything else automatically
	install(CODE "
		include(BundleUtilities)
		fixup_bundle(\"${BUNDLE_PATH}\" \"\" \"${LIBRARIES_DIR}\")
		" COMPONENT Runtime
	)
endif()
