#!/usr/bin/env python3
from .creatures import Flameling, Pyrodon
from .creatures import Aquabub, Torragon
from .creatures import Creature
import abc


class CreatureFactory(abc.ABC):
    @abc.abstractmethod
    def create_base(self):
        pass

    @abc.abstractmethod
    def create_evolved(self):
        pass


class FlameFactory(CreatureFactory):
    def create_base(self) -> Creature:
        creature = Flameling()
        return (creature)

    def create_evolved(self) -> Creature:
        creature = Pyrodon()
        return (creature)


class AquaFactory(CreatureFactory):
    def create_base(self) -> Creature:
        creature = Aquabub()
        return (creature)

    def create_evolved(self) -> Creature:
        creature = Torragon()
        return (creature)
