# file name: algorithm animator.py
'''
This file is used to create an animation for the algorithm for a robot to collect boxes in
a warehouse and put them in the drop zone based on given warehouse map and box position in
a continuous world
'''
import math
import matplotlib.patches as patches
from matplotlib import pyplot as plt


warehouse = ['..#...',
             '#....#',
             '..##.#',
             '..#..#',
             '#....@']

todo = [(1.0, -.5),
        (0.5, -3.5)]

moves = ['move -1.5807963267948966 0.0', 'move -1.5607963267948968 1.0',
         'move -1.5707963267948966 3.0', 'move 1.5707963267948966 3.0',
         'move -1.3400698904821917 0.6713069578484757', 'lift 0', 'move -1.5807963267948966 0.0',
         'move -1.560796326794897 0.6713069578484757', 'move 1.3400698904821917 3.0',
         'move -1.5707963267948966 3.0', 'move 1.5707963267948966 0.5099999999999998',
         'down 5.5 -4.5', 'move -1.5807963267948966 0.0', 'move -1.5607963267948968 3.51',
         'move -1.5707963267948966 1.0', 'move 1.5707963267948966 0.51', 'lift 1',
         'move -1.5807963267948966 0.0', 'move -1.5607963267948968 0.51', 'move -1.5707963267948966 1.0',
         'move 1.5707963267948966 3.51', 'down 5.5 -4.5']

STARTPAUSE = 10
INTERVALPAUSE = 0.15
sz = max(len(warehouse), len(warehouse[0]))
dropzonepos = (0, 0)
for i in range(len(warehouse)):
    for j in range(len(warehouse[0])):
        if warehouse[i][j] == '@':
            dropzonepos = (i, j)
pos = [dropzonepos[1] + 0.5, -dropzonepos[0] - 0.5]
hasbox = False
n = 0
heading = 0.0


def drawWarehouse(ax, hasbox, pos, todo, n, heading):
    ax.clear()
    plt.axis('scaled')
    plt.axis('off')
    plt.axis([-0.5, sz + 0.5, -sz - 0.5, 0.5])
    ax.add_patch(patches.Rectangle((0, 0), len(
        warehouse[0]), -len(warehouse), fc='none', ec='black'))
    for i in range(len(warehouse)):
        for j in range(len(warehouse[0])):
            if warehouse[i][j] == '#':
                ax.add_patch(patches.Rectangle((j, -i), 1, -1, fc='black'))
            elif warehouse[i][j] == '.':
                ax.add_patch(patches.Rectangle((j, -i), 1, -1, fc='none'))
            elif warehouse[i][j] == '@':
                pass
                ax.add_patch(patches.Rectangle((j, -i), 1, -1, fc='green'))
            else:
                pass
    for i in range(n, len(todo)):
        ax.add_patch(patches.Rectangle(
            (todo[i][0] - 0.1, todo[i][1] - 0.1), 0.2, 0.2, fc='red'))

    ax.add_patch(patches.Circle((pos[0], pos[1]), radius=0.25, fc='magenta'))
    if hasbox:
        ax.add_patch(patches.Rectangle(
            (pos[0] - 0.1, pos[1] - 0.1), 0.2, 0.2, fc='red'))
    newpos = (pos[0] + 0.25 * math.cos(heading),
              pos[1] + 0.25 * math.sin(heading))
    ax.plot([pos[0], newpos[0]], [pos[1], newpos[1]], 'k', lw=2)


fig = plt.figure(1)
ax = fig.add_subplot(111)
plt.axis('scaled')
plt.axis('off')
plt.axis([-0.5, sz + 0.5, -sz - 0.5, 0.5])
plt.ion()
plt.show()
print(pos)
drawWarehouse(ax, hasbox, pos, todo, n, heading)
plt.pause(STARTPAUSE)


def executemoves():
    hasbox = False
    global n, pos, heading
    for eachmove in moves:
        paras = eachmove.split(" ")
        if paras[0] == 'lift':
            hasbox = True
            n += 1
        elif paras[0] == 'down':
            hasbox = False
            drawWarehouse(ax, hasbox, pos, todo, n, heading)
            ax.add_patch(patches.Rectangle(
                (float(paras[1]) - 0.1, float(paras[2]) - 0.1), 0.2, 0.2, fc='red'))
            plt.pause(INTERVALPAUSE)
        elif paras[0] == 'move':
            drawWarehouse(ax, hasbox, pos, todo, n, heading)
            prevpos = pos
            turning = float(paras[1])
            heading = (heading + turning + math.pi) % (2 * math.pi) - math.pi
            distance = float(paras[2])
            pos = (prevpos[0] + distance * math.cos(heading),
                   prevpos[1] + distance * math.sin(heading))
            ax.add_patch(patches.Circle((pos[0], pos[1]), 0.25, fc='magenta'))
            heading1 = heading + math.pi / 2
            heading2 = heading - math.pi / 2
            x1x2 = [prevpos[0] + 0.25 *
                    math.cos(heading1), pos[0] + 0.25 * math.cos(heading1)]
            y1y2 = [prevpos[1] + 0.25 *
                    math.sin(heading1), pos[1] + 0.25 * math.sin(heading1)]
            x3x4 = [prevpos[0] + 0.25 *
                    math.cos(heading2), pos[0] + 0.25 * math.cos(heading2)]
            y3y4 = [prevpos[1] + 0.25 *
                    math.sin(heading2), pos[1] + 0.25 * math.sin(heading2)]
            ax.plot(x1x2, y1y2, color='magenta')
            ax.plot(x3x4, y3y4, color='magenta')
            newpos = (pos[0] + 0.25 * math.cos(heading),
                      pos[1] + 0.25 * math.sin(heading))
            ax.plot([pos[0], newpos[0]], [pos[1], newpos[1]], 'k', lw=2)
            plt.pause(INTERVALPAUSE)
        else:
            pass
        drawWarehouse(ax, hasbox, pos, todo, n, heading)
        plt.pause(INTERVALPAUSE)
    plt.pause(STARTPAUSE)


executemoves()
