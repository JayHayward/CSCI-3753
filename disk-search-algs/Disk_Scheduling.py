from enum import Enum


class Direction(Enum):
    ALL = 0
    DOWN = 1
    UP = 2


DIRECTION = Direction.ALL

MIN_CYLINDER = 0
MAX_CYLINDER = 99
HEAD_START = 15
REQUESTS = (40, 48, 14, 44, 90, 99, 55)


def print_results(results):
    distance_travelled = 0
    current = HEAD_START

    for position in results:
        distance_travelled += abs(current - position)
        current = position

    print(' -> '.join(map(str, [HEAD_START] + results)))

    print('Distance travelled:', distance_travelled)


def fcfs():
    return list(REQUESTS)


def sstf():
    requests = list(REQUESTS)
    current = HEAD_START
    path = []

    while requests:
        next_request = min(requests, key=lambda request: abs(request - current))

        path.append(next_request)
        requests.remove(next_request)

        current = next_request

    return path


def scan_down():
    path = sorted(REQUESTS)

    next_index = len(REQUESTS)
    for index, request in enumerate(path):
        if request > HEAD_START:
            next_index = index
            break

    return path[:next_index][::-1] + [MIN_CYLINDER] + path[next_index:]


def scan_up():
    path = sorted(REQUESTS)

    next_index = len(REQUESTS)
    for index, request in enumerate(path):
        if request > HEAD_START:
            next_index = index
            break

    return path[next_index:] + [MAX_CYLINDER] + path[:next_index][::-1]


def look_down():
    path = sorted(REQUESTS)

    next_index = len(REQUESTS)
    for index, request in enumerate(path):
        if request > HEAD_START:
            next_index = index
            break

    return path[:next_index][::-1] + path[next_index:]


def look_up():
    path = sorted(REQUESTS)

    next_index = len(REQUESTS)
    for index, request in enumerate(path):
        if request > HEAD_START:
            next_index = index
            break

    return path[next_index:] + path[:next_index][::-1]


def cscan_down():
    path = sorted(REQUESTS)

    next_index = len(REQUESTS)
    for index, request in enumerate(path):
        if request > HEAD_START:
            next_index = index
            break

    return path[:next_index][::-1] + [MIN_CYLINDER] + [MAX_CYLINDER] + path[next_index:][::-1]


def cscan_up():
    path = sorted(REQUESTS)

    next_index = len(REQUESTS)
    for index, request in enumerate(path):
        if request > HEAD_START:
            next_index = index
            break

    return path[next_index:] + [MAX_CYLINDER] + [MIN_CYLINDER] + path[:next_index]


def clook_down():
    path = sorted(REQUESTS)

    next_index = len(REQUESTS)
    for index, request in enumerate(path):
        if request > HEAD_START:
            next_index = index
            break

    return path[:next_index][::-1] + path[next_index:][::-1]


def clook_up():
    path = sorted(REQUESTS)

    next_index = len(REQUESTS)
    for index, request in enumerate(path):
        if request > HEAD_START:
            next_index = index
            break

    return path[next_index:] + path[:next_index]


if __name__ == '__main__':
    print('FCFS:', end=' ')
    print_results(fcfs())

    print('\nSSTF:', end=' ')
    print_results(sstf())

    if DIRECTION != Direction.UP:
        print('\nSCAN DOWN:', end=' ')
        print_results(scan_down())

        print('\nLOOK DOWN:', end=' ')
        print_results(look_down())

        print('\nCSCAN DOWN:', end=' ')
        print_results(cscan_down())

        print('\nCLOOK DOWN:', end=' ')
        print_results(clook_down())

    if DIRECTION != Direction.DOWN:
        print('\nSCAN UP:', end=' ')
        print_results(scan_up())

        print('\nLOOK UP:', end=' ')
        print_results(look_up())

        print('\nCSCAN UP:', end=' ')
        print_results(cscan_up())

        print('\nCLOOK UP:', end=' ')
        print_results(clook_up())
