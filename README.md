# quad_simulator
Simulator for the Quadrotor Project, IIT Kharagpur

Prerequisites for running the codes :

1. ROS Hydro or above must be installed.
2. The tum_simulator at https://github.com/tum-vision/tum_simulator must be on the system for using the ardrone simulation.
3. Make sure the GAZEBO_MODEL_PATH rightly points to the gazebo models folder.

To setup the simulator :

- Add the iarc_arena folder to the GAZEBO_MODEL_PATH as set in the environment.

Install Gazebo:
```sh
$ sudo apt-get install ros-indigo-gazebo-ros-pkgs ros-indigo-gazebo-ros-control
```

Now edit .bashrc and add the following lines at the end of the file.
```sh
source /home/manash/catkin_ws/devel/setup.bash
export ROS_WORKSPACE=~/catkin_ws/
export ROS_PACKAGE_PATH+=~/catkin_ws/src
export GAZEBO_MODEL_PATH=~/gazebo_models/
export GAZEBO_RESOURCE_PATH=/usr/share/gazebo-2.2/worlds/
```

- Extract [gazebo_models.zip](https://drive.google.com/file/d/0B-yT84mLsuTTOGFlRUtBeWktdVk/view?usp=sharing) to your home folder

Make a folder Quadcopter in your catkin_ws/src directory. go to that directory and clone tum_ardrone from https://github.com/tum-vision/tum_ardrone.git
```sh
$ roscd
$ catkin_make
```

- You will get an error most probably.
- So now edit ~/catkin_ws/build/ardrone/tmp/ardronelib-gitclone.cmake 
- Change git:// to https://

```sh
$ roscd
$ catkin_make
```

catkin_ws/src/Quadcopter
```sh
$ git clone https://github.com/AutonomyLab/ardrone_autonomy.git -b hydro-devel
$ cd ~/catkin_ws
$ catkin_make
$ roscd
$ catkin_make
```

- On success go to catkin_ws/src/Quadcopter and clone: tum_simulator from https://github.com/tum-vision/tum_simulator.git

- Go to catkin_ws/src/Quadcopter/tum_simulator/cvg_sim_gazebo_plugins

- Edit CMakeLists.txt 
- Search for ${SDFormat_INCLUDE_DIRS} in that file and add /usr/include/gazebo-2.2/gazebo/ after it on the next line

- Go to catkin_ws/src/Quadcopter/tum_simulator/cvg_sim_gazebo_plugins and replace all occurrences of  
    - shared_dynamic_cast with dynamic_pointer_cast
    - DisconnectWorldUpdateStart with DisconnectWorldUpdateBegin

in each of the following files
diffdrive_plugin_6w.cpp,   gazebo_ros_sonar.cpp ,gazebo_ros_baro.cpp  
quadrotor_simple_controller.cpp, gazebo_ros_gps.cpp, quadrotor_state_controller.cpp
gazebo_ros_imu.cpp, gazebo_ros_magnetic.cpp

```sh
$ roscd
$ catkin_make 
```

If it is successfully built then go to 
catkin_ws/src/Quadcopter/ and clone Quad Simulator
https://github.com/quadrotor-IITKgp/quad_simulator.git

```sh
$ roscd
$ catkin_make 
```

If everything runs successfully then quad simulator is installed.

test it using

```sh
$ killall gzserver
$ killall gzclient
$ roslaunch quad_simulator arena.launch 
```