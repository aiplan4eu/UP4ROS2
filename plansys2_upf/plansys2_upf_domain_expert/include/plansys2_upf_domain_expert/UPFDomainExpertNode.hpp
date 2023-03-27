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

#ifndef PLANSYS2_UPFDOMAIN_EXPERT__UPFDOMAINEXPERTNODE_HPP_
#define PLANSYS2_UPFDOMAIN_EXPERT__UPFDOMAINEXPERTNODE_HPP_

#include <optional>
#include <memory>

#include "std_msgs/msg/string.hpp"
#include "lifecycle_msgs/msg/state.hpp"
#include "lifecycle_msgs/msg/transition.hpp"
#include "plansys2_msgs/srv/get_domain_types.hpp"
#include "plansys2_msgs/srv/get_domain_actions.hpp"
#include "plansys2_msgs/srv/get_domain_action_details.hpp"
#include "plansys2_msgs/srv/get_domain_durative_action_details.hpp"
#include "plansys2_msgs/srv/get_domain.hpp"
#include "plansys2_msgs/srv/get_node_details.hpp"
#include "plansys2_msgs/srv/get_states.hpp"

#include "rclcpp/rclcpp.hpp"
#include "rclcpp_lifecycle/lifecycle_node.hpp"

namespace plansys2
{

/// UPFDomainExpertNode contains a model, and manages the requests from the UPFDomainExpertClient.
class UPFDomainExpertNode : public rclcpp_lifecycle::LifecycleNode
{
public:
  /// Create a new UPFDomainExpertNode
  UPFDomainExpertNode();

  using CallbackReturnT =
    rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn;

  /// Configures domain by creating a UPFDomainExpert object
  /**
   * \param[in] state LifeCycle Node's state
   * \return Success or Failure
   */
  CallbackReturnT on_configure(const rclcpp_lifecycle::State & state);

  /// Activates the node
  /**
   * \param[in] state LifeCycle Node's state
   * \return Success or Failure
   */
  CallbackReturnT on_activate(const rclcpp_lifecycle::State & state);

  /// Deactivates the node
  /**
   * \param[in] state LifeCycle Node's state
   * \return Success or Failure
   */
  CallbackReturnT on_deactivate(const rclcpp_lifecycle::State & state);

  /// Cleans up the node
  /**
   * \param[in] state LifeCycle Node's state
   * \return Success or Failure
   */
  CallbackReturnT on_cleanup(const rclcpp_lifecycle::State & state);

  /// Shuts down the node
  /**
   * \param[in] state LifeCycle Node's state
   * \return Success or Failure
   */
  CallbackReturnT on_shutdown(const rclcpp_lifecycle::State & state);

  /// Manages the error in the node
  /**
   * \param[in] state LifeCycle Node's state
   * \return Success or Failure
   */
  CallbackReturnT on_error(const rclcpp_lifecycle::State & state);


  /// Receives the result of the GetDomainTypes service call
  /**
   * \param[in] request_header The header of the request
   * \param[in] request The request
   * \param[out] request The response
   */
  void get_domain_types_service_callback(
    const std::shared_ptr<rmw_request_id_t> request_header,
    const std::shared_ptr<plansys2_msgs::srv::GetDomainTypes::Request> request,
    const std::shared_ptr<plansys2_msgs::srv::GetDomainTypes::Response> response);

  /// Receives the result of the GetDomainActions service call
  /**
   * \param[in] request_header The header of the request
   * \param[in] request The request
   * \param[out] request The response
   */
  void get_domain_actions_service_callback(
    const std::shared_ptr<rmw_request_id_t> request_header,
    const std::shared_ptr<plansys2_msgs::srv::GetDomainActions::Request> request,
    const std::shared_ptr<plansys2_msgs::srv::GetDomainActions::Response> response);

  /// Receives the result of the GetDomainActionDetails service call
  /**
   * \param[in] request_header The header of the request
   * \param[in] request The request
   * \param[out] request The response
   */
  void get_domain_action_details_service_callback(
    const std::shared_ptr<rmw_request_id_t> request_header,
    const std::shared_ptr<plansys2_msgs::srv::GetDomainActionDetails::Request> request,
    const std::shared_ptr<plansys2_msgs::srv::GetDomainActionDetails::Response> response);

  /// Receives the result of the GetDomainActions service call
  /**
   * \param[in] request_header The header of the request
   * \param[in] request The request
   * \param[out] request The response
   */
  void get_domain_durative_actions_service_callback(
    const std::shared_ptr<rmw_request_id_t> request_header,
    const std::shared_ptr<plansys2_msgs::srv::GetDomainActions::Request> request,
    const std::shared_ptr<plansys2_msgs::srv::GetDomainActions::Response> response);

  /// Receives the result of the GetDomainDurativeActionDetails service call
  /**
   * \param[in] request_header The header of the request
   * \param[in] request The request
   * \param[out] request The response
   */
  void get_domain_durative_action_details_service_callback(
    const std::shared_ptr<rmw_request_id_t> request_header,
    const std::shared_ptr<plansys2_msgs::srv::GetDomainDurativeActionDetails::Request> request,
    const std::shared_ptr<plansys2_msgs::srv::GetDomainDurativeActionDetails::Response> response);

  /// Receives the result of the GetDomainPredicates service call
  /**
   * \param[in] request_header The header of the request
   * \param[in] request The request
   * \param[out] request The response
   */
  void get_domain_predicates_service_callback(
    const std::shared_ptr<rmw_request_id_t> request_header,
    const std::shared_ptr<plansys2_msgs::srv::GetStates::Request> request,
    const std::shared_ptr<plansys2_msgs::srv::GetStates::Response> response);

  /// Receives the result of the GetNodeDetails service call
  /**
   * \param[in] request_header The header of the request
   * \param[in] request The request
   * \param[out] request The response
   */
  void get_domain_predicate_details_service_callback(
    const std::shared_ptr<rmw_request_id_t> request_header,
    const std::shared_ptr<plansys2_msgs::srv::GetNodeDetails::Request> request,
    const std::shared_ptr<plansys2_msgs::srv::GetNodeDetails::Response> response);

  /// Receives the result of the GetDomainFunctions service call
  /**
   * \param[in] request_header The header of the request
   * \param[in] request The request
   * \param[out] request The response
   */
  void get_domain_functions_service_callback(
    const std::shared_ptr<rmw_request_id_t> request_header,
    const std::shared_ptr<plansys2_msgs::srv::GetStates::Request> request,
    const std::shared_ptr<plansys2_msgs::srv::GetStates::Response> response);

  /// Receives the result of the GetDomainFunctionDetails service call
  /**
   * \param[in] request_header The header of the request
   * \param[in] request The request
   * \param[out] request The response
   */
  void get_domain_function_details_service_callback(
    const std::shared_ptr<rmw_request_id_t> request_header,
    const std::shared_ptr<plansys2_msgs::srv::GetNodeDetails::Request> request,
    const std::shared_ptr<plansys2_msgs::srv::GetNodeDetails::Response> response);

  /// Receives the result of the GetDomain service call
  /**
   * \param[in] request_header The header of the request
   * \param[in] request The request
   * \param[out] request The response
   */
  void get_domain_service_callback(
    const std::shared_ptr<rmw_request_id_t> request_header,
    const std::shared_ptr<plansys2_msgs::srv::GetDomain::Request> request,
    const std::shared_ptr<plansys2_msgs::srv::GetDomain::Response> response);

private:
  rclcpp::Service<plansys2_msgs::srv::GetDomainTypes>::SharedPtr get_types_service_;
  rclcpp::Service<plansys2_msgs::srv::GetDomainActions>::SharedPtr get_domain_actions_service_;
  rclcpp::Service<plansys2_msgs::srv::GetDomainActionDetails>::SharedPtr
    get_domain_action_details_service_;
  rclcpp::Service<plansys2_msgs::srv::GetDomainActions>::SharedPtr
    get_domain_durative_actions_service_;
  rclcpp::Service<plansys2_msgs::srv::GetDomainDurativeActionDetails>::SharedPtr
    get_domain_durative_action_details_service_;
  rclcpp::Service<plansys2_msgs::srv::GetStates>::SharedPtr
    get_domain_predicates_service_;
  rclcpp::Service<plansys2_msgs::srv::GetNodeDetails>::SharedPtr
    get_domain_predicate_details_service_;
  rclcpp::Service<plansys2_msgs::srv::GetStates>::SharedPtr
    get_domain_functions_service_;
  rclcpp::Service<plansys2_msgs::srv::GetNodeDetails>::SharedPtr
    get_domain_function_details_service_;
  rclcpp::Service<plansys2_msgs::srv::GetDomain>::SharedPtr get_domain_service_;
};

}  // namespace plansys2

#endif  // PLANSYS2_UPFDOMAIN_EXPERT__UPFDOMAINEXPERTNODE_HPP_
