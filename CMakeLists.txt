cmake_minimum_required (VERSION 2.8.7)

project(Stragnar_CV)

include(ExternalProject)
include(CheckCXXCompilerFlag)

# Set the version number
set (Stragnar_CV_VERSION_MAJOR 0)
set (Stragnar_CV_VERSION_MINOR 1)
set (CMAKE_VERBOSE_MAKEFILE false)
set (CMAKE_RULE_MESSAGES OFF)

CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -O3")
else()
    message(ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

# Configure a header to pass some CMake settings to the source.
configure_file (
    "${Stragnar_CV_SOURCE_DIR}/src/Stragnar_CV_Config.h.in"
    "${Stragnar_CV_BINARY_DIR}/src/Stragnar_CV_Config.h"
)

# Add the binary directory to the search include path to find 
# Stragnar_CV_Config.h
include_directories("${Stragnar_CV_BINARY_DIR}")
include_directories("${Stragnar_CV_SOURCE_DIR}")

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

find_package(OpenCV REQUIRED)
if (OpenCV_FOUND)
    # auto_allocation.cpp    error_handling.cpp     matrix_operations.cpp  out_and_in_array.cpp   saturation_casts.cpp   smart_pointers.cpp
    add_executable(auto_allocation src/introduction/auto_allocation)
    add_executable(error_handling src/introduction/error_handling)
    add_executable(matrix_operations src/introduction/matrix_operations)
    add_executable(out_and_in_array src/introduction/out_and_in_array)
    add_executable(saturation_casts src/introduction/saturation_casts)
    add_executable(smart_pointers src/introduction/smart_pointers)

    add_dependencies(auto_allocation OpenCV)
    add_dependencies(error_handling OpenCV)
    add_dependencies(matrix_operations OpenCV)
    add_dependencies(out_and_in_array OpenCV)
    add_dependencies(saturation_casts OpenCV)
    add_dependencies(smart_pointers OpenCV)

    include_directories(${OpenCV_INCLUDE_DIRS})

    target_link_libraries(auto_allocation ${OpenCV_LIBRARIES})
    target_link_libraries(error_handling ${OpenCV_LIBRARIES})
    target_link_libraries(matrix_operations ${OpenCV_LIBRARIES})
    target_link_libraries(out_and_in_array ${OpenCV_LIBRARIES})
    target_link_libraries(saturation_casts ${OpenCV_LIBRARIES})
    target_link_libraries(smart_pointers ${OpenCV_LIBRARIES})
endif (OpenCV_FOUND)

