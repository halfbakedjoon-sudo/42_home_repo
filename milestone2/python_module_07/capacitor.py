#!/usr/bin/env python3
import ex0
from ex1 import HealingCreatureFactory, TransformCreatureFactory


def testing_factory2(fac: ex0.CreatureFactory) -> None:
    print("Testing Creature with healing capability")
    fac_base = fac.create_base()
    print(" base:")
    print(fac_base.describe())
    print(fac_base.attack())
    print(fac_base.heal())

    fac_base = fac.create_evolved()
    print(" evolved:")
    print(fac_base.describe())
    print(fac_base.attack())
    print(fac_base.heal())
    print()


def testing_transform(fac: ex0.CreatureFactory) -> None:
    print("Testing Creature with transform capability")
    fac_base = fac.create_base()
    print(" base:")
    print(fac_base.describe())
    print(fac_base.attack())
    print(fac_base.transform())
    print(fac_base.attack())
    print(fac_base.revert())

    fac_base = fac.create_evolved()
    print(" evolved:")
    print(fac_base.describe())
    print(fac_base.attack())
    print(fac_base.transform())
    print(fac_base.attack())
    print(fac_base.revert())
    print()


def main() -> None:
    heal_fac = HealingCreatureFactory()
    testing_factory2(heal_fac)

    trans_fac = TransformCreatureFactory()
    testing_transform(trans_fac)


if __name__ == "__main__":
    main()
