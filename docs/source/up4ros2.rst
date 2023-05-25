The up4ros Node
===============

.. _up4ros:


The main component of this repository is the up4ros2 `ROS <https://www.ros.org/>`_ package. 
This node is a ROS 2 wrapper for the AIPlan4EU Unified Planning library available 
at `this link <https://github.com/aiplan4eu/unified-planning>`_ and exposes the following actions and services:

Actions
-------


PDDLPlanOneShotAction
^^^^^^^^^^^^^^^^^^^^^
This action takes in input a pddl problem and domain and tries to use one of the registered planners to produce a solution in the feedback. 
The result will tell us if the planner managed or not to find a solution.

**Goal type:** up_msgs.msg.PlanRequest

.. code-block:: console

    up_msgs/Problem problem

    uint8 SATISFIABLE=0
    uint8 SOLVED_OPTIMALLY=1
    uint8 resolution_mode

    # Max allowed runtime time in seconds.
    float64 timeout

    # Engine specific options to be passed to the engine
    string engine_option_names
    string engine_option_values

where a problem is defined as:

.. code-block:: console

    string domain_name
    string problem_name
    up_msgs/TypeDeclaration[] types
    up_msgs/Fluent[] fluents
    up_msgs/ObjectDeclaration[] objects

    # List of actions in the domain.
    up_msgs/Action[] actions

    # Initial state, including default values of state variables.
    up_msgs/Assignment[] initial_state

    # Facts and effects that are expected to occur strictly later than the initial state.
    # features: TIMED_EFFECT
    up_msgs/TimedEffect[] timed_effects

    # Goals of the planning problem.
    up_msgs/Goal[] goals

    # The plan quality metrics
    up_msgs/Metric[] metrics


    # If the problem is hierarchical, defines the tasks and methods as well as the initial task network.
    # features: hierarchical
    up_msgs/Hierarchy[] hierarchy

    # all features of the problem
    uint8[] features

    ## Features of the problem.
    ## Features are essential in that not supporting a feature `X` should allow disregarding any field tagged with `features: [X]`.

    # PROBLEM_CLASS
    uint8 ACTION_BASED=0
    uint8 HIERARCHICAL=26
    # PROBLEM_TYPE
    uint8 SIMPLE_NUMERIC_PLANNING=30
    uint8 GENERAL_NUMERIC_PLANNING=31
    # TIME
    uint8 CONTINUOUS_TIME=1
    uint8 DISCRETE_TIME=2
    uint8 INTERMEDIATE_CONDITIONS_AND_EFFECTS=3
    uint8 TIMED_EFFECT=4
    uint8 TIMED_GOALS=5
    uint8 DURATION_INEQUALITIES=6
    # EXPRESSION_DURATION
    uint8 STATIC_FLUENTS_IN_DURATIONS=27
    uint8 FLUENTS_IN_DURATIONS=28
    # NUMBERS
    uint8 CONTINUOUS_NUMBERS=7
    uint8 DISCRETE_NUMBERS=8
    uint8 BOUNDED_TYPES=38
    # CONDITIONS_KIND
    uint8 NEGATIVE_CONDITIONS=9
    uint8 DISJUNCTIVE_CONDITIONS=10
    uint8 EQUALITIES=11
    uint8 EXISTENTIAL_CONDITIONS=12
    uint8 UNIVERSAL_CONDITIONS=13
    # EFFECTS_KIND
    uint8 CONDITIONAL_EFFECTS=14
    uint8 INCREASE_EFFECTS=15
    uint8 DECREASE_EFFECTS=16
    uint8 STATIC_FLUENTS_IN_BOOLEAN_ASSIGNMENTS=41
    uint8 STATIC_FLUENTS_IN_NUMERIC_ASSIGNMENTS=42
    uint8 FLUENTS_IN_BOOLEAN_ASSIGNMENTS=43
    uint8 FLUENTS_IN_NUMERIC_ASSIGNMENTS=44
    # TYPING
    uint8 FLAT_TYPING=17
    uint8 HIERARCHICAL_TYPING=18
    # FLUENTS_TYPE
    uint8 NUMERIC_FLUENTS=19
    uint8 OBJECT_FLUENTS=20
    # QUALITY_METRICS
    uint8 ACTIONS_COST=21
    uint8 FINAL_VALUE=22
    uint8 MAKESPAN=23
    uint8 PLAN_LENGTH=24
    uint8 OVERSUBSCRIPTION=29
    # ACTION_COST_KIND
    uint8 STATIC_FLUENTS_IN_ACTIONS_COST=45
    uint8 FLUENTS_IN_ACTIONS_COST=46
    # SIMULATED_ENTITIES
    uint8 SIMULATED_EFFECTS=25


**feedback type:** up_msgs.msg.PlanGenerationResult

.. code-block:: console

    ## Message sent by engine.
    ## Contains the engine exit status as well as the best plan found if any.

    # ==== Engine stopped normally ======

    # Valid plan found
    # The `plan` field must be set.
    uint8 SOLVED_SATISFICING=0
    # Plan found with optimality guarantee
    # The `plan` field must be set and contains an optimal solution.
    uint8 SOLVED_OPTIMALLY=1
    # No plan exists
    uint8 UNSOLVABLE_PROVEN=2
    # The engine was not able to find a solution but does not give any guarantee that none exist
    # (i.e. the engine might not be complete)
    uint8 UNSOLVABLE_INCOMPLETELY=3

    # ====== Engine exited before making any conclusion ====
    # Search stopped before concluding SOLVED_OPTIMALLY or UNSOLVABLE_PROVEN
    # If a plan was found, it might be reported in the `plan` field

    # The engine ran out of time
    uint8 TIMEOUT=13
    # The engine ran out of memory
    uint8 MEMOUT=14
    # The engine faced an internal error.
    uint8 INTERNAL_ERROR=15
    # The problem submitted is not supported by the engine.
    uint8 UNSUPPORTED_PROBLEM=16

    # ====== Intermediate answer ======
    # This Answer is an Intermediate Answer and not a Final one
    uint8 INTERMEDIATE=17

    uint8 status

    # Optional. Best plan found if any.
    up_msgs/Plan plan

    # A set of engine specific values that can be reported, for instance
    # - "grounding-time": "10ms"
    # - "expanded-states": "1290"
    string[] metric_names
    string[] metric_values

    # Optional log messages about the engine's activity.
    # Note that it should not be expected that logging messages are visible to the end user.
    # If used in conjunction with INTERNAL_ERROR or UNSUPPORTED_PROBLEM, it would be expected to have at least one log message at the ERROR level.
    up_msgs/LogMessage[] log_messages

    # Synthetic description of the engine that generated this message.
    string engine_name

**result type:** up_msgs.msg.PDDLPlanOneShotResult

.. code-block:: console

    bool success
    string message

PlanOneShotAction
^^^^^^^^^^^^^^^^^

This action takes in input a problem and domain formulated as ROS messages and tries to use one of the registered planners to produce a solution in the feedback. 
The result will tell us if the planner managed or not to find a solution.

**Goal type:** up_msgs.msg.PlanRequest

.. code-block:: console

    # Problem that should be solved.

    # Specify if the domain/model string contains a file path, or the content
    uint8 FILE=0
    uint8 RAW=1
    uint8 mode

    string domain
    string problem

    uint8 SATISFIABLE=0
    uint8 SOLVED_OPTIMALLY=1
    uint8 resolution_mode

    # Max allowed runtime time in seconds.
    float64 timeout

    # Engine specific options to be passed to the engine
    string engine_option_names
    string engine_option_values

**feedback type:** up_msgs.msg.PlanGenerationResult

.. code-block:: console

    ## Message sent by engine.
    ## Contains the engine exit status as well as the best plan found if any.

    # ==== Engine stopped normally ======

    # Valid plan found
    # The `plan` field must be set.
    uint8 SOLVED_SATISFICING=0
    # Plan found with optimality guarantee
    # The `plan` field must be set and contains an optimal solution.
    uint8 SOLVED_OPTIMALLY=1
    # No plan exists
    uint8 UNSOLVABLE_PROVEN=2
    # The engine was not able to find a solution but does not give any guarantee that none exist
    # (i.e. the engine might not be complete)
    uint8 UNSOLVABLE_INCOMPLETELY=3

    # ====== Engine exited before making any conclusion ====
    # Search stopped before concluding SOLVED_OPTIMALLY or UNSOLVABLE_PROVEN
    # If a plan was found, it might be reported in the `plan` field

    # The engine ran out of time
    uint8 TIMEOUT=13
    # The engine ran out of memory
    uint8 MEMOUT=14
    # The engine faced an internal error.
    uint8 INTERNAL_ERROR=15
    # The problem submitted is not supported by the engine.
    uint8 UNSUPPORTED_PROBLEM=16

    # ====== Intermediate answer ======
    # This Answer is an Intermediate Answer and not a Final one
    uint8 INTERMEDIATE=17

    uint8 status

    # Optional. Best plan found if any.
    up_msgs/Plan plan

    # A set of engine specific values that can be reported, for instance
    # - "grounding-time": "10ms"
    # - "expanded-states": "1290"
    string[] metric_names
    string[] metric_values

    # Optional log messages about the engine's activity.
    # Note that it should not be expected that logging messages are visible to the end user.
    # If used in conjunction with INTERNAL_ERROR or UNSUPPORTED_PROBLEM, it would be expected to have at least one log message at the ERROR level.
    up_msgs/LogMessage[] log_messages

    # Synthetic description of the engine that generated this message.
    string engine_name

**result type:** up_msgs.msg.PlanOneShotResult

.. code-block:: console

    bool success
    string message

PlanOneShotRemoteAction
^^^^^^^^^^^^^^^^^^^^^^^

This action takes in input a problem name which should be known by the running up4ros node and tries to use one of the registered planners to produce a solution in the feedback.
The result will tell us if the planner managed or not to find a solution.
The action assumes that the user has used the services described below to set up at run time a problem to be solved by the planners.

**Goal type:** up_msgs.msg.PlanRequestRemote

.. code-block:: console

    string problem

    uint8 SATISFIABLE=0
    uint8 SOLVED_OPTIMALLY=1
    uint8 resolution_mode

    # Max allowed runtime time in seconds.
    float64 timeout

    # Engine specific options to be passed to the engine
    string engine_option_names
    string engine_option_values


**feedback type:** up_msgs.msg.PlanGenerationResult

.. code-block:: console

    ## Message sent by engine.
    ## Contains the engine exit status as well as the best plan found if any.


    # ==== Engine stopped normally ======

    # Valid plan found
    # The `plan` field must be set.
    uint8 SOLVED_SATISFICING=0
    # Plan found with optimality guarantee
    # The `plan` field must be set and contains an optimal solution.
    uint8 SOLVED_OPTIMALLY=1
    # No plan exists
    uint8 UNSOLVABLE_PROVEN=2
    # The engine was not able to find a solution but does not give any guarantee that none exist
    # (i.e. the engine might not be complete)
    uint8 UNSOLVABLE_INCOMPLETELY=3

    # ====== Engine exited before making any conclusion ====
    # Search stopped before concluding SOLVED_OPTIMALLY or UNSOLVABLE_PROVEN
    # If a plan was found, it might be reported in the `plan` field

    # The engine ran out of time
    uint8 TIMEOUT=13
    # The engine ran out of memory
    uint8 MEMOUT=14
    # The engine faced an internal error.
    uint8 INTERNAL_ERROR=15
    # The problem submitted is not supported by the engine.
    uint8 UNSUPPORTED_PROBLEM=16

    # ====== Intermediate answer ======
    # This Answer is an Intermediate Answer and not a Final one
    uint8 INTERMEDIATE=17

    uint8 status

    # Optional. Best plan found if any.
    up_msgs/Plan plan

    # A set of engine specific values that can be reported, for instance
    # - "grounding-time": "10ms"
    # - "expanded-states": "1290"
    string[] metric_names
    string[] metric_values

    # Optional log messages about the engine's activity.
    # Note that it should not be expected that logging messages are visible to the end user.
    # If used in conjunction with INTERNAL_ERROR or UNSUPPORTED_PROBLEM, it would be expected to have at least one log message at the ERROR level.
    up_msgs/LogMessage[] log_messages

    # Synthetic description of the engine that generated this message.
    string engine_name


**result type:** up_msgs.msg.PlanOneShotRemoteResult

.. code-block:: console

    bool success
    string message

Services
--------

Services are used to handle and manage planning problems interactively at runtime.
In particular, the up4ros node exposes the following services:

AddAction
^^^^^^^^^

This service adds an action to a currently defined domain. The service is defined as:

.. code-block:: console

    string problem_name
    up_msgs/Action action
    ---
    bool success
    string message

where the action is defined as:

.. code-block:: console
        
    ## Unified action representation that represents any kind of actions.

    # Action name. E.g. "move"
    string name

    # Typed and named parameters of the action.
    up_msgs/Parameter[] parameters

    # If set, the action is durative. Otherwise it is instantaneous.
    # features: DURATIVE_ACTIONS
    up_msgs/Duration[] duration

    # Conjunction of conditions that must hold for the action to be applicable.
    up_msgs/Condition[] conditions

    # Conjunction of effects as a result of applying this action.
    up_msgs/Effect[] effects


AddFluent
^^^^^^^^^

This service adds a fluent to one of the problems known to the node. The service is defined as:

.. code-block:: console

    string problem_name
    up_msgs/Fluent fluent
    up_msgs/Expression default_value
    ---
    bool success
    string message

where a fluent is defined as:

.. code-block:: console

    ## A state-dependent variable.
    string name
    # Return type of the fluent.
    string value_type
    # Typed and named parameters of the fluent.
    up_msgs/Parameter[] parameters

    # If non-empty, then any state variable using this fluent that is not explicitly given a value in the initial state
    # will be assumed to have this default value.
    # This allows mimicking the closed world assumption by setting a "false" default value to predicates.
    # Note that in the initial state of the problem message, it is assumed that all default values are set.
    up_msgs/Expression[] default_value

while an expression is defined as:

.. code-block:: console

    up_msgs/ExpressionItem[] expressions
    uint8[] level


AddGoal
^^^^^^^

This service adds a new goal to one of the problems known by the node. The service is defined as:

.. code-block:: console

    string problem_name
    up_msgs/Goal[] goal
    up_msgs/GoalWithCost[] goal_with_cost
    ---
    bool success
    string message

where a goal is defined as:

.. code-block:: console

    ## A Goal is currently an expression that must hold either:
    ## - in the final state,
    ## - over a specific temporal interval (under the `timed_goals` features)

    # Goal expression that must hold in the final state.
    up_msgs/Expression goal

    # Optional. If specified the goal should hold over the specified temporal interval (instead of on the final state).
    # features: TIMED_GOALS
    up_msgs/TimeInterval[] timing


and a goal with cost is defined as:

.. code-block:: console

    ## Represents a goal associated with a cost, used to define oversubscription planning.

    # Goal expression
    up_msgs/Expression goal
    # The cost
    up_msgs/Real cost


AddObject
^^^^^^^^^
This service adds a new object to one of the problems known by the node. The service is defined as:

.. code-block:: console

    string problem_name
    up_msgs/ObjectDeclaration object
    ---
    bool success
    string message

where an object is defined as:

.. code-block:: console

    ## Declares an object with the given name and type.

    # Name of the object.
    string name 
    # Type of the object.
    # The type must have been previously declared in the problem definition.
    string type 


GetProblem
^^^^^^^^^^

Retrieves ones of the problems known by the node. The service is defined as:

.. code-block:: console

    string problem_name
    ---
    up_msgs/Problem problem
    bool success
    string message

where a problem is defined as:

.. code-block:: console

    string domain_name
    string problem_name
    up_msgs/TypeDeclaration[] types
    up_msgs/Fluent[] fluents
    up_msgs/ObjectDeclaration[] objects

    # List of actions in the domain.
    up_msgs/Action[] actions

    # Initial state, including default values of state variables.
    up_msgs/Assignment[] initial_state

    # Facts and effects that are expected to occur strictly later than the initial state.
    # features: TIMED_EFFECT
    up_msgs/TimedEffect[] timed_effects

    # Goals of the planning problem.
    up_msgs/Goal[] goals

    # The plan quality metrics
    up_msgs/Metric[] metrics


    # If the problem is hierarchical, defines the tasks and methods as well as the initial task network.
    # features: hierarchical
    up_msgs/Hierarchy[] hierarchy

    # all features of the problem
    uint8[] features

    ## Features of the problem.
    ## Features are essential in that not supporting a feature `X` should allow disregarding any field tagged with `features: [X]`.

    # PROBLEM_CLASS
    uint8 ACTION_BASED=0
    uint8 HIERARCHICAL=26
    # PROBLEM_TYPE
    uint8 SIMPLE_NUMERIC_PLANNING=30
    uint8 GENERAL_NUMERIC_PLANNING=31
    # TIME
    uint8 CONTINUOUS_TIME=1
    uint8 DISCRETE_TIME=2
    uint8 INTERMEDIATE_CONDITIONS_AND_EFFECTS=3
    uint8 TIMED_EFFECT=4
    uint8 TIMED_GOALS=5
    uint8 DURATION_INEQUALITIES=6
    # EXPRESSION_DURATION
    uint8 STATIC_FLUENTS_IN_DURATIONS=27
    uint8 FLUENTS_IN_DURATIONS=28
    # NUMBERS
    uint8 CONTINUOUS_NUMBERS=7
    uint8 DISCRETE_NUMBERS=8
    uint8 BOUNDED_TYPES=38
    # CONDITIONS_KIND
    uint8 NEGATIVE_CONDITIONS=9
    uint8 DISJUNCTIVE_CONDITIONS=10
    uint8 EQUALITIES=11
    uint8 EXISTENTIAL_CONDITIONS=12
    uint8 UNIVERSAL_CONDITIONS=13
    # EFFECTS_KIND
    uint8 CONDITIONAL_EFFECTS=14
    uint8 INCREASE_EFFECTS=15
    uint8 DECREASE_EFFECTS=16
    uint8 STATIC_FLUENTS_IN_BOOLEAN_ASSIGNMENTS=41
    uint8 STATIC_FLUENTS_IN_NUMERIC_ASSIGNMENTS=42
    uint8 FLUENTS_IN_BOOLEAN_ASSIGNMENTS=43
    uint8 FLUENTS_IN_NUMERIC_ASSIGNMENTS=44
    # TYPING
    uint8 FLAT_TYPING=17
    uint8 HIERARCHICAL_TYPING=18
    # FLUENTS_TYPE
    uint8 NUMERIC_FLUENTS=19
    uint8 OBJECT_FLUENTS=20
    # QUALITY_METRICS
    uint8 ACTIONS_COST=21
    uint8 FINAL_VALUE=22
    uint8 MAKESPAN=23
    uint8 PLAN_LENGTH=24
    uint8 OVERSUBSCRIPTION=29
    # ACTION_COST_KIND
    uint8 STATIC_FLUENTS_IN_ACTIONS_COST=45
    uint8 FLUENTS_IN_ACTIONS_COST=46
    # SIMULATED_ENTITIES
    uint8 SIMULATED_EFFECTS=25

NewProblem
^^^^^^^^^^

This service adds a new problem name to the list of problems known by the node. The service is defined as:

.. code-block:: console

    string problem_name
    ---
    bool success
    string message

PDDLPlanOneShot
^^^^^^^^^^^^^^^

Service equivalent to the PDDLPlanOneShotAction described above. The service is defined as:

.. code-block:: console

    up_msgs/PDDLPlanRequest plan_request
    ---
    up_msgs/PlanGenerationResult plan_result
    bool success
    string message


SetInitialValue
^^^^^^^^^^^^^^^

This service adds a new initial value to one expression of one of the problems known by the node. The service is defined as:

.. code-block:: console

    string problem_name
    up_msgs/Expression expression
    up_msgs/Expression value
    ---
    bool success
    string message

where an expression is defined as:

.. code-block:: console

    up_msgs/ExpressionItem[] expressions
    uint8[] level

SetProblem
^^^^^^^^^^

This service adds a completely defined new problem to the list of problems known by the node. The service is defined as:


.. code-block:: console

    string problem_name
    up_msgs/Problem problem
    ---
    bool success
    string message

where a problem is defined as:

.. code-block:: console

    string domain_name
    string problem_name
    up_msgs/TypeDeclaration[] types
    up_msgs/Fluent[] fluents
    up_msgs/ObjectDeclaration[] objects

    # List of actions in the domain.
    up_msgs/Action[] actions

    # Initial state, including default values of state variables.
    up_msgs/Assignment[] initial_state

    # Facts and effects that are expected to occur strictly later than the initial state.
    # features: TIMED_EFFECT
    up_msgs/TimedEffect[] timed_effects

    # Goals of the planning problem.
    up_msgs/Goal[] goals

    # The plan quality metrics
    up_msgs/Metric[] metrics


    # If the problem is hierarchical, defines the tasks and methods as well as the initial task network.
    # features: hierarchical
    up_msgs/Hierarchy[] hierarchy

    # all features of the problem
    uint8[] features

    ## Features of the problem.
    ## Features are essential in that not supporting a feature `X` should allow disregarding any field tagged with `features: [X]`.

    # PROBLEM_CLASS
    uint8 ACTION_BASED=0
    uint8 HIERARCHICAL=26
    # PROBLEM_TYPE
    uint8 SIMPLE_NUMERIC_PLANNING=30
    uint8 GENERAL_NUMERIC_PLANNING=31
    # TIME
    uint8 CONTINUOUS_TIME=1
    uint8 DISCRETE_TIME=2
    uint8 INTERMEDIATE_CONDITIONS_AND_EFFECTS=3
    uint8 TIMED_EFFECT=4
    uint8 TIMED_GOALS=5
    uint8 DURATION_INEQUALITIES=6
    # EXPRESSION_DURATION
    uint8 STATIC_FLUENTS_IN_DURATIONS=27
    uint8 FLUENTS_IN_DURATIONS=28
    # NUMBERS
    uint8 CONTINUOUS_NUMBERS=7
    uint8 DISCRETE_NUMBERS=8
    uint8 BOUNDED_TYPES=38
    # CONDITIONS_KIND
    uint8 NEGATIVE_CONDITIONS=9
    uint8 DISJUNCTIVE_CONDITIONS=10
    uint8 EQUALITIES=11
    uint8 EXISTENTIAL_CONDITIONS=12
    uint8 UNIVERSAL_CONDITIONS=13
    # EFFECTS_KIND
    uint8 CONDITIONAL_EFFECTS=14
    uint8 INCREASE_EFFECTS=15
    uint8 DECREASE_EFFECTS=16
    uint8 STATIC_FLUENTS_IN_BOOLEAN_ASSIGNMENTS=41
    uint8 STATIC_FLUENTS_IN_NUMERIC_ASSIGNMENTS=42
    uint8 FLUENTS_IN_BOOLEAN_ASSIGNMENTS=43
    uint8 FLUENTS_IN_NUMERIC_ASSIGNMENTS=44
    # TYPING
    uint8 FLAT_TYPING=17
    uint8 HIERARCHICAL_TYPING=18
    # FLUENTS_TYPE
    uint8 NUMERIC_FLUENTS=19
    uint8 OBJECT_FLUENTS=20
    # QUALITY_METRICS
    uint8 ACTIONS_COST=21
    uint8 FINAL_VALUE=22
    uint8 MAKESPAN=23
    uint8 PLAN_LENGTH=24
    uint8 OVERSUBSCRIPTION=29
    # ACTION_COST_KIND
    uint8 STATIC_FLUENTS_IN_ACTIONS_COST=45
    uint8 FLUENTS_IN_ACTIONS_COST=46
    # SIMULATED_ENTITIES
    uint8 SIMULATED_EFFECTS=25



