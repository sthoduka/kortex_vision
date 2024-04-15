#include "../include/calibrationparser.h"

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

CameraCalibration::CameraCalibration(const Json::Value& jsonArray)
{
  if (jsonArray.isNull())
  {
    std::cerr << "Input JSON is Null!" << std::endl;
  }
  else
  {
    height = jsonArray["height"].asInt();
    width = jsonArray["width"].asInt();

    type = jsonArray["type"].asString();
    camera_matrix = jsonToFloatVector(jsonArray["camera_matrix"]);
    distortion = jsonToFloatVector(jsonArray["distortion"]);
    rectification = jsonToFloatVector(jsonArray["rectification"]);
    projection = jsonToFloatVector(jsonArray["projection"]);
  }
};
CameraCalibration::~CameraCalibration(){}

;