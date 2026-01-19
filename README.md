# ROS2 Linear Actuator Controller - for Simulation
Repository that holds my progress for the project. This is a small project that I aim to use to keep my skills in Mechatronics Control Simulation in practice. I am trying to create a simple controller for a linear actuator model from a previous project. The simulation will be in ROS2 with gazebo, however I want to be able to send commands to both the sim and the actual linear actuator I have. In this way I'm planning to use this project as a way to learn and experiment with Rust as well.


## Current Progress 
- URDF File and Rviz Simulation

Commands to launch:

from workspace directory
```bash
colcon build --symlink-install
source install/setup.bash
ros2 launch linear_actuator actuator_launch.launch
```
note: source install is unessacry if the environment has been properly sourced in the bashrc

## To Do Next 
- Set up simple controller in C++
- Create a Gazebo environment to simulate in.
- if everything works well, to try with Rust
- if everything works well try to adapt the Rust controller to the physical linear actuator with raspberry pi
- if everything works try to setup a pipeline where a command is sent to the simulation first and then to the physical actuator.

