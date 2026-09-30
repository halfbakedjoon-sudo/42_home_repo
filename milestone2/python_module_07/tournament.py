#!/usr/bin/env python3
import ex2
from ex2.strategy import BattleError
from ex0 import CreatureFactory
from ex2 import BattleStrategy
from ex0 import FlameFactory, AquaFactory
from ex0.creatures import Creature
from ex1 import HealingCreatureFactory, TransformCreatureFactory


def fighting(opp1: tuple[Creature, BattleStrategy],
             opp2: tuple[Creature, BattleStrategy]):
    try:
        print(opp1[0].describe())
        print(" vs.")
        print(opp2[0].describe())
        print(" now fight!")
        opp1[1].act(opp1[0])
        opp2[1].act(opp2[0])
    except BattleError:
        raise


def battle(opp1: tuple[CreatureFactory, BattleStrategy],
           opp2: tuple[CreatureFactory, BattleStrategy],
           opp3: tuple[CreatureFactory | None, BattleStrategy
                       | None] = (None, None)) -> None:
    try:
        if (isinstance(opp3[0], CreatureFactory) and
                isinstance(opp3[1], BattleStrategy)):
            opp1_base = opp1[0].create_base()
            opp2_base = opp2[0].create_base()
            opp3_base = opp3[0].create_base()
            print("*** Tournament ***\n3 opponents involved\n\n* Battle *")
            fighting((opp1_base, opp1[1]), (opp2_base, opp2[1]))
            print()
            print("* Battle *")
            fighting((opp1_base, opp1[1]), (opp3_base, opp3[1]))
            print()
            print("* Battle *")
            fighting((opp2_base, opp2[1]), (opp3_base, opp3[1]))
        else:
            opp1_base = opp1[0].create_base()
            opp2_base = opp2[0].create_base()
            print("*** Tournament ***\n2 opponents involved\n\n* Battle *")
            fighting((opp1_base, opp1[1]), (opp2_base, opp2[1]))
    except BattleError as e:
        print(e)


if __name__ == "__main__":
    flamefac = FlameFactory()
    healfac = HealingCreatureFactory()
    defend = ex2.DefensiveStrategy()
    normal = ex2.NormalStrategy()
    aggr = ex2.AggressiveStrategy()
    aquafac = AquaFactory()
    transfac = TransformCreatureFactory()

    try:
        print("Tournament 0 (basic)")
        print(" [ (Flameling+Normal), (Healing+Defensive) ]")
        battle((flamefac, normal),
               (healfac, defend))
        print()

        print("Tournament 1 (error)")
        print(" [ (Flameling+Aggressive), (Healing+Defensive) ]")
        battle((flamefac, aggr),
               (healfac, defend))
        print()

        print("Tournament 2 (multiple)")
        print(" [ (Aquabub+Normal), (Healing+Defensive), "
              "(Transform+Aggressive) ]")
        battle((aquafac, normal),
               (healfac, defend),
               (transfac, aggr))
    except Exception as e:
        print(e)
