![master](https://github.com/aiplan4eu/UP4ROS2/actions/workflows/master.yaml/badge.svg)
![devel](https://github.com/aiplan4eu/UP4ROS2/actions/workflows/devel.yaml/badge.svg)
[![codecov](https://codecov.io/github/aiplan4eu/UP4ROS2/branch/master/graph/badge.svg?token=W9RX14LTPS)](https://codecov.io/github/aiplan4eu/UP4ROS2)
[![Documentation Status](https://readthedocs.org/projects/up4ros2/badge/?version=latest)](https://up4ros2.readthedocs.io/en/latest/)

# UP4ROS2

This repository contains a ROS 2 wrapper for the AIPlan4EU Unified Planning library available at https://github.com/aiplan4eu/unified-planning.

## Documentation

The documentation is available [here](https://up4ros2.readthedocs.io/en/latest/)

## Quick Overview

The **up4ros** node wraps the unified planning library.
  * It can be launched with: `ros2 launch up4ros2 up4ros2.launch.py`

  * Exposed services:
    * `/up4ros2/add_action` `[up_msgs/srv/AddAction]` 
    * `/up4ros2/add_fluent` `[up_msgs/srv/AddFluent]` 
    * `/up4ros2/add_goal` `[up_msgs/srv/AddGoal]` 
    * `/up4ros2/add_object` `[up_msgs/srv/AddObject]` 
    * `/up4ros2/new_problem` `[up_msgs/srv/NewProblem]` 
    * `/up4ros2/set_initial_value` `[up_msgs/srv/SetInitialValue]` 
    * `/up4ros2/set_problem` `[up_msgs/srv/SetProblem]`
  * Exposed actions:
    * `/up4ros2/planOneShotPDDL` `[up_msgs/action/PDDLPlanOneShot]` 
    * `/up4ros2/planOneShot` `[up_msgs/action/PlanOneShot]` 
    * `/up4ros2/planOneShotRemote` `[up_msgs/action/PlanOneShotRemote]` 

## Acknowledgments

<img src="https://www.aiplan4eu-project.eu/wp-content/uploads/2021/07/euflag.png" width="60" height="40">

This library is being developed for the AIPlan4EU H2020 project (https://aiplan4eu-project.eu) that is funded by the European Commission under grant agreement number 101016442.
