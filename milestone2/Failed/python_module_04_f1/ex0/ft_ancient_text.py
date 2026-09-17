#!/usr/bin/env python3
import sys
import typing


def ft_ancient_fragment() -> None:
    if len(sys.argv) != 2:
        print("Usage: ft_ancient_text.py <file>")
        return

    filename: str = sys.argv[1]
    print("=== Cyber Archives Recovery ===")
    print(f"Accessing file '{filename}'")
    try:
        fd: typing.IO[str] = open(filename)

        content = fd.read()

        lines = content.splitlines()
        print("---\n")
        for i in lines:
            print(f"{i}")
        print("\n---")
    except OSError as e:
        print(f"Error opening file '{filename}': {e}")
        return
    finally:
        fd.close()
        print(f"File '{filename}' closed.")


if __name__ == "__main__":
    ft_ancient_fragment()
