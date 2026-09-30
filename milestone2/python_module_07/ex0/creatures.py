#!/usr/bin/env python3
import abc


class Creature(abc.ABC):
    def __init__(self):
        self.name = {"flameling": "fire",
                     "pyrodon": "fire/flying",
                     "aquabub": "water",
                     "torragon": "water"}
        self.creature = self.__class__.__name__

    @abc.abstractmethod
    def attack(self) -> str:
        pass

    def describe(self) -> str:
        return (f"{self.creature} is a "
                f"{(self.name.get(self.creature.lower())).title()}"
                " type Creature")


class Flameling(Creature):
    def attack(self) -> str:
        return (f"{self.__class__.__name__} uses Ember!")


class Pyrodon(Creature):
    def attack(self) -> str:
        return (f"{self.__class__.__name__} uses Flamethrower!")


class Aquabub(Creature):
    def attack(self) -> str:
        return (f"{self.__class__.__name__} uses Water Gun!")


class Torragon(Creature):
    def attack(self) -> str:
        return (f"{self.__class__.__name__} uses Hydro Pump!")
