#!/usr/bin/env python3
import alchemy
import traceback


if __name__ == "__main__":
    try:
        print("=== Alembic 4 ===")
        print("Accessing the alchemy module using 'import alchemy'")
        print(f"Testing {(alchemy.create_air.__name__)}: "
              f"{alchemy.create_air()}")
        print("Now show that not all functions can be reached")
        print("This will raise an exception!")
        print("Testing the hidden create_earth: ")
        print(alchemy.create_earth())
    except AttributeError:
        traceback.print_exc()
