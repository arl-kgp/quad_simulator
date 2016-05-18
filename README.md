# quad_simulator
Simulator for the Quadrotor Project, IIT Kharagpur

For setting it up:

Install Gazebo:
```sh
$ sudo apt-get install ros-indigo-gazebo-ros-pkgs ros-indigo-gazebo-ros-control
```

Now edit ~/.bashrc and add the following lines at the end of the file.
```sh
source ~s/catkin_ws/devel/setup.bash
export ROS_WORKSPACE=~/catkin_ws/
export ROS_PACKAGE_PATH+=~/catkin_ws/src
export GAZEBO_MODEL_PATH=~/gazebo_models/
export GAZEBO_RESOURCE_PATH=/usr/share/gazebo-2.2/worlds/
```

- Extract [gazebo_models.zip](https://drive.google.com/file/d/0B-yT84mLsuTTOGFlRUtBeWktdVk/view?usp=sharing) to your home folder

