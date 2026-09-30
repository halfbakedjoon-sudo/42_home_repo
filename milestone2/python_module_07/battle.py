#!/usr/bin/env python3
import ex0


def testing_factory(fac: ex0.CreatureFactory) -> None:
    print("Testing factory")
    fac_base = fac.create_base()
    print(fac_base.describe())
    print(fac_base.attack())

    fac_base = fac.create_evolved()
    print(fac_base.describe())
    print(fac_base.attack())
    print()


def testing_battle(fac: ex0.CreatureFactory,
                   fac2: ex0.CreatureFactory
                   ) -> None:
    print("Testing battle")
    fac_base = fac.create_base()
    fac_base2 = fac2.create_base()

    print(fac_base.describe())
    print(" vs.")
    print(fac_base2.describe())
    print(" fight!")
    print(fac_base.attack())
    print(fac_base2.attack())


def main() -> None:
    flame_fac = ex0.FlameFactory()
    aqua_fac = ex0.AquaFactory()
    testing_factory(flame_fac)
    testing_factory(aqua_fac)
    testing_battle(flame_fac, aqua_fac)


if __name__ == "__main__":
    main()
