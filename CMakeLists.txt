cmake_minimum_required(VERSION 2.8.3)

project(kinova_vision)

# System Dependencies
find_package(PkgConfig)
find_package(OpenCV REQUIRED COMPONENTS core highgui imgproc)

pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0)
pkg_check_modules(GST_APP REQUIRED gstreamer-app-1.0)
pkg_check_modules(JSONCPP REQUIRED jsoncpp)

include_directories(
  include
  ${OpenCV_INCLUDE_DIRS}
  ${JSON_INCLUDE_DIRS}
  ${GLIB_INCLUDE_DIRS}
  ${GST_APP_INCLUDE_DIRS}
)

set(CMAKE_CXX_FLAGS "-fpermissive")

add_library(KinovaVision src/vision.cpp)
target_link_libraries(KinovaVision
  ${OpenCV_LIBS}
  ${JSONCPP_LIBRARIES}
  ${GSTREAMER_LIBRARIES}
  ${GST_APP_LIBRARIES}
)

  
add_executable(KinovaVisionMain src/vision_main.cpp)
target_link_libraries(KinovaVisionMain PRIVATE  
  KinovaVision
  ${OpenCV_LIBS}
  ${JSONCPP_LIBRARIES}
  ${GSTREAMER_LIBRARIES}
  ${GST_APP_LIBRARIES}
)
