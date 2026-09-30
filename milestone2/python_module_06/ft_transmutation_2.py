#!/usr/bin/env python3
import alchemy


def transmutation_2() -> None:
    print("=== Transmutation 2 ===")
    print("Import alchemy module only")
    print("Testing lead to gold: ", end="")
    print(alchemy.transmutation.recipes.lead_to_gold())
    print()


if __name__ == "__main__":
    transmutation_2()
