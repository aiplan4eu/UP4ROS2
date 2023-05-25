# Copyright 2023 Magazino GmbH
# Copyright 2022 Intelligent Robotics Lab
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

from glob import glob
import os

from setuptools import setup

package_name = "up4ros2"

setup(
    name=package_name,
    version="0.0.0",
    packages=[package_name],
    data_files=[
        ("share/ament_index/resource_index/packages", ["resource/" + package_name]),
        ("share/" + package_name, ["package.xml"]),
        (os.path.join("share", package_name, "launch"), glob("launch/*.launch.py")),
        (os.path.join("share", package_name, "pddl"), glob("tests/pddl/*")),
    ],
    install_requires=["setuptools"],
    zip_safe=True,
    maintainer="guglielmo gemignani",
    maintainer_email="gemignani@magazino.eu",
    description="ROS 2 Support for UPF",
    license="Apache License, Version 2.0",
    tests_require=["pytest"],
    entry_points={
        "console_scripts": ["up4ros2_main = up4ros2.up4ros2_main:main"],
    },
)
