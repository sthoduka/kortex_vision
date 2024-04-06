#include "../include/vision.h"
// #include "constants.h"
#include <cstdlib>
#include "opencv2/opencv.hpp"
#include <stdio.h>
#include <iostream>
#include <jsoncpp/json/json.h>
#include <memory>

std::string keys = "{ help  h          |                           | Print help message. }"
                   "{ config c         | ../config/config.json     | Usage: Path to json config file.}";

int main(int argc, char** argv)
{
  cv::CommandLineParser parser(argc, argv, keys);

  parser.about("Non-ROS library for KINOVA® KORTEX™ arms vision module.");
  if (parser.has("help"))
  {
    parser.printMessage();
    return 0;
  }
  return EXIT_SUCCESS;
}