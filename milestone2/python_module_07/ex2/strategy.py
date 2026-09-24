#!/usr/bin/env python3
import abc
from ex0.creatures import Creature
from ex1.creatures2 import Creature as Creature2
from ex1.creatures2 import Sproutling, Bloomelle
from ex1.creatures2 import Shiftling, Morphagon
from ex1.creatures2 import TransformCapability


class BattleError(Exception):
    def __init__(self, message: str = "Default invalid match type.") -> None:
        self.message = message
        super().__init__(message)


class BattleStrategy(abc.ABC):
    @abc.abstractmethod
    def act(self, creature):
        pass

    @abc.abstractmethod
    def is_valid(self, creature) -> bool:
        pass


class NormalStrategy(BattleStrategy):
    def act(self, creature: Creature | Creature2):
        print(creature.attack())

    def is_valid(self, creature) -> bool:
        return True


class AggressiveStrategy(BattleStrategy):
    def act(self, creature: Shiftling | Morphagon):
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
    def act(self, creature: Sproutling | Bloomelle):
        print(creature.attack())
        print(creature.heal())

    def is_valid(self, creature: Creature2) -> bool:
        if isinstance(creature, TransformCapability):
            return True
        else:
            return False
