## This is originally posted by Aritra Chatterjee and Itamar Grutman on Piazza.com
## as a tool for students to visualize their result

from math import *
import matplotlib.patches as patches
import matplotlib.pyplot as plt


def drawWH(wh, todo, moves):
    pos = convert_moves(init(wh), moves)
    ax = plt.gca()
    plt.gca().set_aspect('equal', adjustable='box')
    plt.xlim(0, len(wh[0]))
    plt.ylim(-len(wh), 0)
    ax.add_artist(plt.Circle((pos[0][0], pos[0][1]), 0.25, color='g'))
    for p in range(1, len(pos)):
        ax.add_artist(plt.Circle((pos[p][0], pos[p][1]), 0.25, color='r'))

    for box in todo:
        ax.add_artist(patches.Rectangle((box[0] - 0.1, box[1] - 0.1), 0.2, 0.2))

    for row in range(len(wh)):
        for col in range(len(wh[0])):
            ch = wh[row][col]
            if ch == '#':
                p = (col, -row)
                ax.add_artist(patches.Rectangle((p[0], p[1] - 1), 1, 1, color='k'))

    for i in range(len(pos) - 1):
        pc = pos[i]
        qc = pos[i + 1]
        ux = qc[0] - pc[0]
        uy = qc[1] - pc[1]
        d = sqrt(ux * ux + uy * uy)
        if d > 1e-2:
            ux /= d
            uy /= d
            u = (uy * 0.25, -ux * 0.25)  # orthogonal unit vector times length
            p = (pc[0] - u[0], pc[1] - u[1])
            q = (qc[0] - u[0], qc[1] - u[1])
            for i in range(2):
                plt.plot([p[0], q[0]], [p[1], q[1]], 'k-')
                p = (pc[0] + u[0], pc[1] + u[1])
                q = (qc[0] + u[0], qc[1] + u[1])
    plt.show()


def convert_moves(init, moves):
    pos = []
    curr_pos = init
    for move in moves:
        new_pos = to_position(curr_pos, move)
        pos.append(new_pos[:2])
        curr_pos = new_pos
    return pos


def to_position(init, move):
    if 'move' in move:
        split = move.split()
        steer = float(split[1])
        d = float(split[2])
        heading = init[2] + steer
        return [init[0] + d * cos(heading), init[1] + d * sin(heading), heading]
    return init


def init(wh):
    for i in range(len(wh)):
        for j in range(len(wh[0])):
            if wh[i][j] == '@':
                return [j + 0.5, -i - 0.5, 0]


warehouse = ['..#...',
             '#....#',
             '..##.#',
             '..#..#',
             '#....@']
todo = [(1.0, -.5), (0.5, -3.5)]

moves = ['move -1.5807963267948966 0.0', 'move -1.5607963267948968 1.0',
         'move -1.5707963267948966 3.0', 'move 1.5707963267948966 3.0',
         'move -1.3400698904821917 0.6713069578484757', 'lift 0', 'move -1.5807963267948966 0.0',
         'move -1.560796326794897 0.6713069578484757', 'move 1.3400698904821917 3.0',
         'move -1.5707963267948966 3.0', 'move 1.5707963267948966 0.5099999999999998',
         'down 5.5 -4.5', 'move -1.5807963267948966 0.0', 'move -1.5607963267948968 3.51',
         'move -1.5707963267948966 1.0', 'move 1.5707963267948966 0.51', 'lift 1',
         'move -1.5807963267948966 0.0', 'move -1.5607963267948968 0.51', 'move -1.5707963267948966 1.0',
         'move 1.5707963267948966 3.51', 'down 5.5 -4.5']

drawWH(warehouse, todo, moves)
