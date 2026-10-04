from parsing import Config
import random


class MazeGenerator:
    class Cell:
        class NEWS:
            def __init__(self) -> None:
                self.north: bool = False
                self.south: bool = False
                self.east: bool = False
                self.west: bool = False

        def __init__(self) -> None:
            self.news = self.NEWS()
            self.visited: bool = False

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
                    cell.news.north = True
                if h == height - 1:
                    cell.news.south = True
                if w == 0:
                    cell.news.west = True
                if w == width - 1:
                    cell.news.east = True
                maze_base[coor] = cell
        return maze_base

    @staticmethod
    def maze_gen(
        maze_base: dict[tuple[int, int], Cell], config: Config, coor: tuple[int, int]
       ) -> list[tuple[int, int]]:
        # x, y = (random.randint(0, config.height - 1),
        #         random.randint(0, config.width - 1))
        path: list[tuple[int, int]] = []
        path.append(coor)
        directions: list[str] = ["up", "down", "left", "right"]
        while True:
            direction = random.choice(directions)
            x, y = coor
            if direction == "left":
                if maze_base[x, y].news.west:
                    continue
                if not maze_base[x, y - 1].visited:
                    maze_base[x, y].news.north = True
                    maze_base[x, y - 1].news.south = True
                if not maze_base[x, y + 1].visited:
                    maze_base[x, y].news.south = True
                    maze_base[x, y + 1].news.north = True
                maze_base[x, y].visited = True
                print("\033[H\033[J", end="")
                from maze_output import maze_print
                maze_print(config.width, config.height, maze_base,
                           config.entry, config.exit)
                if x != 0:
                    coor = (x - 1), y
                path.append(coor)
                break
            if direction == "right":
                if maze_base[x, y].news.east:
                    continue
                if not maze_base[x, y - 1].visited:
                    maze_base[x, y].news.north = True
                    maze_base[x, y - 1].news.south = True
                if not maze_base[x, y + 1].visited:
                    maze_base[x, y].news.south = True
                    maze_base[x, y + 1].news.north = True
                maze_base[x, y].visited = True
                print("\033[H\033[J", end="")
                from maze_output import maze_print
                maze_print(config.width, config.height, maze_base,
                           config.entry, config.exit)
                if x != 0:
                    coor = (x + 1), y
                path.append(coor)
                break
        return path
