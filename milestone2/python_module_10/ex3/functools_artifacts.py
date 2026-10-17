#!/usr/bin/env python3
import functools
from operator import add, mul
from collections.abc import Callable
from typing import Any

# Ancient Library Test Data
spell_powers = [22, 16, 47, 13, 12, 45]
operations = ['add', 'multiply', 'max', 'min']
fibonacci_tests = [11, 14, 11]


# functools, operator

# spell_reducer(spells, operation) - Reduce spell powers:
# • Use functools.reduce to combine all spell powers
# • Support operations: "add", "multiply", "max", "min"
# • Use operator module functions (add, mul, etc.)
# • Return the final reduced value
# • If spells is empty, return 0
# • If operation is unknown, properly handle the error


def spell_reducer(spells: list[int], operation: str) -> int:
    try:
        if operation == 'add':
            output = functools.reduce(add, spells)
        elif operation == 'multiply':
            output = functools.reduce(mul, spells)
        elif operation == 'max':
            output = functools.reduce(max, spells) 
        elif operation == 'min':
            output = functools.reduce(min, spells) 
    except Exception as e:
        print(e)
    return output if spells else 0


print()
print('Testing spell reducer...')
print(f'Original list: {spell_powers}')
print(f'Sum:     {spell_reducer(spell_powers, operations[0])}')
print(f'Product: {spell_reducer(spell_powers, operations[1])}')
print(f'Max:     {spell_reducer(spell_powers, operations[2])}')
print(f'Min:     {spell_reducer(spell_powers, operations[3])}')


# partial_enchanter(base_enchantment) - Create partial applications:
# • Take a base enchantment function with signature (power: int,
#   element: str, target:
# str) -> str
# • Use functools.partial to create 3 specialized versions
# • Each version pre-filling power=50 and the element


def partial_enchanter(
        base_enchantment: Callable[[int, str, str], str]
        ) -> dict[str, Callable[[str], str]]:
    fire = functools.partial(base_enchantment, 50, 'fire')
    ice = functools.partial(base_enchantment, 50, 'ice')
    stone = functools.partial(base_enchantment, 50, 'stone')
    output: dict[str, Callable[[str], str]] = {
        'fire': fire, 'ice': ice,
        'stone': stone
    }
    return output


def base_enchantment(power: int, element: str, target: str) -> str:
    return f'He used {element} to hit {target}, dealing {power} damage!'


special_enchantment: dict[str, Callable[[str], str]] = \
    partial_enchanter(base_enchantment)

fire = special_enchantment['fire']
ice = special_enchantment['ice']
stone = special_enchantment['stone']

print()
print('Testing partial enchanter...')
print(f'{fire('dragon')}')
print(f'{ice('dragon')}')
print(f'{stone('dragon')}')


# memoized_fibonacci(n) - Cached fibonacci:
# • Use functools.lru_cache decorator for memoization
# • Implement fibonacci sequence calculation
# • Function should return the nth Fibonacci number
# • The cache should improve performance for repeated calls
# • Return the nth fibonacci number

@functools.lru_cache(maxsize=None)
def memoized_fibonacci(n: int) -> int:
    print('Computing...')
    return (n if n < 2 else memoized_fibonacci(n - 1) +
            memoized_fibonacci(n - 2))


print()
print('Testing memoized fibonacci...')
print(f'Fib(0): {memoized_fibonacci(0)}')
print(f'Fib(1): {memoized_fibonacci(1)}')
print(f'Fib(10): {memoized_fibonacci(10)}')
print(f'Fib(15): {memoized_fibonacci(15)}')
print(f'Fib(0): {memoized_fibonacci(0)}')
print(f'Fib(1): {memoized_fibonacci(1)}')
print(f'Fib(10): {memoized_fibonacci(10)}')
print(f'Fib(15): {memoized_fibonacci(15)}')


# spell_dispatcher() - Create single dispatch system:
# • Use decorator functools.singledispatch to create a spell system
# • The base function receives Any and handles unknown spell type
# • Handle different types: int (damage spell), str (enchantment),
#   list (multi-cast)
# • Return the dispatcher function
# • Each type should have appropriate spell behavior


@functools.singledispatch
def spell_dispatcher(value: Any) -> str:
    return 'Unknown spell type'


@spell_dispatcher.register
def _(value: int) -> str:
    return (f'Damage spell: {value} damage')


@spell_dispatcher.register
def _(value: str) -> str:
    return (f'Enchantment: {value}')


@spell_dispatcher.register
def _(value: list) -> str:
    return (f'Multi-cast: {len(value)} spells')


print()
print('Testing spell dispatcher...')
print(spell_dispatcher(42))
print(spell_dispatcher('fireball'))
print(spell_dispatcher(['fireball', 'doom', 'tornado']))
print(spell_dispatcher(3.142))
