#!/usr/bin/env python3
import alchemy.elements


def alembic_2() -> None:
    print("=== Alembic 2 ===")
    print("Accessing alchemy/elements.py using 'import ...' structure")
    print(f"Testing {(alchemy.elements.create_earth.__name__)}: "
          f"{alchemy.elements.create_earth()}")
    print()


if __name__ == "__main__":
    alembic_2()
