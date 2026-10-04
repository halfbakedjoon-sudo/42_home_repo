#!/usr/bin/env python3
from parsing import parsing
from maze_output import maze_print
from maze import MazeGenerator
import time
import sys

if __name__ == "__main__":
    print("\033[H\033[J", end="")
    # print("\033[48;5;44m", end="")
    config = parsing()
    # print(config)
    maze = MazeGenerator()
    maze_base: dict[tuple[int, int], MazeGenerator.Cell] = {}
    path: list[tuple[int, int]] = []
    maze_base = maze.maze_initialize(config)
    # print(maze_base.keys())
    maze_print(config.width, config.height, maze_base, config.entry,
               config.exit)
    x, y = 2, 3
    coor = x, y
    path = maze.maze_gen(maze_base, config, (coor))
    for item in path:
        x1, y1 = item
        print(f"\033[{y1 * 2 + 2};{x1 * 4 + 3}H■", end="", flush=True)
        sys.stdout.flush()
        print(f"\033[{config.height * 2 + 1};1H")
        print("\033[0m", end="")
        time.sleep(0.5)
