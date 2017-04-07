# quad_simulator
Simulator for the Quadrotor Project, IIT Kharagpur

For setting it up:

#### Install Gazebo:
Make sure you have gazebo 2.x.x installed, to check run
```sh
$ gazebo --version
```
If the version is not 2.x.x, purge gazebo and its ros packages
```sh
$ sudo apt-get purge gazebo* ros-indigo-gazebo*
```
Install gazebo2 and its ros packages
```sh
$ sudo apt-get install gazebo2
$ sudo apt-get install ros-indigo-gazebo-ros-pkgs ros-indigo-gazebo-ros-control
```

#### Install Dependencies
Install these dependencies
- `$ sudo apt-get install libsdl1.2-dev`
- `$ sudo apt-get install liblapack-dev -y ; sudo apt-get install liblapack3 -y ; sudo apt-get install libopenblas-base -y ; sudo apt-get install libopenblas-dev -y ;`
- `$ sudo apt-get install freeglut3 freeglut3-dev`

#### Get ROS Packages for Simulator
Clone these repositories in a catkin workspace
- `$ git clone https://github.com/quadrotor-IITKgp/ardrone_autonomy.git`
- `$ git clone https://github.com/quadrotor-IITKgp/tum_simulator.git`
- `$ git clone https://github.com/quadrotor-IITKgp/quad_simulator.git`
- `$ git clone https://github.com/quadrotor-IITKgp/tum_ardrone.git`
- Checkout to `ark-world` branch of tum_simulator
- Checkout to `indigo-devel` branch of ardrone_autonomy
- Checkout to `indigo-devel` branch of tum_ardrone

#### Build

- `$ catkin_make`

#### Run the Simulator

- `$ roslaunch cvg_sim_gazebo iarc_with_bots.launch` and `$ rosrun quad_simulator groundbot_node`
- or `$ roslaunch cvg_sim_gazebo iarc_world.launch` for only MAV and IARC arena without ground bots.
- `$ rosrun tum_ardrone drone_autopilot`
- `$ rosrun tum_ardrone drone_stateestimation`
- `$ rosrun tum_ardrone drone_gui`

