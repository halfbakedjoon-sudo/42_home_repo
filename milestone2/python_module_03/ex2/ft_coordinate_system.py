#!/usr/bin/env python3
import math


class InvalidError(Exception):
    def __init__(self, message: str = "Invalid syntax") -> None:
        super().__init__(message)


def check_len(tuple_string: list[str]) -> None:
    if len(tuple_string) != 3:
        raise InvalidError


def coor_cal(pos1: tuple[float, float, float],
             pos2: tuple[float, float, float]) -> float:
    d_diff = math.sqrt((pos2[0]-pos1[0])**2 +
                       (pos2[1]-pos1[1])**2 +
                       (pos2[2]-pos1[2])**2)
    return d_diff


def get_player_pos() -> None:
    print("=== Game Coordinate System ===")
    print("\nGet a first set of coordinates")
    while True:
        raw_position1 = input("Enter new coordinates as floats in format "
                              "'x,y,z': ")
        split_position1 = raw_position1.split(",")
        try:
            check_len(split_position1)
            list_position1 = []
            for value in split_position1:
                list_position1.append(float(value))
            x, y, z = list_position1
            position1: tuple[float, float, float] = (x, y, z)
        except ValueError as e:
            print(f"Error on parameter '{value}': {e}")
            continue
        except InvalidError as e:
            print(f"{e}")
            continue
        break

    print(f"Got a first tuple: {position1}")
    print(f"It includes: X={position1[0]}, Y={position1[1]}, Z={position1[2]}")
    t = (0.0, 0.0, 0.0)
    d1 = coor_cal(position1, t)
    print(f"Distance to center: {round(d1, 4)}")

    print("\nGet a second set of coordinates")
    while True:
        raw_position2 = input("Enter new coordinates as floats in format "
                              "'x,y,z': ")
        split_position2 = raw_position2.split(",")
        try:
            check_len(split_position1)
            list_position2 = []
            for value in split_position2:
                list_position2.append(float(value))
            x, y, z = list_position2
            position2: tuple[float, float, float] = (x, y, z)
        except ValueError as e:
            print(f"Error on parameter '{value}': {e}")
            continue
        except InvalidError as e:
            print(f"{e}")
            continue
        break
    d2 = coor_cal(position2, position1)
    print(f"Distance between the 2 sets of coordinates: {round(d2, 4)}")


if __name__ == "__main__":
    get_player_pos()
