#!/usr/bin/env python3
from alchemy import potions

if __name__ == "__main__":
    print("=== Distillation 0 ===")
    print("Testing strength_potion: "
          f"{potions.strength_potion()}")
    print("Testing healing_potion: "
          f"{potions.healing_potion()}")
