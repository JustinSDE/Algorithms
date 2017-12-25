## implemented Q-learning algorithm using epsilon-decay (episilon-greedy) algorithm
## all previsous algorithms, such as policy evaluation, value iteration, policy iteration
## are bosed on a model that the MDP process is known.
## In Q-learning, we don't need to know the MDP as long as we can interact with the environement

import numpy as np
from GridGame import GridGame
import random


def getAction(epsilon, num_act, Q_table, state):
    if np.random.random() < epsilon:
        return random.randint(0, num_act - 1)
    else:
        return np.argmax(Q_table[state])


if __name__ == "__main__":
    # deterministic case with a step reward of 0.0
    Q_table = np.random.random((11, 4))
    epsilon = 2
    gamma = 0.8
    count_table = np.ones((11, 4))
    print(count_table)
    env = GridGame(stepreward=0.0, stochasticFlag=False)
    EPISODES = 1000
    for i in range(EPISODES):
        state = env.reset()
        done = False
        while not done:
            action = getAction(epsilon, 4, Q_table, state)
            prevstate = state
            state, reward, done = env.step(action)
            alpha = 1.0 / count_table[prevstate][action]
            count_table[prevstate][action] += 1
            if not done:
                Q_table[prevstate][action] += alpha * (
                        reward + 0.8 * np.max(Q_table[state]) - Q_table[prevstate][action])
            else:
                Q_table[prevstate][action] += alpha * (reward - Q_table[prevstate][action])
            print("state {}, reward {}, done {}".format(state, reward, done))
    policy = {}
    values = {}
    for i in range(11):
        policy[i] = np.argmax(Q_table[i])
        values[i] = np.max(Q_table[i])
    env.drawPolicy(policy)
    env.drawValue(values)

    # stchostic case with a step reward of 0.0
    Q_table = np.random.random((11, 4))
    epsilon = 2
    gamma = 0.8
    count_table = np.ones((11, 4))
    print(count_table)
    env = GridGame(stepreward=0.0, stochasticFlag=True)
    EPISODES = 1000
    for i in range(EPISODES):
        state = env.reset()
        done = False
        while not done:
            action = getAction(epsilon, 4, Q_table, state)
            prevstate = state
            state, reward, done = env.step(action)
            alpha = 1.0 / count_table[prevstate][action]
            count_table[prevstate][action] += 1
            if not done:
                Q_table[prevstate][action] += alpha * (
                        reward + 0.8 * np.max(Q_table[state]) - Q_table[prevstate][action])
            else:
                Q_table[prevstate][action] += alpha * (reward - Q_table[prevstate][action])
            print("state {}, reward {}, done {}".format(state, reward, done))
    policy = {}
    values = {}
    for i in range(11):
        policy[i] = np.argmax(Q_table[i])
        values[i] = np.max(Q_table[i])
    env.drawPolicy(policy)
    env.drawValue(values)
