#!/usr/bin/env python3
import sys
import typing


def ft_stream_management() -> None:
    if len(sys.argv) != 2:
        print("Usage: ft_stream_management.py <file>")
        return

    filename: str = sys.argv[1]
    print("=== Cyber Archives Recovery & Preservation ===")
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
        sys.stderr.write(f"[STDERR] Error opening file '{filename}': {e}")
        return

    fd.close()
    print(f"File '{filename}' closed.")

    new_content: list[str] = []
    for i in lines:
        new_content.append(i + "#")

    print("\nTransform data:")
    print("---\n")
    for i in new_content:
        print(f"{i}")
    print("\n---")

    print("Enter new file name (or empty): ", end="")
    sys.stdout.flush()
    new_file: str = sys.stdin.readline().rstrip("\n")
    if new_file:
        print(f"Saving data to '{new_file}'")
        try:
            new_fd: typing.IO[str] = open(new_file, "w", newline="")
            for n in range(len(new_content)):
                if n < len(new_content) - 1:
                    new_fd.write(new_content[n] + "\n")
                else:
                    new_fd.write(new_content[n])
            print(f"Data saved in file '{new_file}'.")
            new_fd.close()
        except OSError as e:
            sys.stderr.write(f"[STDERR] Error opening file '{new_file}': {e}")
            sys.stderr.flush()
            print("\nData not saved.")
    else:
        print("Not saving data.")


if __name__ == "__main__":
    ft_stream_management()
