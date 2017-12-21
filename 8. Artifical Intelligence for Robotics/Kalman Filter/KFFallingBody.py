import numpy as np
from numpy.linalg import inv
import matplotlib.pyplot as plt

np.random.seed(12475)
ypos = [100.0]
v = [0.0]

g = 2.0

lasty = 100
lastv = 0.0
for i in range(10):  # generate true positions
    lasty, lastv = lasty + lastv - g / 2, lastv - g
    ypos.append(lasty)
    v.append(lastv)

measurements = []  # generate measurement with noise
for eachy in ypos:
    measurements.append(np.random.normal(eachy, 10))
initial_yv = [95., 1.3]

x = np.matrix([[initial_yv[0]], [initial_yv[1]]])  # y and vy
u = -g  # with control
B = np.matrix([[0.5], [1.0]])  # control matrix
P = np.matrix(np.eye(2)) * 100  # set the error to 100 since state is unknown

F = np.matrix([[1.0, 1.0], [0.0, 1.0]])  # F is the predication matrix
H = np.matrix([[1.0, 0.0]])  # measurement matrix, only measures x and y
R = np.matrix([[5000.0]])  # measurement noise
I = np.matrix(np.eye(2))  # identity matrix

predicted_y = []
predicted_vy = []
for i in range(len(measurements)):
    # predication update
    x = np.dot(F, x) + B * u
    P = np.dot(np.dot(F, P), F.T)
    # measurement update
    Z = np.matrix([measurements[i]]).T
    y = Z - H.dot(x)
    S = H.dot(P).dot(H.T) + R
    K = P.dot(H.T).dot(inv(S))
    x = x + K.dot(y)
    P = (I - K.dot(H)).dot(P)

    predicted_y.append(x[0, 0])
    predicted_vy.append(x[1, 0])

if __name__ == "__main__":
    print("true positions are:\n", ypos)
    print("true velocities are:\n", v)
    print("measurements are:\n", measurements)
    print("predicted y are:\n", predicted_y)
    print("predicted vy are:\n", predicted_vy)

    plt.plot(predicted_y, 'bo-', label="Predicted")
    plt.plot(measurements, 'rs--', label="Measured")
    plt.plot(ypos, 'k*-', label="True")
    plt.legend()
    plt.show()
