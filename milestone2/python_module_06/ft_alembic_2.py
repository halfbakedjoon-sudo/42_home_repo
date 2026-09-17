#!/usr/bin/env python3
import alchemy.elements


if __name__ == "__main__":
    print("=== Alembic 2 ===")
    print("Accessing alchemy/elements.py using 'import ...' structure")
    print(f"Testing {(alchemy.elements.create_earth.__name__)}: "
          f"{alchemy.elements.create_earth()}")
