```bash
echo "deb [trusted=yes] https://github.com/aiplan4eu/UP4ROS2/raw/jammy-rolling/ ./" | sudo tee /etc/apt/sources.list.d/aiplan4eu_UP4ROS2.list
echo "yaml https://github.com/aiplan4eu/UP4ROS2/raw/jammy-rolling/local.yaml rolling" | sudo tee /etc/ros/rosdep/sources.list.d/1-aiplan4eu_UP4ROS2.list
```
