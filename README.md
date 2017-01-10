# meccanoid-tx1-project

This repo provides some general documentation (this README) about the Meccanoid TX1 project and source code implementations for the ROS nodes illustrated in the graph below: Hardware used in this project consists of

1. Meccanoid G15KS personal robot
2. Jetson TX1 development kit
3. 2x Arduino Uno + motor shield
4. Kinect v1 camera
5. Marvelmind ultrasonic indoor GPS system 
6. 7 port usb2 hub

<p align="center"> <img src="https://github.com/meccanoid-tx1/meccanoid-tx1-project/blob/master/rosgraph.png" alt="graph" width="400"/> </p>

## Meccanoid G15Ks

The base platform for this project is the Meccanoid G15KS personal robot. Assemble it according to the [instructions](http://cdn.meccano.com/notice/15402.pdf)

<p align="center"> <img align="center" src="https://d1whcn1ntmec99.cloudfront.net/images/catalog/products/meccano/g15ks/full1.jpg" alt="mecca" width="400"/> </p>

## Jetson TX1 dev kit

The primary embedded device used for this project is the Jetson TX1 development kit. Secondary devices for remote control of servos and motors consists of Arduino Uno's. The following sections provides links/instructions on how to set up the Jetson.

<p align="center"> <img align="center" src="http://images.nvidia.com/content/tegra/embedded-systems/images/jetson-tx1-developer-kits.png" alt="jetson" width="400"/> </p>


### Host (your computer)
Start by register an account on the Nvidia [Embedded Developer Program](https://developer.nvidia.com/embedded-developer-program) to get access to software and documentation needed to set up the Jetson TX1.

Once you've got the account go to the [Embedded Download Center](https://developer.nvidia.com/embedded/downloads) and download the **JetPack for L4T** installer and install both host and target software / connect everything according to the provided installation guidelines. *We used JetPack 2.3 for which your host computer will need to run Ubuntu 14.04 (works using a virual machine) and your Jetson will be running 64-bit Ubuntu 16.04.*

### Target (the Jetson)
Once Ubuntu is booted up on the target you can go about installing stuff, some scripts and suggestions is given below.

1. Put each of the following code snippets in separate files: ` your_file1.sh, your_file2.sh, ...` 
2. Make executable by running `$ chmod +x your_fileX.sh`
3. Execute each script as super user by running `$ sudo ./your_fileX.sh`.

#### Robot operating system

This script will clone install scripts from Jetsonhacks, execute them and fix permission issues. Default version is ROS Kinetic Base, if you need another version just clone the repo from Jetsonhacks and modify the install scripts prior to executing them.

```bash
#!/bin/bash

# url for jetsonhacks ROS kinetic install scripts
repo="https://github.com/jetsonhacks/installROSTX1.git"

# clone scripts to homefolder
git clone "$repo" "/home/ubuntu/ros_install"

# update repos
. '/home/ubuntu/ros_install/updateRepositories.sh'

# install ROS
. '/home/ubuntu/ros_install/installROS.sh'

# fix dependency issues since script should be called by super user
rosdep fix-permissions
rosdep update
```

#### Kinect drivers

This script will install Kinect drivers and disable usb auto-suspend. If usb auto suspend is on, the data stream from the Kinect camera is killed.

```bash
#!/bin/bash

# ----------------------------------------------------
# Jetpack 2.3 pre-installs the following dependencies
# ----------------------------------------------------
# apt-get install freeglut3-dev
# apt-get install pkg-config
# apt-get install build-essential
# apt-get install libxmu-dev
# apt-get install libxi-dev
# ----------------------------------------------------

# libusb 1.0 development headers
apt-get install libusb-1.0-0-dev

# Add ubuntu launchpad repository
add-apt-repository ppa:floe/libtisch
apt-get update

# Install freenect driver, development headers and demo apps
apt-get install freenect libfreenect-dev libfreenect-demos

# Add user to plugdec
adduser $USER plugdev

# Disable usb auto suspend from boot up script hence forward
sed -i '$s/$/ usbcore.autosuspend=-1/' /boot/extlinux/extlinux.conf

# Disable usb auto suspend for the current session 
bash -c 'echo -1 > /sys/module/usbcore/parameters/autosuspend'
```
you may sometimes may not be able to connect to the video feed of the kinect in that case you may have to install PrimeSense Sensor Module for OpenNI from
```
# Clone Repository
git clone https://github.com/avin2/SensorKinect

# Go into the Directory of Driver Install
cd Bin

#Install Driver
tar xjf SensorKinect093-Bin-Linux-x64-v5.1.2.1.tar.bz2
cd Sensor-Bin-Linux-x64-v5.1.2.1
./install.sh
```

#### ROS Kinect node

This script will install the ROS openni Kinect node for the Kinetic distribution which is used for publishing image data from the Kinect camera to a ROS topic. If you have another ROS distribution change `kinetic` to your distribution name eg. `install ros-your_distribution_name-openni-camera`.

```bash
#!/bin/bash

# install ros kinect driver for publishing sensor_msgs/Image see: wiki.ros.org/openni_camera
apt-get install ros-kinetic-openni-camera

# install ros kinect launch stack, lots of stuff.. see: wiki.ros.org/openni_launch
apt-get install ros-kinetic-openni-launch

# install image view package see: wiki.ros.org/image_view
apt-get install ros-kinetic-image-view
```

#### ROS Serial (arduino) node

This script will install the ROS serial node for communication over serial ports.

```bash
#!/bin/bash

# Ardiuno specific extensions, see: http://wiki.ros.org/rosserial_arduino
apt-get install ros-kinetic-rosserial-arduino

# ROS Serial protocol, see: http://wiki.ros.org/rosserial
apt-get install ros-kinetic-rosserial
```

Then set up ros_lib in the arduino environment by typing the following: (where `<sketchbook>` is the path of your Arduino sketchbook libraries)
 
```bash
$ cd <sketchbook>/libraries
$ rm -rf ros_lib
$ rosrun rosserial_arduino make_libraries.py .
```

#### The Code

1. Set up a Catkin workspace called "meccanoid_ws" in your (jetson) home folder `/ubuntu/home` (must be this name since currently using hard coded path in face detection node, if you want another name, change the path in the face detection node).

2. Clone this repo and replace the autogenerated (empty) `src` folder with this `src` folder at the root of the workspace. Also put the `res` folder at the root of the Catkin workspace.

3. From the root of the Catkin workspace run `catkin make` 

#### Set up persistent names for usb devices

Connected USB devices (currently 3pcs, 2x Arduino + 1 Marvelmind beacon) change virtual serial ports when disconnected or even randomly when connected... Set up persistent names by creating symlinks as described [here](http://hintshop.ludvig.co.nz/show/persistent-names-usb-serial-devices/). For example:

1. Servo arduino connected at: /dev/head_arduino
2. Motor arduino connected at: /dev/motor_arduino
3. Beacon connection at: /dev/beacon

## Arduino UNO's

Connect the arduinos via the USB hub to the Jetson and to their respective motors/servos.

<p align="center"> <img align="center" src="http://www.arduino.org/media/k2/galleries/90/A000066-Arduino-Uno-TH-1front.jpg" alt="uno" width="400"/> </p>

Push the arduino code from `meccanoid_motor_control` and `meccanoid_servo_control` from the `src/meccanoid_tx1_arduino` folder to each arduino connected to the motors/servos.

## Marvelmind positioning system

Connect the hedge (mobile beacon) via the USB hub to the Jetson and the modem to a computer running Windows and 
set up the Marvelmind sofware on the Windows machine as described [here](http://www.marvelmind.com/).

<p align="center"> <img align="center" src="http://www.marvelmind.com/pics/IMG_4469_1024a.jpg" alt="marvel" width="400"/> </p>

## Running the code

Given the serial-port symlinks above run this script to start everything. (roslaunch were giving us problems since we start 3 serial connections and there is not any way of introducing "delays" between node start up in launch files).

```bash
#!/bin/bash

xterm -hold -e "roscore" &
sleep 8 &
xterm -hold -e "rosrun openni_camera openni_node" &
sleep 2 &
xterm -hold -e "rosrun meccanoid_tx1 meccanoid_face_detection_node" &
sleep 2 &
xterm -hold -e "rosrun meccanoid_tx1 meccanoid_obstacle_avoidance_node" &
sleep 2 &
xterm -hold -e "rosrun rosserial_python serial_node.py /dev/motor_arduino __name:=motorarduino" &
sleep 2 &
xterm -hold -e "rosrun rosserial_python serial_node.py /dev/head_arduino __name:=headarduino " &
sleep 2 &
xterm -hold -e "rosrun meccanoid_tx1 meccanoid_teleop_node" &
sleep 2 &
xterm -hold -e "rosrun meccanoid_tx1 meccanoid_positioning_node /dev/beacon" &
echo "launched core and all nodes!"
```
