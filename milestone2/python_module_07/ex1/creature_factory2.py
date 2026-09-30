#!/usr/bin/env python3
from ex0.creature_factory import CreatureFactory
from .creatures2 import Sproutling, Bloomelle
from .creatures2 import Shiftling, Morphagon
from .creatures2 import Creature


class HealingCreatureFactory(CreatureFactory):
    def create_base(self) -> Creature:
        creature = Sproutling()
        return (creature)

    def create_evolved(self) -> Creature:
        creature = Bloomelle()
        return (creature)


class TransformCreatureFactory(CreatureFactory):
    def create_base(self) -> Creature:
        creature = Shiftling()
        return (creature)

    def create_evolved(self) -> Creature:
        creature = Morphagon()
        return (creature)
