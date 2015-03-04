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

- Make a folder Quadcopter in your catkin_ws/src directory. go to that directory and clone tum_ardrone from https://github.com/tum-vision/tum_ardrone.git

- In catkin_ws/src/Quadcopter
```sh
$ git clone https://github.com/AutonomyLab/ardrone_autonomy.git -b hydro-devel
$ cd ~/catkin_ws
$ catkin_make
```

- You will get an error most probably.
- So now edit ~/catkin_ws/build/ardrone/tmp/ardronelib-gitclone.cmake 
- Change git:// to https://

```sh
$ roscd
$ catkin_make
```

- If you still get an error at this step, then some libraries aren't installed on your computer. The above package has the following dependencies and install them if you don't have them:

```sh
$ sudo apt-get install freeglut3-dev liblapack3gf liblapack-dev libblas3gf libblas-dev
```

- On success go to catkin_ws/src/Quadcopter and clone: tum_simulator from https://github.com/quadrotor-IITKgp/tum_simulator

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

Test it using

```sh
$ killall gzserver
$ killall gzclient
$ roslaunch quad_simulator arena.launch 
```