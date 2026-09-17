#!/usr/bin/env python3
import sys
from typing import IO


def ft_archive_creation() -> None:
    if len(sys.argv) != 2:
        print("Usage: ft_archive_creation.py <file>")
        return

    filename: str = sys.argv[1]
    print("=== Cyber Archives Recovery & Preservation ===")
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

    new_content: list[str] = []
    for i in lines:
        new_content.append(i + "#")

    print("Transform data:")
    print("---\n")
    for i in new_content:
        print(f"{i}")
    print("\n---")

    new_file: str = input("Enter new file name (or empty): ")
    if new_file:
        print(f"Saving data to '{new_file}'")
        new_fd: IO[str] = open(new_file, "w", newline="")
        for n in range(len(new_content)):
            if n < len(new_content) - 1:
                new_fd.write(new_content[n] + "\n")
            else:
                new_fd.write(new_content[n])
        print(f"Data saved in file '{new_file}'")
        new_fd.close()
    else:
        print("Not saving data.")


if __name__ == "__main__":
    ft_archive_creation()
