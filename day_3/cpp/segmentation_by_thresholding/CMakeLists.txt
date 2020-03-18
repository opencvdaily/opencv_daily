cmake_minimum_required(VERSION 2.8)
project(segmentation_by_thresholding)


set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/build;${CMAKE_MODULE_PATH}")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


include_directories(
  include
  /usr/local/include/opencv2/
)

# Set CMake Vars
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# Add Image Blender Executable
add_executable(segmentation_by_thresholding
        src/thresholding.cpp)

target_link_libraries(segmentation_by_thresholding
  /usr/local/lib/libopencv_core.so
  /usr/local/lib/libopencv_highgui.so
  /usr/local/lib/libopencv_imgcodecs.so
  /usr/local/lib/libopencv_imgproc.so
)

# Add Install Targets
# install (TARGETS segmentation_by_thresholding DESTINATION bin)