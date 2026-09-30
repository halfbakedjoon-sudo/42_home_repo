#!/usr/bin/env python3
import elements


def alembic_0() -> None:
    print("=== Alembic 0 ===")
    print("Using 'import ...' structure to access elements.py")
    print(f"Testing {(elements.create_fire.__name__)}: "
          f"{elements.create_fire()}")
    print()


if __name__ == "__main__":
    alembic_0()
