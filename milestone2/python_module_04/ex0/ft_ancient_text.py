#!/usr/bin/env python3
import sys
from typing import IO


def ft_ancient_fragment() -> None:
    if len(sys.argv) != 2:
        print("Usage: ft_ancient_text.py <file>")
        return

    filename: str = sys.argv[1]
    print("=== Cyber Archives Recovery ===")
    print(f"Accessing file '{filename}'")
    try:
        fd: IO[str] = open(filename)
    except OSError as e:
        print(f"Error opening file '{filename}': {e}")
        return

    content = fd.read()

    lines = content.splitlines()
    print("---\n")
    for i in lines:
        print(f"{i}")
    print("\n---")
    fd.close()
    print(f"File '{filename}' closed.")


if __name__ == "__main__":
    ft_ancient_fragment()
