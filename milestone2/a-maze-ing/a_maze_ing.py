#!/usr/bin/env python3
from parsing import parsing


if __name__ == "__main__":
    config = parsing()
    print(config)
    w: dict[tuple[int, int], str] = {}
    for n in range(config.height * 2 + 1):
        for i in range(config.width * 2 + 1):
            coor: tuple[int, int] = (n, i)
            w[coor] = "╬\033[0m"

    for n in range(config.height * 2 + 1):
        for i in range(config.width * 2 + 1):
            coor2: tuple[int, int] = (n, i)
            if n == 0:
                if n == 0 and i == 0:
                    w[coor2] = "╔\033[0m"
                elif n == 0 and i == config.width * 2:
                    w[coor2] = "╗\033[0m"
                elif i % 2 == 0:
                    w[coor2] = "╦\033[0m"
                elif n == 0:
                    w[coor2] = "═══\033[0m"
            elif n != 0 and n != config.height * 2:
                if n % 2 == 1:
                    if i % 2 == 0:
                        w[coor2] = "║\033[0m"
                    elif i % 2 == 1:
                        w[coor2] = "   \033[0m"
                if n % 2 == 0:
                    if i == 0:
                        w[coor2] = "╠\033[0m"
                    elif i == config.width * 2:
                        w[coor2] = "╣\033[0m"
                    elif i % 2 == 1:
                        w[coor2] = "═══\033[0m"
            elif n == config.height * 2:
                if n == config.height * 2 and i == 0:
                    w[coor2] = "╚\033[0m"
                elif n == config.height * 2 and i == config.width * 2:
                    w[coor2] = "╝\033[0m"
                elif i % 2 == 0:
                    w[coor2] = "╩\033[0m"
                elif n == config.height * 2:
                    w[coor2] = "═══\033[0m"
    x, y = config.entry
    w[y * 2 + 1, x * 2 + 1] = " ■ \033[0m"
    x, y = config.exit
    w[y * 2 + 1, x * 2 + 1] = " ■ \033[0m"

    print(w.keys())
    for h in range(config.height * 2 + 1):
        wall_list: list[str] = []
        for r in range(config.width * 2 + 1):
            wall_list.append(w[h, r])
        wall = "".join(wall_list)
        print(wall)
