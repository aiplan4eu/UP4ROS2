// Copyright 2019 Intelligent Robotics Lab
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "plansys2_upf_domain_expert/UPFDomainExpertNode.hpp"

#include <string>
#include <memory>
#include <vector>

#include "plansys2_core/Utils.hpp"

#include "lifecycle_msgs/msg/state.hpp"

namespace plansys2
{

UPFDomainExpertNode::UPFDomainExpertNode()
: rclcpp_lifecycle::LifecycleNode("upf_domain_expert")
{
  declare_parameter("model_file", "");

  get_types_service_ = create_service<plansys2_msgs::srv::GetDomainTypes>(
    "upf_domain_expert/get_domain_types",
    std::bind(
      &UPFDomainExpertNode::get_domain_types_service_callback,
      this, std::placeholders::_1, std::placeholders::_2,
      std::placeholders::_3));
  get_domain_actions_service_ = create_service<plansys2_msgs::srv::GetDomainActions>(
    "upf_domain_expert/get_domain_actions",
    std::bind(
      &UPFDomainExpertNode::get_domain_actions_service_callback,
      this, std::placeholders::_1, std::placeholders::_2,
      std::placeholders::_3));
  get_domain_action_details_service_ =
    create_service<plansys2_msgs::srv::GetDomainActionDetails>(
    "upf_domain_expert/get_domain_action_details", std::bind(
      &UPFDomainExpertNode::get_domain_action_details_service_callback,
      this, std::placeholders::_1, std::placeholders::_2,
      std::placeholders::_3));
  get_domain_durative_actions_service_ = create_service<plansys2_msgs::srv::GetDomainActions>(
    "upf_domain_expert/get_domain_durative_actions",
    std::bind(
      &UPFDomainExpertNode::get_domain_durative_actions_service_callback,
      this, std::placeholders::_1, std::placeholders::_2,
      std::placeholders::_3));
  get_domain_durative_action_details_service_ =
    create_service<plansys2_msgs::srv::GetDomainDurativeActionDetails>(
    "upf_domain_expert/get_domain_durative_action_details", std::bind(
      &UPFDomainExpertNode::get_domain_durative_action_details_service_callback,
      this, std::placeholders::_1, std::placeholders::_2,
      std::placeholders::_3));
  get_domain_predicates_service_ = create_service<plansys2_msgs::srv::GetStates>(
    "upf_domain_expert/get_domain_predicates", std::bind(
      &UPFDomainExpertNode::get_domain_predicates_service_callback,
      this, std::placeholders::_1, std::placeholders::_2,
      std::placeholders::_3));
  get_domain_predicate_details_service_ =
    create_service<plansys2_msgs::srv::GetNodeDetails>(
    "upf_domain_expert/get_domain_predicate_details", std::bind(
      &UPFDomainExpertNode::get_domain_predicate_details_service_callback,
      this, std::placeholders::_1, std::placeholders::_2,
      std::placeholders::_3));
  get_domain_functions_service_ = create_service<plansys2_msgs::srv::GetStates>(
    "upf_domain_expert/get_domain_functions", std::bind(
      &UPFDomainExpertNode::get_domain_functions_service_callback,
      this, std::placeholders::_1, std::placeholders::_2,
      std::placeholders::_3));
  get_domain_function_details_service_ =
    create_service<plansys2_msgs::srv::GetNodeDetails>(
    "upf_domain_expert/get_domain_function_details", std::bind(
      &UPFDomainExpertNode::get_domain_function_details_service_callback,
      this, std::placeholders::_1, std::placeholders::_2,
      std::placeholders::_3));
  get_domain_service_ = create_service<plansys2_msgs::srv::GetDomain>(
    "upf_domain_expert/get_domain", std::bind(
      &UPFDomainExpertNode::get_domain_service_callback,
      this, std::placeholders::_1, std::placeholders::_2,
      std::placeholders::_3));
}


using CallbackReturnT =
  rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn;

CallbackReturnT
UPFDomainExpertNode::on_configure(const rclcpp_lifecycle::State & state)
{
  RCLCPP_INFO(get_logger(), "[%s] Configuring...", get_name());
  std::string model_file = get_parameter("model_file").get_value<std::string>();

  // ToDo: Send model to UPF

  RCLCPP_INFO(get_logger(), "[%s] Configured", get_name());
  return CallbackReturnT::SUCCESS;
}

CallbackReturnT
UPFDomainExpertNode::on_activate(const rclcpp_lifecycle::State & state)
{
  RCLCPP_INFO(get_logger(), "[%s] Activating...", get_name());
  RCLCPP_INFO(get_logger(), "[%s] Activated", get_name());

  return CallbackReturnT::SUCCESS;
}

CallbackReturnT
UPFDomainExpertNode::on_deactivate(const rclcpp_lifecycle::State & state)
{
  RCLCPP_INFO(get_logger(), "[%s] Deactivating...", get_name());
  RCLCPP_INFO(get_logger(), "[%s] Deactivated", get_name());

  return CallbackReturnT::SUCCESS;
}

CallbackReturnT
UPFDomainExpertNode::on_cleanup(const rclcpp_lifecycle::State & state)
{
  RCLCPP_INFO(get_logger(), "[%s] Cleaning up...", get_name());
  RCLCPP_INFO(get_logger(), "[%s] Cleaned up", get_name());

  return CallbackReturnT::SUCCESS;
}

CallbackReturnT
UPFDomainExpertNode::on_shutdown(const rclcpp_lifecycle::State & state)
{
  RCLCPP_INFO(get_logger(), "[%s] Shutting down...", get_name());
  RCLCPP_INFO(get_logger(), "[%s] Shutted down", get_name());

  return CallbackReturnT::SUCCESS;
}

CallbackReturnT
UPFDomainExpertNode::on_error(const rclcpp_lifecycle::State & state)
{
  RCLCPP_ERROR(get_logger(), "[%s] Error transition", get_name());

  return CallbackReturnT::SUCCESS;
}

void
UPFDomainExpertNode::get_domain_types_service_callback(
  const std::shared_ptr<rmw_request_id_t> request_header,
  const std::shared_ptr<plansys2_msgs::srv::GetDomainTypes::Request> request,
  const std::shared_ptr<plansys2_msgs::srv::GetDomainTypes::Response> response)
{
  if (upf_domain_expert_ == nullptr) {
    response->success = false;
    response->error_info = "Requesting service in non-active state";
    RCLCPP_WARN(get_logger(), "Requesting service in non-active state");
  } else {
    response->success = false;
    response->error_info = "Unable to get domain types from UPF4ROS2";
  }
}

void
UPFDomainExpertNode::get_domain_actions_service_callback(
  const std::shared_ptr<rmw_request_id_t> request_header,
  const std::shared_ptr<plansys2_msgs::srv::GetDomainActions::Request> request,
  const std::shared_ptr<plansys2_msgs::srv::GetDomainActions::Response> response)
{
  if (upf_domain_expert_ == nullptr) {
    response->success = false;
    response->error_info = "Requesting service in non-active state";
    RCLCPP_WARN(get_logger(), "Requesting service in non-active state");
  } else {
    response->success = true;
    for (const auto & action : upf_domain_expert_->getActions()) {
      response->actions.push_back(action);
    }
  }
}

void
UPFDomainExpertNode::get_domain_action_details_service_callback(
  const std::shared_ptr<rmw_request_id_t> request_header,
  const std::shared_ptr<plansys2_msgs::srv::GetDomainActionDetails::Request> request,
  const std::shared_ptr<plansys2_msgs::srv::GetDomainActionDetails::Response> response)
{
  if (upf_domain_expert_ == nullptr) {
    response->success = false;
    response->error_info = "Requesting service in non-active state";

    RCLCPP_WARN(get_logger(), "Requesting service in non-active state");
  } else {
    auto action = upf_domain_expert_->getAction(request->action, request->parameters);

    if (action) {
      response->action = *action;
      response->success = true;
    } else {
      RCLCPP_WARN(get_logger(), "Requesting a non-existing action [%s]", request->action.c_str());
      response->success = false;
      response->error_info = "Action not found";
    }
  }
}

void
UPFDomainExpertNode::get_domain_durative_actions_service_callback(
  const std::shared_ptr<rmw_request_id_t> request_header,
  const std::shared_ptr<plansys2_msgs::srv::GetDomainActions::Request> request,
  const std::shared_ptr<plansys2_msgs::srv::GetDomainActions::Response> response)
{
  if (upf_domain_expert_ == nullptr) {
    response->success = false;
    response->error_info = "Requesting service in non-active state";
    RCLCPP_WARN(get_logger(), "Requesting service in non-active state");
  } else {
    response->success = true;
    for (const auto & action : upf_domain_expert_->getDurativeActions()) {
      response->actions.push_back(action);
    }
  }
}

void
UPFDomainExpertNode::get_domain_durative_action_details_service_callback(
  const std::shared_ptr<rmw_request_id_t> request_header,
  const std::shared_ptr<plansys2_msgs::srv::GetDomainDurativeActionDetails::Request> request,
  const std::shared_ptr<plansys2_msgs::srv::GetDomainDurativeActionDetails::Response> response)
{
  if (upf_domain_expert_ == nullptr) {
    response->success = false;
    response->error_info = "Requesting service in non-active state";

    RCLCPP_WARN(get_logger(), "Requesting service in non-active state");
  } else {
    auto action = upf_domain_expert_->getDurativeAction(request->durative_action, request->parameters);

    if (action) {
      response->durative_action = *action;
      response->success = true;
    } else {
      RCLCPP_WARN(
        get_logger(), "Requesting a non-existing durative action [%s]",
        request->durative_action.c_str());
      response->success = false;
      response->error_info = "Durative action not found";
    }
  }
}

void
UPFDomainExpertNode::get_domain_predicates_service_callback(
  const std::shared_ptr<rmw_request_id_t> request_header,
  const std::shared_ptr<plansys2_msgs::srv::GetStates::Request> request,
  const std::shared_ptr<plansys2_msgs::srv::GetStates::Response> response)
{
  if (upf_domain_expert_ == nullptr) {
    response->success = false;
    response->error_info = "Requesting service in non-active state";
    RCLCPP_WARN(get_logger(), "Requesting service in non-active state");
  } else {
    response->success = true;
    response->states = plansys2::convertVector<plansys2_msgs::msg::Node, plansys2::Predicate>(
      upf_domain_expert_->getPredicates());
  }
}

void
UPFDomainExpertNode::get_domain_predicate_details_service_callback(
  const std::shared_ptr<rmw_request_id_t> request_header,
  const std::shared_ptr<plansys2_msgs::srv::GetNodeDetails::Request> request,
  const std::shared_ptr<plansys2_msgs::srv::GetNodeDetails::Response> response)
{
  if (upf_domain_expert_ == nullptr) {
    response->success = false;
    response->error_info = "Requesting service in non-active state";
    RCLCPP_WARN(get_logger(), "Requesting service in non-active state");
  } else {
    auto predicate = upf_domain_expert_->getPredicate(request->expression);
    if (predicate) {
      response->node = predicate.value();
      response->success = true;
    } else {
      RCLCPP_WARN(
        get_logger(), "Requesting a non-existing predicate [%s]",
        request->expression);
      response->success = false;
      response->error_info = "Predicate not found";
    }
  }
}

void
UPFDomainExpertNode::get_domain_functions_service_callback(
  const std::shared_ptr<rmw_request_id_t> request_header,
  const std::shared_ptr<plansys2_msgs::srv::GetStates::Request> request,
  const std::shared_ptr<plansys2_msgs::srv::GetStates::Response> response)
{
  if (upf_domain_expert_ == nullptr) {
    response->success = false;
    response->error_info = "Requesting service in non-active state";
    RCLCPP_WARN(get_logger(), "Requesting service in non-active state");
  } else {
    response->success = true;
    response->states = plansys2::convertVector<plansys2_msgs::msg::Node, plansys2::Function>(
      upf_domain_expert_->getFunctions());
  }
}

void
UPFDomainExpertNode::get_domain_function_details_service_callback(
  const std::shared_ptr<rmw_request_id_t> request_header,
  const std::shared_ptr<plansys2_msgs::srv::GetNodeDetails::Request> request,
  const std::shared_ptr<plansys2_msgs::srv::GetNodeDetails::Response> response)
{
  if (upf_domain_expert_ == nullptr) {
    response->success = false;
    response->error_info = "Requesting service in non-active state";
    RCLCPP_WARN(get_logger(), "Requesting service in non-active state");
  } else {
    auto function = upf_domain_expert_->getFunction(request->expression);
    if (function) {
      response->node = function.value();
      response->success = true;
    } else {
      RCLCPP_WARN(
        get_logger(), "Requesting a non-existing function [%s]",
        request->expression);
      response->success = false;
      response->error_info = "Function not found";
    }
  }
}

void
UPFDomainExpertNode::get_domain_service_callback(
  const std::shared_ptr<rmw_request_id_t> request_header,
  const std::shared_ptr<plansys2_msgs::srv::GetDomain::Request> request,
  const std::shared_ptr<plansys2_msgs::srv::GetDomain::Response> response)
{
  if (upf_domain_expert_ == nullptr) {
    response->success = false;
    response->error_info = "Requesting service in non-active state";
    RCLCPP_WARN(get_logger(), "Requesting service in non-active state");
  } else {
    response->success = true;

    std::ostringstream stream;
    stream << upf_domain_expert_->getDomain();
    response->domain = stream.str();
  }
}


}  // namespace plansys2
