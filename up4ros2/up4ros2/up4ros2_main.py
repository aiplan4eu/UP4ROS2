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

import tempfile

import rclpy
from rclpy.action import ActionServer
from rclpy.node import Node

from unified_planning import model
from unified_planning.io.pddl_reader import PDDLReader
from unified_planning.shortcuts import OneshotPlanner

from up4ros2.ros2_interface_reader import ROS2InterfaceReader
from up4ros2.ros2_interface_writer import ROS2InterfaceWriter

from up_msgs.action import PDDLPlanOneShot, PlanOneShot, PlanOneShotRemote

from up_msgs.msg import PDDLPlanRequest

from up_msgs.srv import (
    AddAction,
    AddFluent,
    AddGoal,
    AddObject,
    GetProblem,
    NewProblem,
    SetInitialValue,
    SetProblem,
)

from up_msgs.srv import PDDLPlanOneShot as PDDLPlanOneShotSrv


class UP4ROS2Node(Node):
    def __init__(self):
        super().__init__("up4ros2")

        self.problems = {}

        self._ros2_interface_writer = ROS2InterfaceWriter()
        self._ros2_interface_reader = ROS2InterfaceReader()
        self._pddl_plan_one_shot_server = ActionServer(
            self,
            PDDLPlanOneShot,
            "up4ros2/action/planOneShotPDDL",
            self.pddl_plan_one_shot_callback,
        )

        self._plan_one_shot_server = ActionServer(
            self,
            PlanOneShot,
            "up4ros2/action/planOneShot",
            self.plan_one_shot_callback,
        )

        self._plan_one_shot_remote_server = ActionServer(
            self,
            PlanOneShotRemote,
            "up4ros2/action/planOneShotRemote",
            self.plan_one_shot_remote_callback,
        )

        self._get_problem = self.create_service(
            GetProblem, "up4ros2/srv/get_problem", self.get_problem
        )
        self._new_problem = self.create_service(
            NewProblem, "up4ros2/srv/new_problem", self.new_problem
        )
        self._set_problem = self.create_service(
            SetProblem, "up4ros2/srv/set_problem", self.set_problem
        )
        self._add_fluent = self.create_service(
            AddFluent, "up4ros2/srv/add_fluent", self.add_fluent
        )
        self._add_action = self.create_service(
            AddAction, "up4ros2/srv/add_action", self.add_action
        )
        self._add_object = self.create_service(
            AddObject, "up4ros2/srv/add_object", self.add_object
        )
        self._set_initial_value = self.create_service(
            SetInitialValue, "up4ros2/srv/set_initial_value", self.set_initial_value
        )
        self._add_goal = self.create_service(
            AddGoal, "up4ros2/srv/add_goal", self.add_goal
        )
        self._pddl_plan_one_shot_srv = self.create_service(
            PDDLPlanOneShotSrv, "up4ros2/srv/planOneShotPDDL", self.pddl_plan_one_shot
        )

    def get_problem(self, request, response):
        if request.problem_name not in self.problems:
            response.success = False
            response.message = f"Problem {request.problem_name} does not exist"
        else:
            response.problem = self._ros2_interface_writer.convert(
                self.problems[request.problem_name]
            )
            response.success = True
        return response

    def new_problem(self, request, response):
        if request.problem_name in self.problems:
            response.success = False
            response.message = f"Problem {request.problem_name} already exists"
        else:
            self.problems[request.problem_name] = model.Problem(request.problem_name)
            response.success = True
        return response

    def set_problem(self, request, response):
        if request.problem_name in self.problems:
            response.success = False
            response.message = f"Problem {request.problem_name} already exists"
        else:
            self.problems[request.problem_name] = self._ros2_interface_reader.convert(
                request.problem
            )
            response.success = True
        return response

    def add_fluent(self, request, response):
        if request.problem_name not in self.problems:
            response.success = False
            response.message = f"Problem {request.problem_name} does not exist"
        else:
            problem = self.problems[request.problem_name]

            fluent = self._ros2_interface_reader.convert(request.fluent, problem)
            value = self._ros2_interface_reader.convert(request.default_value, problem)
            problem.add_fluent(fluent, default_initial_value=value)
            response.success = True
        return response

    def add_action(self, request, response):
        if request.problem_name not in self.problems:
            response.success = False
            response.message = f"Problem {request.problem_name} does not exist"
        else:
            problem = self.problems[request.problem_name]

            action = self._ros2_interface_reader.convert(request.action, problem)
            problem.add_action(action)
            response.success = True
        return response

    def add_object(self, request, response):
        if request.problem_name not in self.problems:
            response.success = False
            response.message = f"Problem {request.problem_name} does not exist"
        else:
            problem = self.problems[request.problem_name]

            action = self._ros2_interface_reader.convert(request.object, problem)
            problem.add_object(action)
            response.success = True

        return response

    def set_initial_value(self, request, response):
        if request.problem_name not in self.problems:
            response.success = False
            response.message = f"Problem {request.problem_name} does not exist"
        else:
            problem = self.problems[request.problem_name]

            expression = self._ros2_interface_reader.convert(
                request.expression, problem
            )
            value = self._ros2_interface_reader.convert(request.value, problem)
            problem.set_initial_value(expression, value)
            response.success = True
        return response

    def add_goal(self, request, response):
        if request.problem_name not in self.problems:
            response.success = False
            response.message = f"Problem {request.problem_name} does not exist"
        else:
            problem = self.problems[request.problem_name]

            if len(request.goal) > 0:
                goal = self._ros2_interface_reader.convert(
                    request.goal[0].goal, problem
                )
                problem.add_goal(goal)
                response.success = True
            elif len(request.goal_with_cost) > 0:
                goal = self._ros2_interface_reader.convert(
                    request.goal_with_cost[0].goal, problem
                )
                problem.add_goal(goal)
                response.success = True
            else:
                response.success = False
                response.message = "Goal is void"
        return response

    def pddl_plan_one_shot(self, request, response):
        domain_file = ""
        problem_file = ""

        if request.plan_request.mode == PDDLPlanRequest.RAW:
            domain_file = tempfile.NamedTemporaryFile()
            problem_file = tempfile.NamedTemporaryFile()

            with open(domain_file, "w") as pddl_writer:
                pddl_writer.write(request.plan_request.domain)
            with open(problem_file, "w") as pddl_writer:
                pddl_writer.write(request.plan_request.problem)
        else:
            domain_file = request.plan_request.domain
            problem_file = request.plan_request.problem

        reader = PDDLReader()

        try:
            upf_problem = reader.parse_problem(domain_file, problem_file)
        except Exception:
            response.success = False
            response.message = "Error parsing problem"
            return response

        with OneshotPlanner(problem_kind=upf_problem.kind) as planner:
            result = planner.solve(upf_problem)
            print("%s returned: %s" % (planner.name, result.plan))

            if result.plan is not None:
                response.plan_result = self._ros2_interface_writer.convert(result)
                response.success = True
                response.message = ""
            else:
                response.success = False
                response.message = "No plan found"

            return response

    def pddl_plan_one_shot_callback(self, goal_handle):
        domain_file = ""
        problem_file = ""

        if goal_handle.request.plan_request.mode == PDDLPlanRequest.RAW:
            domain_file = tempfile.NamedTemporaryFile()
            problem_file = tempfile.NamedTemporaryFile()

            with open(domain_file, "w") as pddl_writer:
                pddl_writer.write(goal_handle.request.plan_request.domain)
            with open(problem_file, "w") as pddl_writer:
                pddl_writer.write(goal_handle.request.plan_request.problem)
        else:
            domain_file = goal_handle.request.plan_request.domain
            problem_file = goal_handle.request.plan_request.problem

        reader = PDDLReader()
        upf_problem = reader.parse_problem(domain_file, problem_file)

        with OneshotPlanner(problem_kind=upf_problem.kind) as planner:
            result = planner.solve(upf_problem)
            print("%s returned: %s" % (planner.name, result.plan))

            feedback_msg = PDDLPlanOneShot.Feedback()
            feedback_msg.plan_result = self._ros2_interface_writer.convert(result)

            goal_handle.publish_feedback(feedback_msg)
            goal_handle.succeed()

            result = PDDLPlanOneShot.Result()
            result.success = True
            result.message = ""
            return result

    def plan_one_shot_callback(self, goal_handle):
        upf_problem = self._ros2_interface_reader.convert(
            goal_handle.request.plan_request.problem
        )

        with OneshotPlanner(problem_kind=upf_problem.kind) as planner:
            result = planner.solve(upf_problem)
            print("%s returned: %s" % (planner.name, result.plan))

            feedback_msg = PlanOneShot.Feedback()
            feedback_msg.plan_result = self._ros2_interface_writer.convert(result)

            goal_handle.publish_feedback(feedback_msg)
            goal_handle.succeed()

            result = PlanOneShot.Result()
            result.success = True
            result.message = ""
            return result

    def plan_one_shot_remote_callback(self, goal_handle):
        up_problem = self.problems.get(goal_handle.request.plan_request.problem)

        if up_problem is None:
            result = PlanOneShotRemote.Result()

            result.success = False
            result.message = (
                f"Problem {goal_handle.request.plan_request.problem} does not exist"
            )
            goal_handle.succeed()
            return result

        with OneshotPlanner(problem_kind=up_problem.kind) as planner:
            result = planner.solve(up_problem)
            print("%s returned: %s" % (planner.name, result.plan))

            feedback_msg = PlanOneShotRemote.Feedback()
            feedback_msg.plan_result = self._ros_interface_writer.convert(result)

            goal_handle.publish_feedback(feedback_msg)

            result = PlanOneShotRemote.Result()
            result.success = True
            result.message = ""
            goal_handle.succeed()
            return result


def main(args=None):
    rclpy.init(args=args)

    up4ros2_node = UP4ROS2Node()

    rclpy.spin(up4ros2_node)

    up4ros2_node.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    main()
