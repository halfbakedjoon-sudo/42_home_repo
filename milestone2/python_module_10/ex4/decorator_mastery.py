#!/usr/bin/env python3
from collections.abc import Callable
import functools
import time

# def spell_timer(func: Callable) -> Callable
# def power_validator(min_power: int) -> Callable
# def retry_spell(max_attempts: int) -> Callable

# Master's Tower Test Data

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
        time.sleep(0.1)
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


test_powers = [13, 18, 15, 15]
spell_names = ['freeze', 'lightning', 'heal', 'meteor']


def power_validator(
        min_power: int
        ) -> Callable[[Callable[[int, str], str]], Callable[[int, str], str]]:
    def decorator(spell: Callable[[int, str], str]
                  ) -> Callable[[int, str], str]:
        @functools.wraps(spell)
        def wrapper(power: int, name: str) -> str:
            if not power >= min_power:
                return 'Insufficient power for this spell'
            else:
                return spell(power, name)
        return wrapper
    return decorator


def spell(power: int, name: str) -> str:
    return f'Successfully cast {name} with {power} power'


print()
print('Testing power validator...')
validator_15 = power_validator(15)
spell_fn = validator_15(spell)
for power, name in zip(test_powers, spell_names):
    print(f'{spell_fn(power, name)}')


# retry_spell(max_attempts) - Retry decorator:
# • Create a decorator that retries failed spells
# • If function raises an exception, retry up to max_attempts times
# • Print "Spell failed, retrying... (attempt n/max_attempts)"
# • If all attempts fail, return "Spell casting failed after
#   max_attempts attempts"
# • If one attempt succeeds, return its result normally


def make_flaky_spell() -> Callable[[int, str], str]:
    counter: int = 0

    def flaky_spell(power: int, name: str) -> str:
        nonlocal counter
        if counter < 2:
            counter += 1
            raise ValueError
        return f'Hero use {name} ({power} power) on Dragon'
    return flaky_spell


def make_always_failed() -> Callable[[int, str], str]:

    def always_failed(power: int, name: str) -> str:
        raise ValueError
    return always_failed


def retry_spell(
        max_attempts: int
        ) -> Callable[[Callable[[int, str], str]], Callable[[int, str], str]]:

    def decorator(spell: Callable[[int, str], str]
                  ) -> Callable[[int, str], str]:
        @functools.wraps(spell)
        def wrapper(power: int, name: str) -> str:
            attempt: int = 0
            while attempt < max_attempts:
                try:
                    return spell(power, name)
                except Exception:
                    attempt += 1
                    print(f'Spell failed, retrying... '
                          f'({attempt}/{max_attempts})')
            return (f'Spell casting failed after {max_attempts} attempts\n'
                    'Waaaaaaagh spelled !')
        return wrapper
    return decorator


print()
print('Testing retry spell...')
flaky = make_flaky_spell()
retried_flaky = retry_spell(5)(flaky)
print(retried_flaky(20, 'Dragon'))
print()
always_failed = make_always_failed()
retried_fail = retry_spell(5)(always_failed)
print(retried_fail(20, 'Dragon'))


# MageGuild class - Demonstrate staticmethod:
# • validate_mage_name(name) - Static method that checks if name is valid
# • Name is valid if it’s at least 3 characters and contains only
#   letters/spaces
# • cast_spell(self, spell_name, power) - Instance method
# • Should use the power_validator decorator with min_power=10
# • When power is valid, return "Successfully cast spell_name with <power>
#   power"
# • Otherwise return "Insufficient power for this spell"

# class MageGuild:
# @staticmethod
# def validate_mage_name(name: str) -> bool
# def cast_spell(self, spell_name: str, power: int) -> str

test_powers = [24, 21, 24, 26]
spell_names = ['tornado', 'blizzard', 'fireball', 'tsunami']
mage_names = ['Luna', 'Sage', 'Kai', 'River', 'Storm', 'Casey']
invalid_names = ['Jo', 'A', 'Alex123', 'Test@Name']


class MageGuild:
    def __init__(self, name: list[str]) -> None:
        self.name: list[str] = name

    @staticmethod
    def validate_mage_name(name: str) -> bool:
        if len(name) < 3 or not name.isalpha():
            return False
        else:
            return True

    def cast_spell(self, spell_name: str, power: int) -> str:
        min_power = power_validator(10)
        check_power = min_power(spell)
        return check_power(power, spell_name)


print()
print('Testing MageGuild...')
true_mages = MageGuild(mage_names)
print(f'{true_mages.validate_mage_name(mage_names[0])}')
print(f'{true_mages.validate_mage_name(invalid_names[0])}')
print(f'{true_mages.cast_spell('Lighting', 15)}')
print(f'{true_mages.cast_spell('Lighting', 9)}')
