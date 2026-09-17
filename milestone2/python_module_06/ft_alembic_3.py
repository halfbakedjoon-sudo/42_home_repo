#!/usr/bin/env python3
from alchemy import elements


if __name__ == "__main__":
    print("=== Alembic 3 ===")
    print("Accessing alchemy/elements.py using 'from ... "
          "import ...' structure")
    print(f"Testing {(elements.create_air.__name__)}: "
          f"{elements.create_air()}")
