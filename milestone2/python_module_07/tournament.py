#!/usr/bin/env python3
import ex2
import typing
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


def tournament(opp1: tuple[CreatureFactory, BattleStrategy],
               opp2: tuple[CreatureFactory, BattleStrategy],
               opp3: tuple[CreatureFactory | typing.Any, BattleStrategy |
                           typing.Any] = (None, None)) -> None:
    if opp3[0] and opp3[1]:
        try:
            opp1_base = opp1[0].create_base()
            opp2_base = opp2[0].create_base()
            opp3_base = opp3[0].create_base()
            print("*** Tournament ***\n3 opponents involved\n")
            fighting((opp1_base, opp1[1]), (opp2_base, opp2[1]))
            print()
            fighting((opp1_base, opp1[1]), (opp3_base, opp3[1]))
            print()
            fighting((opp2_base, opp2[1]), (opp3_base, opp3[1]))
        except BattleError as e:
            print(e)

    else:
        try:
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

    print("Tournament 0 (basic)")
    print(" [ (Flameling+Normal), (Healing+Defensive) ]")
    tournament((flamefac, normal),
               (healfac, defend))
    print()
    aggr = ex2.AggressiveStrategy()
    print("Tournament 1 (error)")
    print(" [ (Flameling+Aggressive), (Healing+Defensive) ]")
    tournament((flamefac, aggr),
               (healfac, defend))
    print()
    aquafac = AquaFactory()
    transfac = TransformCreatureFactory()
    print("Tournament 2 (multiple)")
    print(" [ (Aquabub+Normal), (Healing+Defensive), (Transform+Aggressive) ]")
    tournament((aquafac, normal),
               (healfac, defend),
               (transfac, aggr))
