from matplotlib import pyplot as plt
import matplotlib.patches as patches


class DeliveryPlanner:
    def __init__(self, warehouse, todo):
        pass
    def plan_delivery(self):
        moves = []
        return moves

STARTPAUSE=10
INTERVALPAUSE=0.15

warehouse = ['..#1..',   ## map of warehouse
             '#....#',
             '..##.#',
             '..#2.#',
             '#....@']
dropzonepos = (4, 5)    ## drop zone position of thw warehouse

moves = ['move 3 4', 'move 2 4', 'move 1 4', 'lift 1', 'move 2 4', 'move 3 4', 'down 4 5', 'lift 2', 'down 4 5']

fig = plt.figure(1)
ax = fig.add_subplot(111)
plt.axis('scaled')
plt.axis('off')
sz = max(len(warehouse), len(warehouse[0]))
plt.axis([-0.5, sz + 0.5, -sz - 0.5, 0.5])
plt.ion()
plt.show()
delta = [[-1, 0],  # go up
         [0, -1],  # go left
         [1, 0],  # go down
         [0, 1],  # go right
         [-1, -1],  # go up left
         [-1, 1],  # go up right
         [1, -1],  # go down left
         [1, 1]  # go down right
         ]


def drawWarehouse(ax, warehouse, hasbox, pos):
    ax.clear()
    plt.axis('scaled')
    plt.axis('off')
    plt.axis([-0.5, sz + 0.5, -sz - 0.5, 0.5])
    for i in range(len(warehouse)):
        for j in range(len(warehouse[0])):
            if warehouse[i][j] == '#':
                ax.add_patch(patches.Rectangle((j, -i), 1, -1, fc='black', ec='#222222', lw=0.5))
            elif warehouse[i][j] == '.':
                ax.add_patch(patches.Rectangle((j, -i), 1, -1, fc='none', ec='#222222', lw=0.5))
            elif warehouse[i][j] == '@':
                ax.add_patch(patches.Rectangle((j, -i), 1, -1, fc='green', ec='#222222', lw=0.5))
            else:
                ax.add_patch(patches.Rectangle((j, -i), 1, -1, fc='none', ec='#222222', lw=0.5))
                ax.add_patch(patches.Rectangle((j + 0.4, -i - 0.4), 0.2, -0.2, fc='red'))
    ax.add_patch(patches.Circle((pos[1] + 0.5, -pos[0] - 0.5), radius=0.25, fc='blue'))
    if hasbox:
        ax.add_patch(patches.Rectangle((pos[1] + 0.4, -pos[0] - 0.4), 0.2, -0.2, fc='red'))


pos = [dropzonepos[0], dropzonepos[1]]
hasbox = False
drawWarehouse(ax, warehouse, hasbox, pos)
plt.pause(STARTPAUSE)

newarehouse = [[warehouse[i][j] for j in range(len(warehouse[0]))] for i in range(len(warehouse))]
# print(newarehouse)

def executemoves():
    hasbox = False
    for eachmove in moves:
        paras = eachmove.split(" ")
        if paras[0] == 'lift':
            hasbox = True
            boxnum = paras[1]
            for i in range(8):
                rownum = pos[0] + delta[i][0]
                colnum = pos[1] + delta[i][1]
                if 0 <= rownum < len(newarehouse) and 0 <= colnum < len(newarehouse[0]) and \
                        newarehouse[rownum][colnum] == paras[1]:
                    newarehouse[rownum][colnum] = '.'
                    break

        elif paras[0] == 'down':
            hasbox = False
            drawWarehouse(ax, newarehouse, hasbox, pos)
            ax.add_patch(patches.Rectangle((dropzonepos[1] + 0.4, -dropzonepos[0] - 0.4), 0.2, -0.2, fc='red'))
            plt.pause(INTERVALPAUSE)

        elif paras[0] == "move":
            pos[0] = int(paras[1])
            pos[1] = int(paras[2])
        drawWarehouse(ax, newarehouse, hasbox, pos)
        plt.pause(INTERVALPAUSE)
    plt.pause(STARTPAUSE)

executemoves()
