#ifndef KINOVA_VISION_H
#define KINOVA_VISION_H

#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>

extern "C" {
#include <gst/gst.h>
#include <gst/app/gstappsink.h>
}

// #include <image_transport/image_transport.h>
// #include <camera_info_manager/camera_info_manager.h>

namespace CameraTypes
{
enum CameraType
{
  Unknown = 0,
  Color = 1,
  Depth = 2,
};
}

class Vision
{
public:
  Vision();
  // Vision(ros::NodeHandle nh_camera, ros::NodeHandle nh_private);
  ~Vision();

  void run();
  void quit();
  void config_rgb_camera(std::string camera_name, std::string frame_id);
  void config_depth_camera();
  void stop();
  void get_color_image(cv::Mat& img);
  void get_depth_image(cv::Mat& depth_img);
  void get_color_and_depth_image(cv::Mat& img, cv::Mat& depth_img);

private:
  bool configure();
  bool initialize();
  bool start();
  bool loadCameraInfo();
  bool publish();
  bool changePipelineState(GstState state);

private:
  // ROS elements
  // ros::NodeHandle nh_;
  // ros::NodeHandle nh_private_;
  // camera_info_manager::CameraInfoManager camera_info_manager_;
  // image_transport::CameraPublisher camera_publisher_;
  // image_transport::ImageTransport image_transport_;

  // Gstreamer elements
  GstElement* gst_pipeline_;
  GstElement* gst_sink_;

  // General gstreamer configuration
  std::string camera_config_;
  std::string camera_name_;
  std::string camera_info_;
  std::string frame_id_;
  std::string image_encoding_;
  std::string base_frame_id_;

  bool is_started_;
  bool stop_requested_;
  bool quit_requested_;
  int retry_count_;
  int camera_type_;
  double time_offset_;
  int image_width_;
  int image_height_;
  int pixel_size_;
  bool use_gst_timestamps_;
  bool is_first_initialize_;
};

#endif
