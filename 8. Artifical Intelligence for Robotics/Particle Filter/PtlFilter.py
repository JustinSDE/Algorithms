import math
import random
import matplotlib.pyplot as plt

pi = math.pi
NOISE_FLAG = True


def angle_trunc(theta):
    '''
    calculate the heading angle of robot in range of [-pi, pi)
    :param theta: heading
    :return: heading in [-pi, pi)
    '''
    return (theta + pi) % (2 * pi) - pi


def move(pos, command):
    '''
    calculate the new pos of a robot after a move
    :param pos: a tuple as (x, y, theta)
    :param command: (steering, heading)
    :return: new pos
    '''
    x, y, theta = pos
    steering, distance = command
    newheading = angle_trunc(theta + steering)
    if NOISE_FLAG:
        newheading += random.gauss(0, 0.01)
        distance += random.gauss(0, distance * 0.01)
    x += distance * math.cos(newheading)
    y += distance * math.sin(newheading)
    return (x, y, newheading)


def measure(pos):
    '''
    calculate the measured position of robot
    :param pos: x, y, thea
    :return: x, y
    '''
    x, y, _ = pos
    if NOISE_FLAG:
        x += random.gauss(0, 0.01 * x)
        y += random.gauss(0, 0.01 * x)
    return x, y


def prob(x1, y1, x2, y2):
    return math.exp((-(x1 - x2) ** 2 - (y1 - y2) ** 2) / 2.0)


if __name__ == "__main__":
    fig = plt.figure(1)  # to show plot
    ax = fig.add_subplot(111)
    ax.axis('scaled')
    ax.axis([-10, 10, -10, 10])
    plt.ion()
    plt.show()
    realrobot = (0., 0., 0.)  # initialize the real robot
    mearobot = measure(realrobot)
    random.seed(22485)
    movements = []
    for i in range(20):
        angle = angle_trunc(random.random() * 2 * pi)
        distance = random.random() * 2 + 1
        movements.append((angle, distance))
    # print(movements)

    particles = []  # initialize particles
    x_particles = []
    y_particles = []  # for plot purpose
    for i in range(3000):
        heading = angle_trunc(random.random() * 2 * pi)
        x = (random.random() - 0.5) * 15
        y = (random.random() - 0.5) * 15
        particles.append((x, y, heading))
        x_particles.append(x)
        y_particles.append(y)
    sampling_prob = [1.0 / 1000 for i in range(1000)]

    ax.clear()
    ax.axis('scaled')
    ax.axis([-10, 10, -10, 10])
    ax.plot(x_particles, y_particles, 'r.')
    ax.plot([realrobot[0]], [realrobot[1]], 'ks')
    plt.pause(10)

    for j, eachmove in enumerate(movements):  # processing the robot's position using particle filters
        realrobot = move(realrobot, eachmove)
        mearobot = measure(realrobot)
        max_prob = 0.0
        for i in range(1000):
            particles[i] = move(particles[i], eachmove)
            sampling_prob[i] = prob(mearobot[0], mearobot[1], particles[i][0], particles[i][1])
            max_prob = max(max_prob, sampling_prob[i])
        print(sampling_prob)
        newparticles = []
        beta = 0.0
        index = 0
        x_particles = []
        y_particles = []
        for i in range(1000):  # use a random wheel to get the value
            beta += random.random() * 2 * max_prob
            while sampling_prob[index] <= beta:
                beta -= sampling_prob[index]
                index = (index + 1) % 1000
            newparticles.append(particles[index])
            x_particles.append(particles[index][0])
            y_particles.append(particles[index][1])
        particles = newparticles

        # visualization moddule
        ax.clear()
        ax.axis('scaled')
        ax.axis([-10, 10, -10, 10])
        ax.plot(x_particles, y_particles, 'r.')
        ax.plot([realrobot[0]], [realrobot[1]], 'ks')
        plt.pause(1)
