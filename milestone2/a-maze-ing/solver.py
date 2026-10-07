from parsing import Config
from maze_output import maze_print
from maze import MazeGenerator
import time
import sys
import random


def maze_solver(maze_base: dict[tuple[int, int], MazeGenerator.Cell],
                config: Config):
    start = config.entry
    exit = config.exit
    exit_x, exit_y = exit
    path: list[tuple[int, int]] = []
    path.append(start)

    while True:
        x, y = path.pop(0)
        maze_base[(x, y)].path = True
        if not maze_base[(x, y)].news.up:
            if not maze_base[(x, y-1)].path:
                if (x, y-1) not in path:
                    path.append((x, y-1))
                maze_base[(x, y-1)].fr = (x, y)
        if not maze_base[(x, y)].news.down:
            if not maze_base[(x, y+1)].path:
                if (x, y+1) not in path:
                    path.append((x, y+1))
                maze_base[(x, y+1)].fr = (x, y)
        if not maze_base[(x, y)].news.left:
            if not maze_base[(x-1, y)].path:
                if (x-1, y) not in path:
                    path.append((x-1, y))
                maze_base[(x-1, y)].fr = (x, y)
        if not maze_base[(x, y)].news.right:
            if not maze_base[(x+1, y)].path:
                if (x+1, y) not in path:
                    path.append((x+1, y))
                maze_base[(x+1, y)].fr = (x, y)
        if maze_base[exit].path:
            break
        if not (x, y) == start:
            time.sleep(config.speed)
            print(f"\033[{y * 2 + 2};{x * 4 + 3}H\033[93m•\033[0m")

    real_path: list[tuple[int, int]] = []
    real_path.append(exit)
    while True:
        x, y = real_path[0]
        if (x, y) == start or (x, y) == exit:
            next = maze_base[(x, y)].fr
            real_path.insert(0, next)
            continue
        next = maze_base[(x, y)].fr
        if next == config.entry:
            break
        real_path.insert(0, next)

    for coor in real_path:
        time.sleep(config.speed)
        x, y = coor
        print(f"\033[{y * 2 + 2};{x * 4 + 3}H\033[94m•\033[0m")

    print("\033[H", end="")
    maze_print(config.width, config.height, maze_base, config.entry,
               config.exit)

    for coor in real_path:
        x, y = coor
        print(f"\033[{y * 2 + 2};{x * 4 + 3}H\033[94m•\033[0m")


def maze_solver2(maze_base: dict[tuple[int, int], MazeGenerator.Cell],
                 config: Config):
    start = config.entry
    exit = config.exit
    exit_x, exit_y = exit
    path: list[tuple[int, int]] = []
    path.append(start)

    while True:
        x, y = path.pop(0)
        maze_base[(x, y)].path = True
        if not maze_base[(x, y)].news.up:
            if not maze_base[(x, y-1)].path:
                path.insert(0, (x, y-1))
                maze_base[(x, y-1)].fr = (x, y)
        if not maze_base[(x, y)].news.down:
            if not maze_base[(x, y+1)].path:
                path.insert(0, (x, y+1))
                maze_base[(x, y+1)].fr = (x, y)
        if not maze_base[(x, y)].news.left:
            if not maze_base[(x-1, y)].path:
                path.insert(0, (x-1, y))
                maze_base[(x-1, y)].fr = (x, y)
        if not maze_base[(x, y)].news.right:
            if not maze_base[(x+1, y)].path:
                path.insert(0, (x+1, y))
                maze_base[(x+1, y)].fr = (x, y)
        if maze_base[exit].path:
            break
        if not (x, y) == start:
            time.sleep(config.speed)
            print(f"\033[{y * 2 + 2};{x * 4 + 3}H\033[93m•\033[0m")

    real_path: list[tuple[int, int]] = []
    real_path.append(exit)
    while True:
        x, y = real_path[0]
        if (x, y) == start or (x, y) == exit:
            next = maze_base[(x, y)].fr
            real_path.insert(0, next)
            continue
        next = maze_base[(x, y)].fr
        if next == config.entry:
            break
        real_path.insert(0, next)

    for coor in real_path:
        time.sleep(config.speed)
        x, y = coor
        print(f"\033[{y * 2 + 2};{x * 4 + 3}H\033[94m•\033[0m")

    print("\033[H", end="")
    maze_print(config.width, config.height, maze_base, config.entry,
               config.exit)

    for coor in real_path:
        x, y = coor
        print(f"\033[{y * 2 + 2};{x * 4 + 3}H\033[94m•\033[0m")
