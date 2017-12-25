## this implements the policy iteration method to get the best policy and value on the grid game
## instead of using the epsilon method, I used an optimal value method

import numpy as np
from GridGame import GridGame


def PolicyIteration(states, actions, transitionrewards, gamma=0.8, tol=0.001, verbose=False):
    policy = {}
    for i in range(len(states)):
        policy[i] = 0  # initialize with action 0 policy
    Q_table = np.ones((len(states), len(actions))) * 100
    PolicyChanged = True
    iterations = 0
    while PolicyChanged:
        PolicyChanged = False
        iterations += 1
        delta = tol + 1.0
        while delta > tol:
            delta = 0.0
            for state, action in policy.items():
                TransRwd = transitionrewards[(state, action)]
                newvalue = 0.0
                for prob, newstate, rwd in TransRwd:
                    newvalue += prob * (rwd + gamma * np.max(Q_table[newstate]))
                delta = max(delta, abs(newvalue - Q_table[state][action]))
                Q_table[state][action] = newvalue
        for i in range(len(states)):
            newaction = np.argmax(Q_table[i])
            if newaction != policy[i]:
                PolicyChanged = True
                policy[i] = newaction
    values = {}
    for i in range(len(states)):
        values[i] = Q_table[i][policy[i]]
    return policy, values, iterations


if __name__ == "__main__":
    # deterministic case with step reward 0.0
    env = GridGame(stepreward=0.0, stochasticFlag=False)
    states, actions, transitionrewards = env.generateModel()
    optimalpolicy, optimalvalue, iterations = PolicyIteration(states, actions, transitionrewards, 0.8, 0.001,
                                                              True)
    env.drawPolicy(optimalpolicy)
    env.drawValue(optimalvalue)
    print("number of iterations is : {} \n".format(iterations))

    # stochastic case with step reward 0.0
    env = GridGame(stepreward=0.0, stochasticFlag=True)
    states, actions, transitionrewards = env.generateModel()
    optimalpolicy, optimalvalue, iterations = PolicyIteration(states, actions, transitionrewards, 0.8, 0.001,
                                                              True)
    env.drawPolicy(optimalpolicy)
    env.drawValue(optimalvalue)
    print("number of iterations is : {} \n".format(iterations))

    # stochastic case with step reward -2.0
    env = GridGame(stepreward=-2.0, stochasticFlag=True)
    states, actions, transitionrewards = env.generateModel()
    optimalpolicy, optimalvalue, iterations = PolicyIteration(states, actions, transitionrewards, 0.8, 0.001,
                                                              True)
    env.drawPolicy(optimalpolicy)
    env.drawValue(optimalvalue)
    print("number of iterations is : {} \n".format(iterations))
