import matplotlib.pyplot as plt
import numpy as np


class Bandit:
    def __init__(self, arms=10, mean=0.0, variance=1.0, actionvariance=1.0):
        self.arms = 10
        self.actionvariance = actionvariance
        self.bands = np.random.normal(mean, variance, size=arms)

    def step(self, action):
        """
        choose an action and get an reward
        :param action:
        :return: reward
        """
        if action < 0 or action > self.arms:
            return "action out of bounds"
        return np.random.normal(self.bands[action], self.actionvariance)


class Greedy:
    def __init__(self, arms=10):
        self.arms = arms
        self.arm_reward = np.random.normal(0, 1, size=arms)
        self.count = [0 for i in range(arms)]
        self.avergeReward = 0.0
        self.totalcount = 0.0
        self.totalReward = 0.0

    def getAction(self):
        return np.argmax(self.arm_reward)

    def update(self, action, reward):
        self.count[action] += 1
        self.totalcount += 1
        self.totalReward += reward
        self.avergeReward = self.totalReward / self.totalcount
        self.arm_reward[action] += 1.0 / self.count[action] * (reward - self.arm_reward[action])

    def getAverageStepReward(self):
        return self.avergeReward


class EpsilonGreedy:
    """
    using Epsilon Greedy method to do both exploration and exploitation
    code not shown due to active course assignment useage of this problem
    """
    pass


class OptimisticInitialValue:
    """
    using optimistic initial value to allow exploration
    """
    pass


class SoftMax:
    """
    using a method similar to boltzmann distribution to get actions
    """
    pass


def play(env, agent, num_steps=1000):
    step = []
    avg_rwd = []
    for i in range(num_steps):
        action = agent.getAction()
        reward = env.step(action)
        agent.update(action, reward)
        step.append(i)
        avg_rwd.append(agent.getAverageStepReward())
    return step, avg_rwd


if __name__ == "__main__":
    np.random.seed(20170604)
    env = Bandit()
    greedyAgent = Greedy()
    x, y = play(env, greedyAgent)
    # print(x)
    # print(y)
    plt.plot(x, y)
    plt.xlabel('Steps')
    plt.ylabel('Average reward')
    plt.show()
