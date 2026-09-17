#!/usr/bin/env python3
import sys


def ft_command_quest() -> None:
    print("=== Command Quest ===")
    print(f"Program name: {sys.argv[0]}")
    if (len(sys.argv) - 1) > 0:
        print(f"Arguments received: {len(sys.argv[1:])}")
        for i in range(1, len(sys.argv)):
            print(f"Arguments {i}: " + sys.argv[i])
    else:
        print("No arguments provided!")
    print(f"Total arguments: {len(sys.argv)}\n")


if __name__ == "__main__":
    ft_command_quest()
