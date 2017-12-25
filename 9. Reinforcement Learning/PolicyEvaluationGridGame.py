# Policy evaluation on the grid game environment, both stochastic and non-stochastic
from GridGame import GridGame
import numpy as np


def PolicyEvaluation(policy, states, transitionreward, gamma=0.8, tol=0.001, verbose=False):
    values = {}
    for i in range(len(states)):
        values[states[i]] = np.random.random() - 0.5
    if verbose:
        print("values before evaluation:\n", values)
    iterations = 0
    delta = tol + 1.0
    while delta > tol:
        delta = 0.0
        for state, action in policy.items():
            TransRwd = transitionreward[(state, action)]
            newvalue = 0.0
            for prob, newstate, rwd in TransRwd:
                newvalue += prob * (rwd + gamma * values[newstate])
            delta = max(delta, abs(newvalue - values[state]))
            values[state] = newvalue
        iterations += 1
    if verbose:
        print("values after policy evaluation:\n", values)
    return values, iterations


if __name__ == "__main__":
    policy = {0: 3, 1: 3, 2: 2, 3: 0, 4: 0, 5: 3, 6: 1, 7: 2, 8: 3, 9: 3, 10: 0}

    # deterministic case with step reward 0.0
    env = GridGame(stepreward=0.0, stochasticFlag=False)
    env.drawPolicy(policy)
    states, actions, transitionrewards = env.generateModel()
    values, iterations = PolicyEvaluation(policy, states, transitionrewards, 0.8, 0.001, True)
    env.drawValue(values)
    print("number of iterations: {}\n\n\n".format(iterations))

    # deterministic case with step reward 2.0
    env = GridGame(stepreward=2.0, stochasticFlag=False)
    env.drawPolicy(policy)
    states, actions, transitionrewards = env.generateModel()
    values, iterations = PolicyEvaluation(policy, states, transitionrewards, 0.8, 0.001, True)
    env.drawValue(values)
    print("number of iterations: {}\n\n\n".format(iterations))

    # schostic case with step reward 0.0
    env = GridGame(stepreward=0.0, stochasticFlag=True)
    env.drawPolicy(policy)
    states, actions, transitionrewards = env.generateModel()
    values, iterations = PolicyEvaluation(policy, states, transitionrewards, 0.8, 0.001, True)
    env.drawValue(values)
    print("number of iterations: {}\n\n\n".format(iterations))

    # schostic case with step reward 2.0
    env = GridGame(stepreward=2.0, stochasticFlag=True)
    env.drawPolicy(policy)
    states, actions, transitionrewards = env.generateModel()
    values, iterations = PolicyEvaluation(policy, states, transitionrewards, 0.8, 0.001, True)
    env.drawValue(values)
    print("number of iterations: {}\n\n\n".format(iterations))
