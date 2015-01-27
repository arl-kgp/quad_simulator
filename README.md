# quad_simulator
Simulator for the Quadrotor Project, IIT Kharagpur

Prerequisites for running the codes :

1. ROS Hydro or above must be installed.
2. The tum_simulator at https://github.com/tum-vision/tum_simulator must be on the system for using the ardrone simulation.
3. Make sure the GAZEBO_MODEL_PATH rightly points to the gazebo models folder.

To setup the simulator :

-> Add the iarc_arena folder to the GAZEBO_MODEL_PATH as set in the environment.

To run the simulator for the current arena : <br />
 $ roslaunch quad_simulator arena.launch
