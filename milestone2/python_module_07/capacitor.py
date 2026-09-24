#!/usr/bin/env python3
import ex0
from ex1 import HealingCreatureFactory, TransformCreatureFactory


def testing_factory2(factory: type[ex0.CreatureFactory]) -> None:
    print("Testing  Creature with healing capability")
    fac = factory()
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


def testing_transform(factory: type[ex0.CreatureFactory]) -> None:
    print("Testing Creature with transform capability")
    fac = factory()
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


if __name__ == "__main__":
    testing_factory2(HealingCreatureFactory)
    testing_transform(TransformCreatureFactory)
