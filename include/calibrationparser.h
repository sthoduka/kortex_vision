#pragma once
#include <stdio.h>
#include <cstdlib>
#include <jsoncpp/json/json.h>
#include <iostream>
std::vector<float> jsonToFloatVector(const Json::Value& jsonArray);

class CameraCalibration
{
public:
  int height;
  int width;
  std::string type;
  std::vector<float> camera_matrix;
  std::vector<float> distortion;
  std::vector<float> rectification;
  std::vector<float> projection;
  CameraCalibration(const Json::Value& jsonArray);
  ~CameraCalibration();
};