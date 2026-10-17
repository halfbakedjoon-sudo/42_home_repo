#!/usr/bin/env python3
from collections.abc import Callable
import functools
import time

# def spell_timer(func: Callable) -> Callable
# def power_validator(min_power: int) -> Callable
# def retry_spell(max_attempts: int) -> Callable
# class MageGuild:
# @staticmethod
# def validate_mage_name(name: str) -> bool
# def cast_spell(self, spell_name: str, power: int) -> str
# Master's Tower Test Data
test_powers = [13, 18, 15, 15]
spell_names = ['freeze', 'lightning', 'heal', 'meteor']
mage_names = ['Ember', 'Luna', 'Kai', 'Morgan', 'Ash', 'Rowan']
invalid_names = ['Jo', 'A', 'Alex123', 'Test@Name']

# spell_timer(func) - Time execution decorator:
# • Create a decorator that measures function execution time
# • Print "Casting function_name..." before execution
# • Print "Spell completed in X.XXX seconds" after execution (3 decimal places)
# • Use functools.wraps to preserve original function metadata
# • Return the original function’s result


def spell_timer(func: Callable[[], str]) -> Callable[[], str]:
    @functools.wraps(func)
    def wrapper() -> str:
        print(f'Casting {func.__name__}...')
        start: float = time.perf_counter()
        spell = func()
        end: float = time.perf_counter()
        print(f'Spell completed in {(end - start):.3f} seconds')
        return spell
    return wrapper


# @spell_timer
def fireball() -> str:
    return 'Fireball cast!'


print()
print('Testing spell timer...')
timer_fireball = spell_timer(fireball)
timer_fireball()
print(f'Result: {timer_fireball.__name__.title()} cast!')


# power_validator(min_power) - Parameterized validation decorator:
# • Create a decorator factory that validates power levels
# • Applied on a standalone function
# • If power is valid (>= min_power), execute the function normally
# • If invalid, return "Insufficient power for this spell"
# • Use functools.wraps properly





# retry_spell(max_attempts) - Retry decorator:
# • Create a decorator that retries failed spells
# • If function raises an exception, retry up to max_attempts times
# • Print "Spell failed, retrying... (attempt n/max_attempts)"
# • If all attempts fail, return "Spell casting failed after max_attempts attempts"
# • If one attempt succeeds, return its result normally
# MageGuild class - Demonstrate staticmethod:
# • validate_mage_name(name) - Static method that checks if name is valid
# • Name is valid if it’s at least 3 characters and contains only letters/spaces
# • cast_spell(self, spell_name, power) - Instance method
# • Should use the power_validator decorator with min_power=10
# • When power is valid, return "Successfully cast spell_name with <power> power"
# • Otherwise return "Insufficient power for this spell"