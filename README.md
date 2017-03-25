# quad_simulator
Simulator for the Quadrotor Project, IIT Kharagpur

For setting it up:

Install Gazebo:
```sh
$ sudo apt-get install ros-indigo-gazebo-ros-pkgs ros-indigo-gazebo-ros-control
```
- `$ git clone ardrone_autonomy`
- `$ git clone tum_ardrone`
- `$ git clone quad_simulator`
- Checkout to `ark-world` branch of ardrone_autonomy
- `$ catkin_make`
- `$ roslaunch cvg_sim_gazebo iarc_with_bots.launch` and `$ rosrun quad_simulator groundbot_node`
- or `$ roslaunch cvg_sim_gazebo iarc_world.launch` for only MAV and IARC arena without ground bots.

