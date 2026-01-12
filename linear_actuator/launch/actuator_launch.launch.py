from launch import LaunchDescription
from launch_ros.actions import Node
from launch.substitutions import Command
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():

    pkg_share = get_package_share_directory('linear_actuator')
    xacro_file = os.path.join(pkg_share, 'urdf', 'linear_actuator.urdf.xacro')
    controller_yaml = os.path.join(pkg_share, 'config', 'controller.yaml')
    rvizConfigPath= os.path.join(pkg_share, 'config/config.rviz')

    return LaunchDescription([

        Node(
            package="controller_manager",
            executable="ros2_control_node",
            parameters=[xacro_file, controller_yaml],
            output="screen"
        ),

        # # Joint State Publisher
        # Node(
        #     package='joint_state_publisher',
        #     executable='joint_state_publisher',
        #     name='joint_state_publisher',
        #     parameters=[{
        #         'robot_description': Command(['xacro ', xacro_file])
        #     }],
        # ),

        Node(
            package='joint_state_publisher_gui',
            executable='joint_state_publisher_gui',
            name='joint_state_publisher_gui',
        ),

        # Robot State Publisher
        Node(
            package='robot_state_publisher',
            executable='robot_state_publisher',
            parameters=[{
                'robot_description': Command(['xacro ', xacro_file])
            }],
            output='screen'
        ),

        # RViz
        Node(
            package='rviz2',
            executable='rviz2',
            name='rviz2',
            output='screen',
            arguments=['-d', rvizConfigPath]
        )
    ])
