# filename Policy Evaluation .py
# use 2 methods to run policy evaluation on a simple random walk problem
'''
in a simple random walk, there are 11 states, at each state of the middle 9,
the object can move either to the left or to the right with 0.5 probability,
if the object ends at the leftmost state, it will receive a reward of 0,
if the object ends at the rightmost state, it will receive a reward of 1.
the step reward is set to be zero
'''
import numpy as np
from numpy.linalg import inv

## Method one, linear porgramming
Omega = np.matrix(np.zeros((11, 11)))
# print(Omega)
Xi = np.matrix(np.zeros((11, 1)))
# print(Xi)
Omega[0, 0] = 1.0
Xi[0, 0] = 0.0
Omega[10, 10] = 1.0
Xi[10, 0] = 1.0
for i in range(1, 10):
    Omega[i, i] = 1.0
    Omega[i, i - 1] = -0.5
    Omega[i, i + 1] = -0.5
print(Omega)
print(Xi)

values = inv(Omega).dot(Xi)
print("-----------values calculated by linear programming-----------\n", values.T)

## value iteration method
values = np.random.rand(11)
values[0] = 0.0
values[10] = 1.0
# print(values)

delta = 1.0
TOL = 0.0001
iterations = 0
while delta > TOL:
    delta = 0.0
    iterations += 1
    for i in range(1, 10):
        newvalue = (values[i - 1] + values[i + 1]) / 2.0
        change = abs(values[i] - newvalue)
        values[i] = newvalue
        delta = max(delta, change)
print("-----number of iterations is----- {}".format(iterations))
print("------values calculated by iteration method are ------\n", values)
