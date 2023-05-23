Usage
=====

.. _installation:

Install through apt
-------------------

Here we assume that the unified-planning package is already installed on your machine. Else, see below.
Installation commands:

.. code-block:: console

   echo "deb [trusted=yes] https://raw.githubusercontent.com/aiplan4eu/UP4ROS2/jammy-noetic/ ./" | sudo tee /etc/apt/sources.list.d/aiplan4eu_UP4ROS2.list
   echo "yaml https://raw.githubusercontent.com/aiplan4eu/UP4ROS2/jammy-noetic/local.yaml noetic" | sudo tee /etc/ros/rosdep/sources.list.d/1-aiplan4eu_UP4ROS2.list
   sudo apt update
   sudo apt install ros-noetic-up4ros2

Install from source
-------------------

This package is a `ROS <https://www.ros.org/>`_ package. It has been developed and tested against `ROS Humble <https://docs.ros.org/en/humble/Installation.html>`_.
To use up4ros2, first install its dependencies (we suggest in a `virtual environment <https://docs.python.org/3/library/venv.html>`_):

.. code-block:: console

   (.venv) $ pip install unified-planning 
   (.venv) $ pip instal unified-planning[tamer]
   (.venv) $ pip instal unified-planning[pyperplan]

At this point, you are ready to install the package in your ros2 workspace.

Launching and solving our first planning problem
------------------------------------------------

To launch our freshly installed up4ros node, run the following command:

.. code-block:: console

   ros2 launch up4ros2 up4ros2.launch.py

At this point, the action servers and services are up and can be queried.
