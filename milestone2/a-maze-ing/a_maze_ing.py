#!/usr/bin/env python3
from solver import bfs_solver, dfs_solver
from parsing import parsing
from maze_output import maze_print
from maze import MazeGenerator
import time
import sys
import random

if __name__ == "__main__":
    seed: int | float | str = random.randint(0, 9999)
    # seed: int | float | str = 42
    config = parsing()
    while True:
        print("\033[H\033[J", end="")
        random.seed(seed)
        maze = MazeGenerator()
        maze_base: dict[tuple[int, int], MazeGenerator.Cell] = {}
        path: list[tuple[int, int]] = []
        maze_base = maze.maze_initialize(config)
        maze_print(config.width, config.height, maze_base, config.entry,
                   config.exit)
        maze.maze_gen_42(maze_base, config)
    
        if config.perfect:
            maze.maze_gen_perf(maze_base, config)
        else:
            maze.maze_gen(maze_base, config)

        entry_x, entry_y = config.entry
        exit_x, exit_y = config.exit
        print(f"\033[{entry_y * 2 + 2};{entry_x * 4 + 2}H\033[31m▐█▌\033[0m")
        print(f"\033[{exit_y * 2 + 2};{exit_x * 4 + 2}H\033[32m▐█▌\033[0m",
              end="")
        real_path: list[tuple[int, int]]
        if config.solver == "BFS":
            real_path = bfs_solver(maze_base, config)
        elif config.solver == "DFS":
            real_path = dfs_solver(maze_base, config)
        else:
            real_path = bfs_solver(maze_base, config)

        print(f"\033[{entry_y * 2 + 2};{entry_x * 4 + 2}H\033[31m▐█▌\033[0m")
        print(f"\033[{exit_y * 2 + 2};{exit_x * 4 + 2}H\033[32m▐█▌\033[0m",
              end="")
        print(f"\033[{config.height * 2 + 2};1H")

        with open(f"{config.output_file}", "w") as fd:
            for y in range(config.height):
                output: list[str] = []
                for x in range(config.width):
                    value: int = 0
                    hex: str = "0123456789abcdef"
                    if maze_base[x, y].news.up:
                        value += 1
                    if maze_base[x, y].news.right:
                        value += 2
                    if maze_base[x, y].news.down:
                        value += 4
                    if maze_base[x, y].news.left:
                        value += 8
                    output.append(f"{hex[value]}")
                output1 = "".join(output)
                fd.write(output1 + "\n")

            fd.write("\n")
            fd.write(f"{entry_x},{entry_y}\n")
            fd.write(f"{exit_x},{exit_y}\n")

            directions: list[str] = []
            coor: tuple[int, int] = (exit_x, exit_y)
            while coor != (entry_x, entry_y):
                x, y = coor
                x2, y2 = maze_base[coor].fr
                if x2 > x:
                    directions.insert(0, "W")
                elif x2 < x:
                    directions.insert(0, "E")
                elif y2 > y:
                    directions.insert(0, "N")
                elif y2 < y:
                    directions.insert(0, "S")
                coor = maze_base[coor].fr

            direction_output = "".join(directions)
            fd.write(direction_output + "\n")

        # print(f"1. Seed number: {seed}\n"
        #       "   Enter '1' to change seed.")
        # maze_type = "Perfect" if config.perfect else "Imperfect"
        # print(f"2. Maze type: {maze_type}\n"
        #       "   Enter '2' to change type.")
        # print(f"3. Speed: {config.speed}\n"
        #       "   Enter '3' to change speed")
        # print("4. Color scheme:\n"
        #       "   Press '4' to change color")
        # print(f"5. Solver: {config.solver}\n"
        #       "   Enter '5' to change solver")
        # print("6. Press 6 to toggle path finder")
        # path_mode: int = 1
        # print("Press enter to generate same maze again")
        # print("Enter 'random' to generate random maze")
        # print("Enter 'exit' to quit")

        path_mode: int = 1
        while True:
            print(f"\033[{config.height * 2 + 2};1H\033[J", end="")
            print(f"1. Seed number: {seed}\n"
                "   Enter '1' to change seed.")
            maze_type = "Perfect" if config.perfect else "Imperfect"
            print(f"2. Maze type: {maze_type}\n"
                "   Enter '2' to change type.")
            print(f"3. Speed: {config.speed}\n"
                "   Enter '3' to change speed")
            print("4. Color scheme:\n"
                "   Press '4' to change color")
            print(f"5. Solver: {config.solver}\n"
                "   Enter '5' to change solver")
            print("6. Press 6 to toggle path finder")
            print("Press enter to generate same maze again")
            print("Enter 'random' to generate random maze")
            print("Enter 'exit' to quit")
            print(f"\033[{config.height * 2 + 17};1H\033[J", end="")
            user_input1: str = input("Input: ")
            if not user_input1:
                break
            elif user_input1.lower() == "random":
                seed = random.randint(0, 9999)
                break
            elif user_input1 == "1":
                seed = input("Please enter seed: ")
                break
            elif user_input1 == "2":
                while True:
                    print(f"\033[{config.height * 2 + 17};1H\033[J", end="")
                    input_type = input("Please enter type (1 for perfect,"
                                       "0 for imperfect)\n"
                                       "Input 'back' to go up one level: \n")
                    if input_type == "1" or input_type == "0":
                        config.perfect = bool(int(input_type))
                        break
                    elif input_type.lower() == "back":
                        break
                    else:
                        continue
                if input_type == "1" or input_type == "0":
                    break
                else:
                    continue
            elif user_input1 == "3":
                while True:
                    print(f"\033[{config.height * 2 + 17};1H\033[J", end="")
                    input_speed = input("Please enter desired speed: ")
                    try:
                        config.speed = float(input_speed)
                        break
                    except ValueError:
                        print("That's not a valid number, try again.")
                break
            elif user_input1 == "4":
                pass
            elif user_input1 == "5":
                while True:
                    print(f"\033[{config.height * 2 + 17};1H\033[J", end="")
                    input_solver = input("Please enter solver 'BFS' 'DFS': ")
                    if input_solver.upper() not in ["BFS", "DFS"]:
                        print("Try again")
                        continue
                    else:
                        config.solver = input_solver.upper()
                        break
                break
            elif user_input1 == "6":
                if path_mode == 1:
                    path_mode = 0
                    print("\033[H", end="")
                    maze_print(config.width, config.height, maze_base, config.entry,
                               config.exit)
                    print(f"\033[{entry_y * 2 + 2};{entry_x * 4 + 2}H\033[31m▐█▌\033[0m")
                    print(f"\033[{exit_y * 2 + 2};{exit_x * 4 + 2}H\033[32m▐█▌\033[0m",
                          end="")
                elif path_mode == 0:
                    path_mode = 1
                    print("\033[H", end="")
                    maze_print(config.width, config.height, maze_base, config.entry,
                               config.exit)
                    for coor in real_path:
                        x, y = coor
                        print(f"\033[{y * 2 + 2};{x * 4 + 3}H\033[94m•\033[0m")
                    print(f"\033[{entry_y * 2 + 2};{entry_x * 4 + 2}H\033[31m▐█▌\033[0m")
                    print(f"\033[{exit_y * 2 + 2};{exit_x * 4 + 2}H\033[32m▐█▌\033[0m",
                          end="")
            elif user_input1.lower() == "exit":
                break
            else:
                continue
        if user_input1.lower() == "exit":
            break
