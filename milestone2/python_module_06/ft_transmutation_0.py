#!/usr/bin/env python3
import alchemy.transmutation.recipes


def transmutation_0() -> None:
    print("=== Transmutation 0 ===")
    print("Using file alchemy/transmutation/recipes.py directly")
    print("Testing lead to gold: ", end="")
    print(alchemy.transmutation.recipes.lead_to_gold())
    print()


if __name__ == "__main__":
    transmutation_0()
