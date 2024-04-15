# Kinova Vision module package

## Overview
TODO


## Installation
TODO

### Building from Source

#### Dependencies
##### OpenCV
* OpenCV
  
##### JSON parser package
* libjsoncpp1

```sh
sudo apt install libjsoncpp1
```

##### GStreamer packages
* gstreamer1.0-tools
* libgstreamer1.0-libav
* libgstreamer1.0-dev 
* libgstreamer-plugins-base1.0-dev 
* libgstreamer-plugins-good1.0-dev
* gstreamer1.0-plugins-good
* gstreamer1.0-plugins-base

```sh
sudo apt install gstreamer1.0-tools gstreamer1.0-libav libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev libgstreamer-plugins-good1.0-dev gstreamer1.0-plugins-good gstreamer1.0-plugins-base
```

#### Building

To build from source, clone the latest version from this repository.

1. Create a catkin workspace
```bash
mkdir build
cd build
cmake ..
make
```

## Usage

### Start roscore (if not already started)
```bash
cd build
./KinovaVisionMain
```

### Specifying launch options
It's possible to override the default argument values when launching the **kinova_vision** node.

Arguments are set using the following syntax: `<argument>:=<value>`.

For instance, the default value of the `device` argument can be overridden to specify another IP address.
```bash
roslaunch kinova_vision kinova_vision_rgbd.launch device:=10.20.0.100
```
#### Additional information on arguments `color_camera_info_url` and `depth_camera_info_url`

These arguments specify the custom camera information file to use instead of the default camera information file.

The file is specified via a specific URL syntax, using either of these two formats:

`package://<package_name>/relative/path/to/file`

`file:///absolute/path/to/file`

For example:
```bash
roslaunch kinova_vision kinova_vision_rgbd.launch color_camera_info_url:=file:///home/user/custom_color_calib_1280x720.ini depth_camera_info_url:=file:///home/user/custom_depth_calib_480x270.ini
```

A custom camera information file is typically created from a default information file (refer to *launch/calibration/default_\*.ini*). Then, one simply needs to adjust the proper matrices.

The following matrices need to be adjusted with the proper values for `FX`, `FY`, `PPX`, `PPY`:
```
camera matrix
FX 0.00000 PPX
0.00000 FY PPY
0.00000 0.00000 1.00000

projection
FX 0.00000 PPX 0.00000 
0.00000 FY PPY 0.00000 
0.00000 0.00000 1.00000 0.00000 
```

The values for `FX`, `FY`, `PPX`, `PPY` can be obtained via the Vision module API. They represent the _focal length_ and the _principal point offset_ in both the _x_ and _y_ coordinates.

<a name="rviz_config_files"></a>
## Rviz configuration files

* **color_only.rviz:** View the images coming from the color camera only. The package needs to be launched with *kinova_vision_color_only.launch*, *kinova_vision.launch* or *kinova_vision_rgbd.launch*.

<p align="left"> <img alt="color_only.rviz.png" src="doc/color_only.rviz.png" title="Color only"/> </p>

* **depth_only.rviz:** View the images and the depth cloud coming from the depth camera only. The package needs to be launched with *kinova_vision_depth_only.launch*, *kinova_vision.launch* or *kinova_vision_rgbd.launch*.

<p align="left"> <img alt="depth_only.rviz.png" src="doc/depth_only.rviz.png" title="Depth only"/> </p>

* **depth_and_color.rviz:** View the images coming from the color camera as well as the images and the depth cloud coming from the depth camera. The package needs to be launched with *kinova_vision.launch* or *kinova_vision_rgbd.launch*.

<p align="left"> <img alt="depth_and_color.rviz.png" src="doc/depth_and_color.rviz.png" title="Depth and color"/> </p>

* **depth_and_color_rgbd.rviz:** View the images coming from the color camera as well as the images, the RGBD point cloud and the depth cloud coming from the depth camera. The package needs to be launched with *kinova_vision_rgbd.launch*.

<p align="left"> <img alt="depth_and_color_rgbd.rviz.png" src="doc/depth_and_color_rgbd.rviz.png" title="Depth and color with rgbd"/> </p>

<a name="nodes"></a>
## Nodes

### kinova_vision_color

This node publishes the raw stream and the meta information of the color camera.



### kinova_vision_depth

This node publishes the raw stream and the meta information of the depth camera.

