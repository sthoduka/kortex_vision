#include "../include/vision.h"
#include "../include/calibrationparser.h"
// #include "constants.h"
#include <cstdlib>
#include "opencv2/opencv.hpp"
#include <stdio.h>
#include <iostream>
#include <jsoncpp/json/json.h>
#include <memory>
#include <fstream>

std::string keys = "{ help  h        |                       | Print help message. }"
                   "{ config c       | ../config/config.json | Usage: Path to json file.}"
                   "{ use_rgb        | true                  | Usage: enable use of RGB cam.}"
                   "{ use_depth      | true                  | Usage : enable use Depth cam.}"
                   "{ rgbresolution  | 320x240               | Available: 320x240, 640x480, 1280x720, 1920x1080}"
                   "{ depthresolution| 424x240               | Available: 424x240, 480x270}";

int main(int argc, char** argv)
{
  cv::CommandLineParser parser(argc, argv, keys);

  parser.about("Non-ROS library for KINOVA® KORTEX™ arms vision module.");
  if (parser.has("help"))
  {
    parser.printMessage();
    return 0;
  }
  Json::Value param;
  std::ifstream config_doc(parser.get<std::string>("config"));
  config_doc >> param;
  std::string device_ip = param["device_ip"].asString();
  std::vector<float> static_transformation = jsonToFloatVector(param["static_transformation"]);
  std::unique_ptr<Vision> kv(new Vision());
  bool use_rgb_camera = (parser.get<std::string>("use_rgb") == "true");
  bool use_depth_camera = (parser.get<std::string>("use_depth") == "true");
  std::string depth_resolution = parser.get<std::string>("depthresolution");
  std::string rgb_resolution = parser.get<std::string>("rgbresolution");
  Json::Value rgb_camera_calibration =
      (use_rgb_camera) ? param["rgb"]["camera_calibrations"][rgb_resolution] : Json::nullValue;
  Json::Value depth_camera_calibration =
      (use_depth_camera) ? param["depth"]["camera_calibrations"][depth_resolution] : Json::nullValue;
  cv::Mat img, depth_img;

  if (use_rgb_camera)
  {
    std::unique_ptr<CameraCalibration> rgb_setting(new CameraCalibration(rgb_camera_calibration));
    img = cv::Mat(rgb_setting->height, rgb_setting->width, CV_8UC3);
    std::string camera_name = rgb_setting->type;
    std::string frame_id = "TODO";
    kv->config_rgb_camera(camera_name, frame_id);
  }

  if (use_depth_camera)
  {
    std::unique_ptr<CameraCalibration> depth_setting(new CameraCalibration(depth_camera_calibration));
    depth_img = cv::Mat(depth_setting->height, depth_setting->width, CV_8UC1);  // TODO
    kv->config_depth_camera();
  }
  kv->run();
  if (use_depth_camera and use_rgb_camera)
  {
    kv->get_color_and_depth_image(img, depth_img);
  }
  else if (use_depth_camera)
  {
    kv->get_depth_image(depth_img);
  }
  else if (use_rgb_camera)
  {
    kv->get_color_image(img);
  }

  kv->stop();
  return EXIT_SUCCESS;
}