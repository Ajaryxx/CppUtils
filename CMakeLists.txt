cmake_minimum_required(VERSION 3.31.6)

#define project
project(CppUtils
VERSION 1.0.0
LANGUAGES CXX)

#define variables
set(LIB "CppUtils")

#create interface lib
add_library(${LIB} INTERFACE)

set_target_properties(${LIB} PROPERTIES
CXX_STANDARD 11
CXX_STANDARD_REQUIRED ON
CXX_EXTENSIONS OFF
)

#Export lib
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

#include directories
target_include_directories(${LIB} INTERFACE
"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

#export targets
install(TARGETS ${LIB}
	EXPORT LIB_TARGETS

	INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

#export namespace
install(EXPORT LIB_TARGETS
	FILE CppUtilsTargets.cmake
	NAMESPACE CppUtils::
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/CppUtils
)

#create config file
configure_package_config_file(
	${CMAKE_CURRENT_SOURCE_DIR}/cmake/CppUtilsConfig.cmake.in
	${CMAKE_CURRENT_BINARY_DIR}/CppUtilsConfig.cmake

	INSTALL_DESTINATION
		${CMAKE_INSTALL_LIBDIR}/cmake/CppUtils
)

#move config file
install(FILES
	${CMAKE_CURRENT_BINARY_DIR}/CppUtilsConfig.cmake

	DESTINATION
	${CMAKE_INSTALL_LIBDIR}/cmake/CppUtils
)

#move include dir
install(DIRECTORY
	${CMAKE_CURRENT_SOURCE_DIR}/include/
	
	DESTINATION
	${CMAKE_INSTALL_INCLUDEDIR}
)


#add subdirectories
add_subdirectory(tests)