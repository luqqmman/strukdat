from time import sleep

class Coordinate:
    x = 0
    y = 0
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __str__(self):
        return f'({self.x}, {self.y})'

    def __eq__(self, other):
        return self.x == other.x and self.y == other.y


class Queue:
    ls = []
    def enqueue(self, n):
        self.ls.append(n)

    def dequeue(self):
        tmp = self.ls[0]
        self.ls = self.ls[1:]
        return tmp

    def not_empty(self):
        return len(self.ls)


def printer(m):
    sleep(0.1)
    for i in range(len(m)):
        print(''.join(m[i]))
    print()


# SETTING
MAP_FILE = 'map2.txt'
WALL_CHAR = '#'
START_CHAR = 'S'
FINISH_CHAR = 'E'

MAP = []
start = Coordinate(0,0)
finish = Coordinate(0,0)


# Baca file masukin ke MAP
with open(MAP_FILE, 'r') as f:
    lines = f.read().split('\n')
    for i in range(len(lines)-1):
        MAP.append(list(lines[i]))
        for j in range(len(lines[0])):
            if lines[i][j] == START_CHAR:
                start = Coordinate(i, j) 
            if lines[i][j] == FINISH_CHAR:
                finish = Coordinate(i, j) 


# SET UP buat bfs
BACKUP_MAP = [line.copy() for line in MAP]
SIZE_X = len(MAP)
SIZE_Y = len(MAP[0])
visited = [[False for _ in range(SIZE_Y)] for _ in range(SIZE_X)]
backtracker = [[False for _ in range(SIZE_Y)] for _ in range(SIZE_X)]
container = Queue()
container.enqueue(start)

while container.not_empty():
    position = container.dequeue()
    if position == finish:
        print('\n---------------------------------\n')
        break

    visited[position.x][position.y] = True
    MAP[position.x][position.y] = '*'
    printer(MAP)
    nearby_position = [
        Coordinate(position.x - 1, position.y),
        Coordinate(position.x + 1, position.y),
        Coordinate(position.x, position.y - 1),
        Coordinate(position.x, position.y + 1),
    ] 

    for pos in nearby_position:
        if pos.x < 0: continue
        if pos.y < 0: continue
        if pos.x >= SIZE_X: continue
        if pos.y >= SIZE_Y: continue
        if MAP[pos.x][pos.y] == WALL_CHAR: continue
        if visited[pos.x][pos.y]: continue

        backtracker[pos.x][pos.y] = position
        visited[pos.x][pos.y] = True
        container.enqueue(pos)



position = finish
shortest = 0
while position != start:
    shortest += 1
    BACKUP_MAP[position.x][position.y] = '+'
    printer(BACKUP_MAP)
    position = backtracker[position.x][position.y]



print(f'shortest path: {shortest}')
