#!/usr/bin/env python3
import alchemy


def distillation_1() -> None:
    print("=== Distillation 1 ===")
    print("Using: 'import alchemy' structure to access potions")
    print("Testing strength_potion: "
          f"{alchemy.strength_potion()}")
    print("Testing heal alias: "
          f"{alchemy.heal()}")
    print()


if __name__ == "__main__":
    distillation_1()
