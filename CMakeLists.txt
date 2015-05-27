cmake_minimum_required (VERSION 2.8.7)

project(Stragnar_CV)

include(ExternalProject)
include(CheckCXXCompilerFlag)

message(${OpenCV_DIR})

# Set the version number
set (Stragnar_CV_VERSION_MAJOR 0)
set (Stragnar_CV_VERSION_MINOR 1)

CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -O3")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

# Configure a header to pass some CMake settings to the source.
configure_file (
    "${Stragnar_CV_SOURCE_DIR}/examples/cpp/Stragnar_CV_Config.h.in"
    "${Stragnar_CV_BINARY_DIR}/examples/cpp/Stragnar_CV_Config.h"
)

# Add the binary directory to the search include path to find 
# Stragnar_CV_Config.h
include_directories("${Stragnar_CV_BINARY_DIR}")
include_directories("${Stragnar_CV_SOURCE_DIR}")

# Add the 'hello world' executable
add_executable(hello_world examples/cpp/hello_world)

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
    -DBUILD_NEW_PYTHON_SUPPORT:BOOL=ON
    -DBUILD_PACKAGE:BOOL=ON
    -DBUILD_SHARED_LIBS:BOOL=ON
    -DBUILD_TESTS:BOOL=OFF
    -DWITH_FFMPEG:BOOL=OFF
    -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_BINARY_DIR}/INSTALL
)

if (OpenCV_FOUND)
    add_executable(copy_matrix examples/cpp/copy_matrix)
    add_executable(video_cap examples/cpp/video_cap)
    add_executable(headshots examples/cpp/headshots)

    add_dependencies(copy_matrix OpenCV)
    add_dependencies(video_cap OpenCV)
    add_dependencies(headshots OpenCV)

    include_directories(${OpenCV_INCLUDE_DIRS})

    target_link_libraries(copy_matrix ${OpenCV_LIBRARIES})
    target_link_libraries(video_cap ${OpenCV_LIBRARIES})
    target_link_libraries(headshots ${OpenCV_LIBRARIES})
endif (OpenCV_FOUND)

