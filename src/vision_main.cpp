#include "../include/vision.h"
// #include "constants.h"
#include <cstdlib>
#include "opencv2/opencv.hpp"
#include <stdio.h>
#include <iostream>
#include <jsoncpp/json/json.h>
#include <memory>
#include <fstream>

std::vector<float> jsonToFloatVector(const Json::Value& jsonArray)
{
  std::vector<float> result;
  if (!jsonArray.isArray())
  {
    std::cerr << "Input JSON is not an array!" << std::endl;
    return result;
  }
  for (unsigned int i = 0; i < jsonArray.size(); i++)
  {
    if (jsonArray[i].isDouble() or jsonArray[i].isInt())
    {
      result.push_back(static_cast<float>(jsonArray[i].asFloat()));
    }
    else
    {
      std::cerr << "Element is not a float number!" << std::endl;
    }
  }
  return result;
}

std::string keys = "{ help  h         |                           | Print help message. }"
                   "{ config c        | ../config/config.json     | Usage: Path to json config file.}"
                   "{ use_rgb         | true                      | Usage: enable the use of RGB camera.}"
                   "{ use_depth       | true                      | Usage : enable the use of Depth camera.}"
                   "{ rgbresolution   | 320x240                   | Available: 320x240, 640x480, 1280x720, 1920x1080}"
                   "{ depthresolution | 424x240                   | Available: 424x240, 480x270}";

int main(int argc, char** argv)
{
  cv::CommandLineParser parser(argc, argv, keys);

  parser.about("Non-ROS library for KINOVA® KORTEX™ arms vision module.");
  if (parser.has("help"))
  {
    parser.printMessage();
    return 0;
  }
  Json::Value parameters;
  std::ifstream config_doc(parser.get<std::string>("config"));
  config_doc >> parameters;
  std::string device_ip = parameters["device_ip"].asString();
  std::vector<float> static_transformation = jsonToFloatVector(parameters["static_transformation"]);
  std::unique_ptr<Vision> kv(new Vision());
  bool use_rgb_camera = (parser.get<std::string>("use_rgb") == "true");
  bool use_depth_camera = (parser.get<std::string>("use_depth") == "true");
  if (use_rgb_camera)
  {
    // ToDO
    kv->config_rgb_camera();
  }
  cv::Mat img(3, 3, CV_8UC3);        // TODO
  cv::Mat depth_img(3, 3, CV_8UC1);  // TODO
  if (use_depth_camera)
  {
    // ToDO
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