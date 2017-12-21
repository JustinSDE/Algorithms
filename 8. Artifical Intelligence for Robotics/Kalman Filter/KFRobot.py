import numpy as np
from numpy.linalg import inv

measurements = [[1., 4.], [3., 5.], [5., 6.], [7., 7.], [9., 8.], [11., 9.]]
initial_xy = [-1., 3.]

dt = 0.1  # time interval
x = np.matrix([[initial_xy[0]], [initial_xy[1]], [0.], [0.]])  # x pos, y pos, x velocity, y velocity
u = np.matrix(np.zeros((4, 1)))  # no control
B = np.matrix(np.zeros((4, 4)))  # no external control
P = np.matrix(np.zeros((4, 4)))  # the error of estimation
P[2, 2] = 1000.0
P[3, 3] = 1000.0  # set error to 1000 because the velocity is unknown
F = np.matrix([[1.0, 0.0, dt, 0.0], [0.0, 1.0, 0.0, dt], [0.0, 0.0, 1.0, 0.0], [0.0, 0.0, 0.0, 1.0]])
# F is prediction matrix that x=x+vx, y=y+vy
H = np.matrix([[1.0, 0.0, 0.0, 0.0], [0.0, 1.0, 0.0, 0.0]])  # measurement matrix, only measures x and y
R = np.matrix([[0.1, 0.0], [0.0, 0.1]])  # measurement noise
I = np.matrix(np.eye(4))  # identity matrix

for i in range(len(measurements)):
    # predication update
    x = np.dot(F, x) + np.dot(B, u)
    P = np.dot(np.dot(F, P), F.T)
    # measurement update
    Z = np.matrix([measurements[i]]).T
    y = Z - H.dot(x)
    S = H.dot(P).dot(H.T) + R
    K = P.dot(H.T).dot(inv(S))
    x = x + K.dot(y)
    P = (I - K.dot(H)).dot(P)

if __name__ == "__main__":
    print("x=\n", x)
    print("P=\n", P)
