# Value iteration algorithm performed on the random walk environment, both stochastic and non-stochastic

import numpy as np
from GridGame import GridGame


def ValueIteration(states, actions, transitionreward, gamma=0.8, tol=0.001, verbose=False):
    delta = tol + 1.0
    Q_table = np.random.random((len(states), len(actions)))
    iterations = 0
    if verbose:
        print(Q_table)
    while delta > tol:
        delta = 0.0
        iterations += 1
        for state in range(len(states)):
            for action in range(len(actions)):
                newvalue = 0.0
                for prob, newstate, rwd in transitionreward[(state, action)]:
                    newvalue += prob * (rwd + gamma * np.max(Q_table[newstate]))
                delta = max(delta, abs(newvalue - Q_table[state][action]))
                Q_table[state][action] = newvalue
    optimalpolicy = {}
    optimalvalue = {}
    for i in range(len(states)):
        optimalpolicy[states[i]] = np.argmax(Q_table[states[i]])
        optimalvalue[states[i]] = np.max(Q_table[states[i]])
    return Q_table, optimalpolicy, optimalvalue, iterations


if "__main__" == __name__:
    # deterministic case with step reward 0.0
    env = GridGame(stepreward=0.0, stochasticFlag=False)
    states, actions, transitionrewards = env.generateModel()
    Q_table, optimalpolicy, optimalvalue, iterations = ValueIteration(states, actions, transitionrewards, 0.8, 0.001,
                                                                      True)
    env.drawPolicy(optimalpolicy)
    env.drawValue(optimalvalue)
    print("number of iterations is : {} \n".format(iterations))

    # deterministic case with step reward 0.5
    env = GridGame(stepreward=0.5, stochasticFlag=False)
    states, actions, transitionrewards = env.generateModel()
    Q_table, optimalpolicy, optimalvalue, iterations = ValueIteration(states, actions, transitionrewards, 0.8, 0.001,
                                                                      True)
    env.drawPolicy(optimalpolicy)
    env.drawValue(optimalvalue)
    print("number of iterations is : {} \n".format(iterations))

    # stochastic case with step reward 0.0
    env = GridGame(stepreward=0.0, stochasticFlag=True)
    states, actions, transitionrewards = env.generateModel()
    Q_table, optimalpolicy, optimalvalue, iterations = ValueIteration(states, actions, transitionrewards, 0.8, 0.001,
                                                                      True)
    env.drawPolicy(optimalpolicy)
    env.drawValue(optimalvalue)
    print("number of iterations is : {} \n".format(iterations))

    # stochastic case with step reward 0.5
    env = GridGame(stepreward=0.5, stochasticFlag=True)
    states, actions, transitionrewards = env.generateModel()
    Q_table, optimalpolicy, optimalvalue, iterations = ValueIteration(states, actions, transitionrewards, 0.8, 0.001,
                                                                      True)
    env.drawPolicy(optimalpolicy)
    env.drawValue(optimalvalue)
    print("number of iterations is : {} \n".format(iterations))

    # stochastic case with step reward -1.0
    env = GridGame(stepreward=-1.0, stochasticFlag=True)
    states, actions, transitionrewards = env.generateModel()
    Q_table, optimalpolicy, optimalvalue, iterations = ValueIteration(states, actions, transitionrewards, 0.8, 0.001,
                                                                      True)
    env.drawPolicy(optimalpolicy)
    env.drawValue(optimalvalue)
    print("number of iterations is : {} \n".format(iterations))

    # stochastic case with step reward -2.0
    env = GridGame(stepreward=-2.0, stochasticFlag=True)
    states, actions, transitionrewards = env.generateModel()
    Q_table, optimalpolicy, optimalvalue, iterations = ValueIteration(states, actions, transitionrewards, 0.8, 0.001,
                                                                      True)
    env.drawPolicy(optimalpolicy)
    env.drawValue(optimalvalue)
    print("number of iterations is : {} \n".format(iterations))
