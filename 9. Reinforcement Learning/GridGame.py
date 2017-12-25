# -*- coding: utf-8 -*-
"""
A stochastic/non-stochastic grid game used as learning example
"""
import random
import matplotlib.pyplot as plt
import matplotlib.patches as patches


class GridGame:
    Actions = [
        (-1, 0),  # up
        (0, -1),  # left
        (1, 0),  # down
        (0, 1)  # left
    ]

    def __init__(self, stepreward=0.0, stochasticFlag=False):
        self.colnum = 4
        self.rownum = 3
        self.block = [(1, 1)]
        self.positive_goal = [(0, 3)]
        self.negative_goal = [(1, 3)]
        self.row = 2
        self.col = 0
        self.state = self._stateNumber(self.row, self.col)
        self.stepreward = stepreward
        self.stochasticFlag = stochasticFlag

    def _stateNumber(self, row, col):
        num = row * 4 + col
        if (num > 5):
            num = num - 1
        return num

    def _toGrid(self, number):
        if number >= 5:
            number += 1
        row = int(number // 4)
        col = int(number % 4)
        return row, col

    def step(self, actnum):
        epsilon = random.random()
        if self.stochasticFlag:
            if epsilon < 0.1:
                actnum = (actnum + 1) % 4
            elif epsilon < 0.2:
                actnum = (actnum - 1) % 4
        action = GridGame.Actions[actnum]
        newrow = self.row + action[0]
        newcol = self.col + action[1]
        if 0 <= newrow < self.rownum and 0 <= newcol < self.colnum and ((newrow, newcol) not in self.block):
            self.row = newrow
            self.col = newcol
        done = False
        reward = self.stepreward
        if (self.row, self.col) in self.positive_goal:
            reward += 1.0
            done = True
        if (self.row, self.col) in self.negative_goal:
            reward -= 1.0
            done = True
        newstate = self._stateNumber(self.row, self.col)
        return newstate, reward, done

    def reset(self, statenumber=7):
        self.row, self.col = self._toGrid(statenumber)
        return statenumber

    def _nextState(self, row, col, actnum):
        newrow = row + GridGame.Actions[actnum][0]
        newcol = col + GridGame.Actions[actnum][1]
        if 0 <= newrow < self.rownum and 0 <= newcol < self.colnum and ((newrow, newcol) not in self.block):
            return newrow, newcol
        else:
            return row, col

    def generateModel(self):
        states = [i for i in range(11)]
        actions = [i for i in range(4)]
        TransitionReward = {}  # {(state, action): [(probability, resulting state, reward)]}
        for state in range(11):
            for action in range(4):
                row, col = self._toGrid(state)
                if (row, col) in self.negative_goal or (row, col) in self.positive_goal:
                    TransitionReward[(state, action)] = [(1.0, state, 0.0)]
                else:
                    if self.stochasticFlag == True:
                        newrow, newcol = self._nextState(row, col, action)
                        newstate = self._stateNumber(newrow, newcol)
                        newreward = self.stepreward
                        if (newrow, newcol) in self.positive_goal:
                            newreward += 1.0
                        elif (newrow, newcol) in self.negative_goal:
                            newreward += -1.0
                        TransitionReward[(state, action)] = [(0.8, newstate, newreward)]

                        newrow, newcol = self._nextState(row, col, (action + 1) % 4)
                        newstate = self._stateNumber(newrow, newcol)
                        newreward = self.stepreward
                        if (newrow, newcol) in self.positive_goal:
                            newreward += 1.0
                        elif (newrow, newcol) in self.negative_goal:
                            newreward += -1.0
                        TransitionReward[(state, action)].append((0.1, newstate, newreward))

                        newrow, newcol = self._nextState(row, col, (action - 1) % 4)
                        newstate = self._stateNumber(newrow, newcol)
                        newreward = self.stepreward
                        if (newrow, newcol) in self.positive_goal:
                            newreward += 1.0
                        elif (newrow, newcol) in self.negative_goal:
                            newreward += -1.0
                        TransitionReward[(state, action)].append((0.1, newstate, newreward))

                    else:
                        newrow, newcol = self._nextState(row, col, action)
                        newstate = self._stateNumber(newrow, newcol)
                        newreward = self.stepreward
                        if (newrow, newcol) in self.positive_goal:
                            newreward += 1.0
                        elif (newrow, newcol) in self.negative_goal:
                            newreward += -1.0
                        TransitionReward[(state, action)] = [(1.0, newstate, newreward)]
        return states, actions, TransitionReward

    def drawPolicy(self, policy=None):
        fig = plt.figure(1)
        ax = fig.add_subplot(111)
        ax.axis('scaled')
        ax.axis([-0.5, 4.5, -3.5, 0.5])
        ax.axis('off')
        for i in range(self.rownum):
            for j in range(self.colnum):
                facecolor = 'none'
                if (i, j) in self.block:
                    facecolor = 'k'
                elif (i, j) in self.positive_goal:
                    facecolor = 'g'
                elif (i, j) in self.negative_goal:
                    facecolor = 'r'
                ax.add_patch(patches.Rectangle((j, -i), 1, -1, fc=facecolor, ec='k'))
        if policy is not None:
            for key, value in policy.items():
                row, col = self._toGrid(key)
                if (row, col) in self.negative_goal:
                    continue
                elif (row, col) in self.positive_goal:
                    continue
                elif (row, col) in self.block:
                    continue
                if value == 0:
                    dx = 0.0
                    dy = 0.2
                elif value == 1:
                    dx = -0.2
                    dy = 0.0
                elif value == 2:
                    dx = 0.0
                    dy = -0.2
                elif value == 3:
                    dx = 0.2
                    dy = -0.0
                else:
                    dx = 0.0
                    dy = 0.0
                ax.arrow(col + 0.5 - dx, -row - 0.5 - dy, 2 * dx, 2 * dy, head_width=0.1, head_length=0.2, ec='k',
                         fc='k')
        plt.show()

    def drawValue(self, Value=None):
        fig = plt.figure(1)
        ax = fig.add_subplot(111)
        ax.axis('scaled')
        ax.axis([-0.5, 4.5, -3.5, 0.5])
        ax.axis('off')
        for i in range(self.rownum):
            for j in range(self.colnum):
                facecolor = 'none'
                if (i, j) in self.block:
                    facecolor = 'k'
                elif (i, j) in self.positive_goal:
                    facecolor = 'g'
                elif (i, j) in self.negative_goal:
                    facecolor = 'r'
                ax.add_patch(patches.Rectangle((j, -i), 1, -1, fc=facecolor, ec='k'))
        if Value is not None:
            for key, value in Value.items():
                row, col = self._toGrid(key)
                # if (row, col) in self.negative_goal:
                #     continue
                # elif (row, col) in self.positive_goal:
                #     continue
                if (row, col) in self.block:
                    continue
                ax.text(col + 0.5, -row - 0.5, "{0:.2f}".format(value), horizontalalignment='center',
                        verticalalignment='center', fontsize=14)

        plt.show()


if __name__ == "__main__":
    ## Test the above grid game to see if the functions work correctly
    env = GridGame()
    policy = {}
    for i in range(11):
        policy[i] = random.randint(0, 3)
    print(policy)

    ## draw policy with a randomized policy
    env.drawPolicy(policy)
    values = {}
    for i in range(11):
        values[i] = random.random() * 10

    ## draw values with a randomized policy
    env.drawValue(values)

    ## test the model

    states, actions, transitionrewards = env.generateModel()
    print("states are: \n", states)
    print("actions are:\n", actions)
    print("transition and rewards are:\n", transitionrewards)

    ## test the step function

    env = GridGame()
    for i in range(1000):
        done = False
        env.reset()
        while not done:
            action = random.randint(0, 3)
            newstate, reward, done = env.step(action)
            print("state {}, reward {}, done {}".format(newstate, reward, done))
    print("finished 1000 tests")
