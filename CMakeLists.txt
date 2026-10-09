cmake_minimum_required(VERSION 3.31.6)

#define project
project(CppUtils
VERSION 1.0.0
LANGUAGES CXX)

#define variables
set(LIB "CppUtils")

#define options
option(BUILD_STATIC "Build library as static" ON)
option(BUILD_SHARED "Build library as shared" OFF)


#check BUILD_STATIC and BUILD_SHARED both enabled
if (BUILD_STATIC AND BUILD_SHARED)
message(FATAL_ERROR "You cannot have BUILD_STATIC and BUILD_SHARED both enabled!")

elseif(NOT BUILD_STATIC AND NOT BUILD_SHARED)
message(FATAL_ERROR "You cannot have BUILD_STATIC and BUILD_SHARED both disabled!")
endif()

#create static or shared lib
if(BUILD_STATIC)
add_library(${LIB} STATIC "dummy.cpp")
else()
add_library(${LIB} SHARED "dummy.cpp")
endif()

#Export lib
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

#include directories
target_include_directories(${LIB} PUBLIC
"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

#export targets
install(TARGETS ${LIB}
	EXPORT LIB_TARGETS

	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	
	INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

#export namespace
install(EXPORT LIB_TARGETS
	FILE CppUtilsTargets.cmake
	NAMESPACE CppUtils::
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/CppUtils)

#create config file
configure_package_config_file(
	${CMAKE_CURRENT_SOURCE_DIR}/cmake/CppUtilsConfig.cmake.in
	${CMAKE_CURRENT_BINARY_DIR}/CppUtilsConfig.cmake

	INSTALL_DESTINATION
		${CMAKE_INSTALL_LIBDIR}/cmake/CppUtils)

#move config file
install(FILES
	${CMAKE_CURRENT_BINARY_DIR}/CppUtilsConfig.cmake

	DESTINATION
	${CMAKE_INSTALL_LIBDIR}/cmake/CppUtils)

#move include dir
install(DIRECTORY
	${CMAKE_CURRENT_SOURCE_DIR}/include/
	
	DESTINATION
	${CMAKE_INSTALL_INCLUDEDIR})


#add subdirectories
add_subdirectory(src)
add_subdirectory(tests)