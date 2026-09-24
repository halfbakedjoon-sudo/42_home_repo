#!/usr/bin/env python3
import abc


class Creature(abc.ABC):
    def __init__(self):
        self.name = {"flameling": "fire",
                     "pyrodon": "fire/flying",
                     "aquabub": "water",
                     "torragon": "water"}

    @abc.abstractmethod
    def attack(self) -> str:
        pass

    def describe(self) -> str:
        creature: str = self.__class__.__name__
        return (f"{creature.capitalize()} is a "
                f"{(self.name.get(creature.lower())).title()} type Creature")


class Flameling(Creature):
    def __init__(self):
        Creature.__init__(self)
        self.creature = self.__class__.__name__

    def attack(self) -> str:
        return ("Flameling uses Ember!")


class Pyrodon(Flameling):
    def attack(self) -> str:
        return ("Pyrodon uses Flamethrower!")


class Aquabub(Creature):
    def __init__(self):
        Creature.__init__(self)
        self.creature = self.__class__.__name__

    def attack(self) -> str:
        return ("Aquabub uses Water Gun!")


class Torragon(Aquabub):
    def attack(self) -> str:
        return ("Torragon uses Hydro Pump!")


if __name__ == "__main__":
    test = Flameling()
