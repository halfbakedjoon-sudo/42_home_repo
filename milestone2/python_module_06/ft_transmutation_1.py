#!/usr/bin/env python3
import alchemy.transmutation


def transmutation_1() -> None:
    print("=== Transmutation 1 ===")
    print("Import transmutation module directly")
    print("Testing lead to gold: ", end="")
    print(alchemy.transmutation.recipes.lead_to_gold())
    print()


if __name__ == "__main__":
    transmutation_1()
