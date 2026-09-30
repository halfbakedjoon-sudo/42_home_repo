#!/usr/bin/env python3
from alchemy import potions


def distillation_0() -> None:
    print("=== Distillation 0 ===")
    print("Direct access to alchemy/potions.py")
    print("Testing strength_potion: "
          f"{potions.strength_potion()}")
    print("Testing healing_potion: "
          f"{potions.healing_potion()}")
    print()


if __name__ == "__main__":
    distillation_0()
