#!/usr/bin/env python3
import abc
from ex0.creatures import Creature
from ex1.creatures2 import Creature as Creature2
from ex1.creatures2 import Sproutling, Bloomelle
from ex1.creatures2 import Shiftling, Morphagon
from ex1.creatures2 import TransformCapability, HealCapability


class BattleError(Exception):
    def __init__(self, message: str = "Default invalid match type.") -> None:
        super().__init__(message)


class BattleStrategy(abc.ABC):
    @abc.abstractmethod
    def act(self, creature) -> None:
        pass

    @abc.abstractmethod
    def is_valid(self, creature) -> bool:
        pass


class NormalStrategy(BattleStrategy):
    def act(self, creature: Creature | Creature2) -> None:
        try:
            if self.is_valid(creature):
                print(creature.attack())
            else:
                raise BattleError
        except BattleError:
            raise

    def is_valid(self, creature: Creature | Creature2) -> bool:
        if isinstance(creature, (Creature, Creature2)):
            return True
        else:
            return False


class AggressiveStrategy(BattleStrategy):
    def act(self, creature: Shiftling | Morphagon) -> None:
        try:
            if self.is_valid(creature):
                print(creature.transform())
                print(creature.attack())
                print(creature.revert())
            else:
                raise BattleError("Battle error, aborting tournament: "
                                  f"Invalid Creature '{creature.creature}' for"
                                  " this aggressive strategy")
        except BattleError:
            raise

    def is_valid(self, creature: Creature2) -> bool:
        if isinstance(creature, TransformCapability):
            return True
        else:
            return False


class DefensiveStrategy(BattleStrategy):
    def act(self, creature: Sproutling | Bloomelle) -> None:
        try:
            if self.is_valid(creature):
                print(creature.attack())
                print(creature.heal())
            else:
                raise BattleError("Battle error, aborting tournament: "
                                  f"Invalid Creature '{creature.creature}' for"
                                  " this defensive strategy")
        except BattleError:
            raise

    def is_valid(self, creature: Creature2) -> bool:
        if isinstance(creature, HealCapability):
            return True
        else:
            return False
