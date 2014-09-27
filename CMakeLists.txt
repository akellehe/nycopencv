cmake_minimum_required (VERSION 2.8.7)

project(Stragnar_CV)
include(ExternalProject)

# Set the version number
set (Stragnar_CV_VERSION_MAJOR 0)
set (Stragnar_CV_VERSION_MINOR 1)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") 

# Configure a header to pass some CMake settings to the source.
configure_file (
    "${Stragnar_CV_SOURCE_DIR}/src/Stragnar_CV_Config.h.in"
    "${Stragnar_CV_BINARY_DIR}/src/Stragnar_CV_Config.h"
)

# Add the binary directory to the search include path to find 
# Stragnar_CV_Config.h
include_directories("${Stragnar_CV_BINARY_DIR}")
include_directories("${Stragnar_CV_SOURCE_DIR}")

# Add the executable
add_executable(hello_world src/hello_world)
add_executable(copy_matrix src/copy_matrix)

# Get opencv
message( "External project - OpenCV" )

ExternalProject_Add(OpenCV
  GIT_REPOSITORY https://github.com/itseez/opencv.git 
  GIT_TAG 3.0.0-alpha
  SOURCE_DIR OpenCV 
  BINARY_DIR OpenCV-build
  INSTALL_DIR OpenCV-install 
  CMAKE_ARGS
    ${ep_common_args}
    -DBUILD_DOCS:BOOL=OFF
    -DBUILD_EXAMPLES:BOOL=OFF
    -DBUILD_NEW_PYTHON_SUPPORT:BOOL=OFF
    -DBUILD_PACKAGE:BOOL=ON
    -DBUILD_SHARED_LIBS:BOOL=ON
    -DBUILD_TESTS:BOOL=OFF
    -DWITH_FFMPEG:BOOL=OFF
    #-DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_BINARY_DIR}/INSTALL
)

add_dependencies(copy_matrix OpenCV)

find_package(OpenCV REQUIRED)
if (OpenCV_FOUND)
    include_directories(${OpenCV_INCLUDE_DIRS})
    target_link_libraries(copy_matrix ${OpenCV_LIBRARIES})
endif (OpenCV_FOUND)

