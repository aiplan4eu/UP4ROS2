## Unified action representation that represents any kind of actions.

# Action name. E.g. "move"
string name

# Typed and named parameters of the action.
up_msgs/Parameter[] parameters

# If set, the action is durative. Otherwise it is instantaneous.
# features: DURATIVE_ACTIONS
up_msgs/Duration[<=1] duration

# Conjunction of conditions that must hold for the action to be applicable.
up_msgs/Condition[] conditions

# Conjunction of effects as a result of applying this action.
up_msgs/Effect[] effects
