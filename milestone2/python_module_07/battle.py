#!/usr/bin/env python3
import ex0


def testing_factory(factory: type[ex0.CreatureFactory]) -> None:
    print("Testing factory")
    fac = factory()
    fac_base = fac.create_base()
    print(fac_base.describe())
    print(fac_base.attack())

    fac_base = fac.create_evolved()
    print(fac_base.describe())
    print(fac_base.attack())
    print()


def testing_battle(factory: type[ex0.CreatureFactory],
                   factory2: type[ex0.CreatureFactory]
                   ) -> None:
    print("Testing battle")
    fac = factory()
    fac_base = fac.create_base()
    fac2 = factory2()
    fac_base2 = fac2.create_base()

    print(fac_base.describe())
    print(" vs.")
    print(fac_base2.describe())
    print(" fight!")
    print(fac_base.attack())
    print(fac_base2.attack())


if __name__ == "__main__":
    testing_factory(ex0.FlameFactory)
    testing_factory(ex0.AquaFactory)
    testing_battle(ex0.FlameFactory, ex0.AquaFactory)
