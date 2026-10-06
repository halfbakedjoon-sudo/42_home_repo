from parsing import Config
from maze_output import maze_print
from maze import MazeGenerator
import time
import sys
import random


def solver(maze_base: dict[tuple[int, int], MazeGenerator.Cell], config: Config):
    start = config.entry
    exit = config.exit
    path: list[tuple[int, int]] = []
    
