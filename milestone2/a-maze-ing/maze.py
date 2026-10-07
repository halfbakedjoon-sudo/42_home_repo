from parsing import Config
import random
import sys
import time
import maze_output


class MazeGenerator:
    class Cell:
        class NEWS:
            def __init__(self) -> None:
                self.up: bool = False
                self.down: bool = False
                self.right: bool = False
                self.left: bool = False

            def __iter__(self):
                return iter((self.up, self.down, self.left, self.right))

        def __init__(self) -> None:
            self.news = self.NEWS()
            self.visited: bool = False
            self.path: bool = False
            self.fr: tuple[int, int] = (-1, -1)
            self.real: bool = False
            self.graphic: bool = False

    @staticmethod
    def maze_initialize(config: Config) -> dict[tuple[int, int], Cell]:
        maze = MazeGenerator()
        maze_base: dict[tuple[int, int], MazeGenerator.Cell] = {}
        height: int = config.height
        width: int = config.width
        for h in range(height):
            for w in range(width):
                coor: tuple[int, int] = (w, h)
                cell = maze.Cell()
                if h == 0:
                    cell.news.up = True
                if h == height - 1:
                    cell.news.down = True
                if w == 0:
                    cell.news.left = True
                if w == width - 1:
                    cell.news.right = True
                maze_base[coor] = cell
        return maze_base    

    @staticmethod
    def maze_gen(maze_base: dict[tuple[int, int], Cell], config: Config):
        x, y = (random.randint(0, config.width - 1),
                random.randint(0, config.height - 1))
        start = 0
        coor = x, y
        path: list[tuple[int, int]] = []
        path.append(coor)
        directions: list[str] = ["up", "down", "left", "right"]
        while True:
            direction: str = ""
            start = len(path)
            if not path:
                break
            x, y = path[-1]
            maze_base[x, y].visited = True
            # print(path)
            if x == 0 and y == 0:
                if (maze_base[x + 1, y].visited and
                    maze_base[x, y + 1].visited):
                    path.pop(-1)
                    continue
                else:
                    direction = random.choice(["down", "right"])
            elif x == config.width - 1 and y == 0:
                if (maze_base[x - 1, y].visited and
                    maze_base[x, y + 1].visited):
                    path.pop(-1)
                    continue
                else:
                    direction = random.choice(["down", "left"])
            elif x == 0 and y == config.height - 1:
                if (maze_base[x + 1, y].visited and
                    maze_base[x, y - 1].visited):
                    path.pop(-1)
                    continue
                else:
                    direction = random.choice(["up", "right"])
            elif x == config.width - 1 and y == config.height - 1:
                if (maze_base[x - 1, y].visited and
                    maze_base[x, y - 1].visited):
                    path.pop(-1)
                    continue
                else:
                    direction = random.choice(["up", "left"])
            elif x == 0:
                if (maze_base[x, y - 1].visited and
                    maze_base[x, y + 1].visited and
                    maze_base[x + 1, y].visited):
                    path.pop(-1)
                    continue
                else:
                    direction = random.choice(["down", "up", "right"])
            elif x == config.width - 1:
                if (maze_base[x, y + 1].visited and
                    maze_base[x, y - 1].visited and
                    maze_base[x - 1, y].visited):
                    path.pop(-1)
                    continue
                else:
                    direction = random.choice(["down", "left", "up"])
            elif y == 0:
                if (maze_base[x, y + 1].visited and
                    maze_base[x - 1, y].visited and
                    maze_base[x + 1, y].visited):
                    path.pop(-1)
                    continue
                else:
                    direction = random.choice(["down", "right", "left"])
            elif y == config.height - 1:
                if (maze_base[x, y - 1].visited and
                    maze_base[x - 1, y].visited and
                    maze_base[x + 1, y].visited):
                    path.pop(-1)
                    continue
                else:
                    direction = random.choice(["up", "right", "left"])
            else:
                if (maze_base[x, y - 1].visited and
                    maze_base[x, y + 1].visited and
                    maze_base[x - 1, y].visited and
                    maze_base[x + 1, y].visited):
                    path.pop(-1)
                    continue
                else:
                    direction = random.choice(directions)

            if direction == "left":
                if (x - 1, y) in maze_base:
                    if maze_base[x - 1, y].visited:
                        continue
                    else:
                        go_or_no = 1
                elif maze_base[x, y].news.right:
                    continue
                else:
                    go_or_no = 1
                if go_or_no == 1:
                    if x != 0:
                        maze_base[x, y].news.left = False
                        maze_base[x - 1, y].news.right = False
                    if y != 0:
                        if not maze_base[x, y - 1].visited:
                            maze_base[x, y].news.up = True
                            maze_base[x, y - 1].news.down = True
                    if y != config.height - 1:
                        if not maze_base[x, y + 1].visited:
                            maze_base[x, y].news.down = True
                            maze_base[x, y + 1].news.up = True
                    print("\033[H", end="")
                    maze_output.maze_print(config.width, config.height,
                                           maze_base, config.entry,
                                           config.exit)
                    coor = (x - 1), y
                    path.append(coor)

            elif direction == "right":
                if (x + 1, y) in maze_base:
                    if maze_base[x + 1, y].visited:
                        continue
                    else:
                        go_or_no = 1
                elif maze_base[x, y].news.right:
                    continue
                else:
                    go_or_no = 1
                if go_or_no == 1:
                    if x != config.width - 1:
                        maze_base[x, y].news.right = False
                        maze_base[x + 1, y].news.left = False
                    if y != 0:
                        if not maze_base[x, y - 1].visited:
                            maze_base[x, y].news.up = True
                            maze_base[x, y - 1].news.down = True
                    if y != config.height - 1:
                        if not maze_base[x, y + 1].visited:
                            maze_base[x, y].news.down = True
                            maze_base[x, y + 1].news.up = True
                    print("\033[H", end="")
                    maze_output.maze_print(config.width, config.height,
                                           maze_base, config.entry,
                                           config.exit)
                    coor = (x + 1), y
                    path.append(coor)

            elif direction == "up":
                if (x, y - 1) in maze_base:
                    if maze_base[x, y - 1].visited:
                        continue
                    else:
                        go_or_no = 1
                elif maze_base[x, y].news.up:
                    continue
                else:
                    go_or_no = 1
                if go_or_no == 1:
                    if y != 0:
                        maze_base[x, y].news.up = False
                        maze_base[x, y - 1].news.down = False
                    if x != 0:
                        if not maze_base[x - 1, y].visited:
                            maze_base[x, y].news.left = True
                            maze_base[x - 1, y].news.right = True
                    if x != config.width - 1:
                        if not maze_base[x + 1, y].visited:
                            maze_base[x, y].news.right = True
                            maze_base[x + 1, y].news.left = True
                    print("\033[H", end="")
                    maze_output.maze_print(config.width, config.height,
                                           maze_base, config.entry,
                                           config.exit)
                    coor = x, (y - 1)
                    path.append(coor)

            elif direction == "down":
                if (x, y + 1) in maze_base:
                    if maze_base[x, y + 1].visited:
                        continue
                    else:
                        go_or_no = 1
                elif maze_base[x, y].news.down:
                    continue
                else:
                    go_or_no = 1
                if go_or_no == 1:
                    if y != config.height - 1:
                        maze_base[x, y].news.down = False
                        maze_base[x, y + 1].news.up = False
                    if x != 0:
                        if not maze_base[x - 1, y].visited:
                            maze_base[x, y].news.left = True
                            maze_base[x - 1, y].news.right = True
                    if x != config.width - 1:
                        if not maze_base[x + 1, y].visited:
                            maze_base[x, y].news.right = True
                            maze_base[x + 1, y].news.left = True
                    print("\033[H", end="")
                    maze_output.maze_print(config.width, config.height,
                                           maze_base, config.entry,
                                           config.exit)
                    coor = x, (y + 1)
                    path.append(coor)

            if start != len(path):
                x1, y1 = path[-1]
                print(f"\033[{y1 * 2 + 2};{x1 * 4 + 2}H▐█▌")

        print("\033[H\033[J", end="")
        maze_output.maze_print(config.width, config.height, maze_base,
                               config.entry, config.exit)

        # for y in range(config.height):
        #     for x in range(config.width):
        #         wall_num: int = 0
        #         for wall in maze_base[x, y].news:
        #             if wall:
        #                 wall_num += 1
        #         if wall_num > 2:
        #             if (x != 0 and x != config.width and
        #                 y != 0 and y != config.height):
        #                 if (maze_base[x, y].news.up and
        #                     maze_base[x, y].news.down and
        #                     maze_base[x, y].news.left):
        #                     maze_base[x, y].news.up = True
        #                     maze_base[x, y - 1].news.down = True

        #         print("\033[H", end="")
        #         maze_output.maze_print(config.width, config.height,
        #                                maze_base, config.entry,
        #                                config.exit)


    @staticmethod
    def maze_gen_perf(maze_base: dict[tuple[int, int], Cell], config: Config):
        x, y = (random.randint(0, config.width - 1),
                random.randint(0, config.height - 1))
        start = 0
        coor = x, y
        path: list[tuple[int, int]] = []
        path.append(coor)
        directions: list[str] = ["up", "down", "left", "right"]
        while True:
            direction: str = ""
            start = len(path)
            if not path:
                break
            x, y = path[-1]
            maze_base[x, y].visited = True
            # print(path)
            if x == 0 and y == 0:
                if (maze_base[x + 1, y].visited and
                    maze_base[x, y + 1].visited):
                    path.pop(-1)
                    continue
                else:
                    direction = random.choice(["down", "right"])
            elif x == config.width - 1 and y == 0:
                if (maze_base[x - 1, y].visited and
                    maze_base[x, y + 1].visited):
                    path.pop(-1)
                    continue
                else:
                    direction = random.choice(["down", "left"])
            elif x == 0 and y == config.height - 1:
                if (maze_base[x + 1, y].visited and
                    maze_base[x, y - 1].visited):
                    path.pop(-1)
                    continue
                else:
                    direction = random.choice(["up", "right"])
            elif x == config.width - 1 and y == config.height - 1:
                if (maze_base[x - 1, y].visited and
                    maze_base[x, y - 1].visited):
                    path.pop(-1)
                    continue
                else:
                    direction = random.choice(["up", "left"])
            elif x == 0:
                if (maze_base[x, y - 1].visited and
                    maze_base[x, y + 1].visited and
                    maze_base[x + 1, y].visited):
                    path.pop(-1)
                    continue
                else:
                    direction = random.choice(["down", "up", "right"])
            elif x == config.width - 1:
                if (maze_base[x, y + 1].visited and
                    maze_base[x, y - 1].visited and
                    maze_base[x - 1, y].visited):
                    path.pop(-1)
                    continue
                else:
                    direction = random.choice(["down", "left", "up"])
            elif y == 0:
                if (maze_base[x, y + 1].visited and
                    maze_base[x - 1, y].visited and
                    maze_base[x + 1, y].visited):
                    path.pop(-1)
                    continue
                else:
                    direction = random.choice(["down", "right", "left"])
            elif y == config.height - 1:
                if (maze_base[x, y - 1].visited and
                    maze_base[x - 1, y].visited and
                    maze_base[x + 1, y].visited):
                    path.pop(-1)
                    continue
                else:
                    direction = random.choice(["up", "right", "left"])
            else:
                if (maze_base[x, y - 1].visited and
                    maze_base[x, y + 1].visited and
                    maze_base[x - 1, y].visited and
                    maze_base[x + 1, y].visited):
                    path.pop(-1)
                    continue
                else:
                    direction = random.choice(directions)

            if direction == "left":
                if (x - 1, y) in maze_base:
                    if maze_base[x - 1, y].visited:
                        continue
                    else:
                        go_or_no = 1
                elif maze_base[x, y].news.right:
                    continue
                else:
                    go_or_no = 1
                if go_or_no == 1:
                    if x != 0:
                        maze_base[x, y].news.left = False
                        maze_base[x - 1, y].news.right = False
                    if x != config.width - 1:
                        if not maze_base[x + 1, y].visited:
                            maze_base[x, y].news.right = True
                            maze_base[x + 1, y].news.left = True
                    if y != 0:
                        if not maze_base[x, y - 1].visited:
                            maze_base[x, y].news.up = True
                            maze_base[x, y - 1].news.down = True
                    if y != config.height - 1:
                        if not maze_base[x, y + 1].visited:
                            maze_base[x, y].news.down = True
                            maze_base[x, y + 1].news.up = True
                    print("\033[H", end="")
                    maze_output.maze_print(config.width, config.height,
                                           maze_base, config.entry,
                                           config.exit)
                    coor = (x - 1), y
                    path.append(coor)

            elif direction == "right":
                if (x + 1, y) in maze_base:
                    if maze_base[x + 1, y].visited:
                        continue
                    else:
                        go_or_no = 1
                elif maze_base[x, y].news.right:
                    continue
                else:
                    go_or_no = 1
                if go_or_no == 1:
                    if x != 0:
                        if not maze_base[x - 1, y].visited:
                            maze_base[x, y].news.left = True
                            maze_base[x - 1, y].news.right = True
                    if x != config.width - 1:
                        maze_base[x, y].news.right = False
                        maze_base[x + 1, y].news.left = False
                    if y != 0:
                        if not maze_base[x, y - 1].visited:
                            maze_base[x, y].news.up = True
                            maze_base[x, y - 1].news.down = True
                    if y != config.height - 1:
                        if not maze_base[x, y + 1].visited:
                            maze_base[x, y].news.down = True
                            maze_base[x, y + 1].news.up = True
                    print("\033[H", end="")
                    maze_output.maze_print(config.width, config.height,
                                           maze_base, config.entry,
                                           config.exit)
                    coor = (x + 1), y
                    path.append(coor)

            elif direction == "up":
                if (x, y - 1) in maze_base:
                    if maze_base[x, y - 1].visited:
                        continue
                    else:
                        go_or_no = 1
                elif maze_base[x, y].news.up:
                    continue
                else:
                    go_or_no = 1
                if go_or_no == 1:
                    if y != 0:
                        maze_base[x, y].news.up = False
                        maze_base[x, y - 1].news.down = False
                    if y != config.height - 1:
                        if not maze_base[x, y + 1].visited:
                            maze_base[x, y].news.down = True
                            maze_base[x, y + 1].news.up = True
                    if x != 0:
                        if not maze_base[x - 1, y].visited:
                            maze_base[x, y].news.left = True
                            maze_base[x - 1, y].news.right = True
                    if x != config.width - 1:
                        if not maze_base[x + 1, y].visited:
                            maze_base[x, y].news.right = True
                            maze_base[x + 1, y].news.left = True
                    print("\033[H", end="")
                    maze_output.maze_print(config.width, config.height,
                                           maze_base, config.entry,
                                           config.exit)
                    coor = x, (y - 1)
                    path.append(coor)

            elif direction == "down":
                if (x, y + 1) in maze_base:
                    if maze_base[x, y + 1].visited:
                        continue
                    else:
                        go_or_no = 1
                elif maze_base[x, y].news.down:
                    continue
                else:
                    go_or_no = 1
                if go_or_no == 1:
                    if y != 0:
                        if not maze_base[x, y - 1].visited:
                            maze_base[x, y].news.up = True
                            maze_base[x, y - 1].news.down = True
                    if y != config.height - 1:
                        maze_base[x, y].news.down = False
                        maze_base[x, y + 1].news.up = False
                    if x != 0:
                        if not maze_base[x - 1, y].visited:
                            maze_base[x, y].news.left = True
                            maze_base[x - 1, y].news.right = True
                    if x != config.width - 1:
                        if not maze_base[x + 1, y].visited:
                            maze_base[x, y].news.right = True
                            maze_base[x + 1, y].news.left = True
                    print("\033[H", end="")
                    maze_output.maze_print(config.width, config.height,
                                           maze_base, config.entry,
                                           config.exit)
                    coor = x, (y + 1)
                    path.append(coor)

            if start != len(path):
                x1, y1 = path[-1]
                print(f"\033[{y1 * 2 + 2};{x1 * 4 + 2}H▐█▌")
                time.sleep(config.speed)
                # buf = []
                # for item in path:  # full path, not path[start:]
                #     x1, y1 = item
                #     buf.append(f"\033[{y1 * 2 + 2};{x1 * 4 + 2}H▐█▌")
                # buf.append(f"\033[{config.height * 2 + 1};1H")
                # buf.append("\033[0m")
                # print("".join(buf), end="", flush=True)
                # time.sleep(config.speed)

        print("\033[H\033[J", end="")
        maze_output.maze_print(config.width, config.height, maze_base,
                               config.entry, config.exit)

    @staticmethod
    def maze_convert_42(maze_base: dict[tuple[int, int], Cell], 
                        coor: tuple[int, int]):
        x, y = coor
        maze_base[x, y].visited = True
        maze_base[x, y].graphic = True
        maze_base[x, y].news.up = True
        maze_base[x, y].news.down = True
        maze_base[x, y].news.left = True
        maze_base[x, y].news.right = True

        maze_base[x, y - 1].news.down = True
        maze_base[x, y + 1].news.up = True
        maze_base[x - 1, y].news.right = True
        maze_base[x + 1, y].news.left = True

    @staticmethod
    def maze_gen_42(maze_base: dict[tuple[int, int], Cell], config: Config):
        if config.width > 8 and config.height > 6:
            x: int = round(config.width / 2 - 1) - 3
            y: int = round(config.height / 2 - 1) - 2
            coor_42: list[tuple[int, int]] = \
                [(x, y), (x+4, y), (x+5, y), (x+6, y),
                 (x, y+1), (x+6, y+1),
                 (x, y+2), (x+1, y+2), (x+2, y+2), (x+4, y+2), (x+5, y+2),
                 (x+6, y+2),
                 (x+2, y+3), (x+4, y+3),
                 (x+2, y+4), (x+4, y+4), (x+5, y+4), (x+6, y+4),]
            for coor in coor_42:
                x1, y1 = coor
                MazeGenerator.maze_convert_42(maze_base, (x1, y1))
                print("\033[H\033[J", end="")
                maze_output.maze_print(config.width, config.height,
                                       maze_base, config.entry,
                                       config.exit)
        else:
            return
