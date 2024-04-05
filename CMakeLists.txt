cmake_minimum_required(VERSION 2.8.3)

project(kinova_vision)

# System Dependencies
find_package(PkgConfig)

pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0)
pkg_check_modules(GST_APP REQUIRED gstreamer-app-1.0)
pkg_check_modules(JSONCPP jsoncpp)


include_directories(
  include
  ${GLIB_INCLUDE_DIRS}
  ${GST_APP_INCLUDE_DIRS})

add_library(KinovaVision src/vision.cpp)
target_link_libraries(KinovaVision
${JSONCPP_LIBRARIES}
  ${GSTREAMER_LIBRARIES}
  ${GST_APP_LIBRARIES})

add_executable(KinovaVision_main src/vision_main.cpp)


set(CMAKE_CXX_FLAGS "-fpermissive")