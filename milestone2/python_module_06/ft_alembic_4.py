#!/usr/bin/env python3
import alchemy
import traceback
import sys


def alembic_4() -> None:
    try:
        print("=== Alembic 4 ===")
        print("Accessing the alchemy module using 'import alchemy'")
        print(f"Testing {(alchemy.create_air.__name__)}: "
              f"{alchemy.create_air()}")
        print("Now show that not all functions can be reached")
        print("This will raise an exception!")
        print("Testing the hidden create_earth: ", end="")
        sys.stdout.flush()
        print(f"{alchemy.create_earth()}")
        print()
    except AttributeError:
        traceback.print_exc()
        print()


if __name__ == "__main__":
    alembic_4()
