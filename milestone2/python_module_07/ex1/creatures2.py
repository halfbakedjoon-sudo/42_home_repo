#!/usr/bin/env python3
import abc


class HealCapability(abc.ABC):
    @abc.abstractmethod
    def heal(self) -> str:
        pass


class TransformCapability(abc.ABC):
    def __init__(self) -> None:
        self.state = False

    @abc.abstractmethod
    def transform(self) -> str:
        pass

    @abc.abstractmethod
    def revert(self) -> str:
        pass


class Creature(abc.ABC):
    def __init__(self) -> None:
        self.name = {"sproutling": "grass",
                     "bloomelle": "grass/fairy",
                     "shiftling": "normal",
                     "morphagon": "normal/dragon"}

    @abc.abstractmethod
    def attack(self) -> str:
        pass

    def describe(self) -> str:
        creature: str = self.__class__.__name__
        return (f"{creature.capitalize()} is a "
                f"{(self.name.get((creature.lower()), 'unknow')).title()} type"
                " Creature")


class Sproutling(Creature, HealCapability):
    def __init__(self) -> None:
        Creature.__init__(self)
        self.creature = self.__class__.__name__

    def attack(self) -> str:
        return (f"{self.creature.capitalize()} use Vine Whip!")

    def heal(self) -> str:
        return (f"{self.creature.capitalize()} heals itself for a small "
                "amount")


class Bloomelle(Sproutling):
    def attack(self) -> str:
        return (f"{self.creature.capitalize()} uses Petal Dance!")

    def heal(self) -> str:
        return (f"{self.creature.capitalize()} heals itself and others for a "
                "large amount")


class Shiftling(Creature, TransformCapability):
    def __init__(self) -> None:
        Creature.__init__(self)
        TransformCapability.__init__(self)
        self.creature = self.__class__.__name__

    def attack(self) -> str:
        if self.state:
            return (f"{self.creature.capitalize()} performs a boosted strike!")
        else:
            return (f"{self.creature.capitalize()} attacks normally.")

    def transform(self) -> str:
        self.state = True
        return (f"{self.creature.capitalize()} shifts into a sharper form!")

    def revert(self) -> str:
        self.state = False
        return (f"{self.creature.capitalize()} returns to normal.")


class Morphagon(Shiftling):
    def attack(self) -> str:
        if self.state:
            return (f"{self.creature.capitalize()} unleashes a devastating "
                    "morph strike!")
        else:
            return (f"{self.creature.capitalize()} attacks normally.")

    def transform(self) -> str:
        self.state = True
        return (f"{self.creature.capitalize()} morphs into a dragonic battle "
                "form!")

    def revert(self) -> str:
        self.state = False
        return (f"{self.creature.capitalize()} stabilizes its form.")
