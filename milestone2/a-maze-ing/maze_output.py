from maze import MazeGenerator
import time


def first_line(width: int,
               h: int,
               maze_base: dict[tuple[int, int], MazeGenerator.Cell]
               ) -> str:
    wall_list: list[str] = []
    wall_list.append("╔\033[0m")
    for x in range(width):
        if maze_base[x, h].news.up:
            wall_list.append("═══\033[0m")
        else:
            wall_list.append("   \033[0m")
        if x != width - 1:
            if maze_base[x, h].news.right:
                wall_list.append("╦\033[0m")
            else:
                wall_list.append("═\033[0m")
    wall_list.append("╗\033[0m")
    return "".join(wall_list)


def second_line(width: int,
                h: int,
                maze_base: dict[tuple[int, int], MazeGenerator.Cell],
                entry: tuple,
                exit: tuple
                ) -> str:
    wall_list: list[str] = []
    wall_list.append("║\033[0m")
    for x in range(width):
        if x != width - 1:
            if maze_base[x, h].news.right:
                if maze_base[x, h].graphic:
                    wall_list.append("\033[96m███\033[0m║")
                else:
                    wall_list.append("   ║\033[0m")
            else:
                wall_list.append("    \033[0m")
    wall_list.append("   ║\033[0m")
    return "".join(wall_list)


def second_line2(width: int,
                 h: int,
                 maze_base: dict[tuple[int, int], MazeGenerator.Cell]
                 ) -> str:
    wall_list: list[str] = []
    for x in range(width):
        if x == 0:
            first_down = maze_base[x, h].news.down
            if first_down:
                wall_list.append("╠═══\033[0m")
            else:
                wall_list.append("║   \033[0m")
        elif x != width - 1 and x != 0:
            first_down = maze_base[x, h].news.down
            first_left = maze_base[x, h].news.left
            left_down = maze_base[x - 1, h].news.down
            down_left = maze_base[x, h + 1].news.left
            if all((first_down, first_left, left_down, down_left)):
                wall_list.append("╬═══\033[0m")
            elif all((first_down, first_left, left_down)):
                wall_list.append("╩═══\033[0m")
            elif all((first_down, first_left, down_left)):
                wall_list.append("╠═══\033[0m")
            elif all((first_down, left_down, down_left)):
                wall_list.append("╦═══\033[0m")
            elif all((first_left, left_down, down_left)):
                wall_list.append("╣   \033[0m")
            elif all((first_down, first_left)):
                wall_list.append("╚═══\033[0m")
            elif all((first_down, left_down)):
                wall_list.append("════\033[0m")
            elif all((first_down, down_left)):
                wall_list.append("╔═══\033[0m")
            elif all((first_left, left_down)):
                wall_list.append("╝   \033[0m")
            elif all((first_left, down_left)):
                wall_list.append("║   \033[0m")
            elif all((left_down, down_left)):
                wall_list.append("╗   \033[0m")
            elif first_down:
                wall_list.append(" ═══\033[0m")
            else:
                wall_list.append("    \033[0m")
        elif x == width - 1:
            first_down = maze_base[x, h].news.down
            first_left = maze_base[x, h].news.left
            left_down = maze_base[x - 1, h].news.down
            down_left = maze_base[x, h + 1].news.left
            if all((first_down, first_left, left_down, down_left)):
                wall_list.append("╬═══╣\033[0m")
            elif all((first_down, first_left, left_down)):
                wall_list.append("╩═══╣\033[0m")
            elif all((first_down, first_left, down_left)):
                wall_list.append("╠═══╣\033[0m")
            elif all((first_down, left_down, down_left)):
                wall_list.append("╦═══╣\033[0m")
            elif all((first_left, left_down, down_left)):
                wall_list.append("╣   ║\033[0m")
            elif all((first_down, first_left)):
                wall_list.append("╚═══╣\033[0m")
            elif all((first_down, left_down)):
                wall_list.append("════╣\033[0m")
            elif all((first_down, down_left)):
                wall_list.append("╔═══╣\033[0m")
            elif all((first_left, left_down)):
                wall_list.append("╝   ║\033[0m")
            elif all((first_left, down_left)):
                wall_list.append("║   ║\033[0m")
            elif all((left_down, down_left)):
                wall_list.append("╗   ║\033[0m")
            else:
                wall_list.append("    ║\033[0m")
    return "".join(wall_list)


def last_line(width: int,
              h: int,
              maze_base: dict[tuple[int, int], MazeGenerator.Cell]
              ) -> str:
    wall_list: list[str] = []
    wall_list.append("╚\033[0m")
    for x in range(width):
        if maze_base[x, h].news.down:
            wall_list.append("═══\033[0m")
        else:
            wall_list.append("   \033[0m")
        if x != width - 1:
            if maze_base[x, h].news.right:
                wall_list.append("╩\033[0m")
            else:
                wall_list.append("═\033[0m")
    wall_list.append("╝\033[0m")
    return "".join(wall_list)


def maze_print(width: int,
               height: int,
               maze_base: dict[tuple[int, int], MazeGenerator.Cell],
               entry: tuple,
               exit: tuple):
    # time.sleep(0.01)
    print(first_line(width, 0, maze_base))
    for y in range(height):
        print(second_line(width, y, maze_base, entry, exit))
        if y != height - 1:
            print(second_line2(width, y, maze_base))
    print(last_line(width, height - 1, maze_base))
