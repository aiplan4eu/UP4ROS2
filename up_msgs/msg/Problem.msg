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
up_msgs/Hierarchy[<=1] hierarchy

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