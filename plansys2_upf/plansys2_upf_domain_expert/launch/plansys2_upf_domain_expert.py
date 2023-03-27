# Copyright 2019 Intelligent Robotics Lab
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, SetEnvironmentVariable
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    # Create the launch configuration variables
    model_file = LaunchConfiguration('model_file')
    namespace = LaunchConfiguration('namespace')
    params_file = LaunchConfiguration('params_file')

    stdout_linebuf_envvar = SetEnvironmentVariable(
        'RCUTILS_CONSOLE_STDOUT_LINE_BUFFERED', '1')

    declare_model_file_cmd = DeclareLaunchArgument(
        'model_file',
        default_value='src/ros2_planning_system/'
        'plansys2_upf_domain_expert/test/pddl/domain_simple.pddl',
        description='PDDL Model file')

    declare_namespace_cmd = DeclareLaunchArgument(
        'namespace',
        default_value='',
        description='Namespace')

    # Specify the actions
    upf_domain_expert_cmd = Node(
        package='plansys2_upf_domain_expert',
        node_executable='upf_domain_expert_node',
        node_name='upf_domain_expert',
        namespace=namespace,
        output='screen',
        parameters=[
          {'model_file': model_file}, params_file])

    # Create the launch description and populate
    ld = LaunchDescription()

    # Set environment variables
    ld.add_action(stdout_linebuf_envvar)
    ld.add_action(declare_model_file_cmd)
    ld.add_action(declare_namespace_cmd)

    # Declare the launch options
    ld.add_action(upf_domain_expert_cmd)

    return ld
