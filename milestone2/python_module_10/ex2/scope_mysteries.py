#!/usr/bin/env python3
from collections.abc import Callable
from typing import Any

# Memory Depths Test Data
initial_powers = [77, 79, 58]
power_additions = [15, 10, 11, 9, 19]
enchantment_types = ['Flowing', 'Radiant', 'Dark']
items_to_enchant = ['Amulet', 'Armor', 'Wand', 'Staff']

# mage_counter() - Create a counting closure:
# • Return a function that counts how many times it’s been called
# • Each call should return the current count (starting from 1)
# • The counter should persist between calls
# • Creating two separate counters must yield independent state.
# • Use closure to maintain state without global variables


def mage_counter() -> Callable[[], int]:
    count: int = 0

    def counting() -> int:
        nonlocal count
        count += 1
        return count
    return counting


counter_a = mage_counter()
counter_b = mage_counter()

print()
print('Testing mage counter...')
print(f'counter_a call 1: {counter_a()}')
print(f'counter_a call 2: {counter_a()}')
print(f'counter_b call 1: {counter_b()}')
print(f'counter_a call 3: {counter_a()}')


# spell_accumulator(initial_power) - Create power accumulator:
# • Return a function that accumulates power over time
# • Each call adds the given amount to the total power
# • Return the new total power after each addition
# • Start with initial_power as the base


def spell_accumulator(initial_power: int) -> Callable[[int], int]:
    power: int = initial_power

    def accumulate(new_power: int) -> int:
        nonlocal power
        power += new_power
        return power
    return accumulate


print()
print('Testing spell accumulator...')
for n, power in enumerate(initial_powers):
    detector = spell_accumulator(power)
    print(f'Base {power}, add {power_additions[n]}: '
          f'{detector(power_additions[n])}')


# enchantment_factory(enchantment_type) - Create enchantment functions:
# • Return a function that applies the specified enchantment
# • The returned function takes an item name and returns enchanted description
# • Format: "enchantment_type item_name" (e.g., "Flaming Sword")
# • Each factory creates functions with different enchantment types


def enchantment_factory(enchantment_type: str) -> Callable[[str], str]:
    def enchantment(item_name: str) -> str:
        return enchantment_type + ' ' + item_name
    return enchantment


print()
print('Testing enchantment factory...')
for n, enchant in enumerate(enchantment_types):
    enchantment = enchantment_factory(enchant)
    print(f'{enchantment(items_to_enchant[n])}')


# memory_vault() - Create a memory management system:
# • Return a dict with ’store’ and ’recall’ functions
# • ’store’ function: takes (key, value) and stores the memory
# • ’recall’ function: takes (key) and returns stored value or
#   "Memory not found"
# • Use closure to maintain private memory storage


def memory_vault() -> dict[str, Callable[..., Any]]:
    storage: dict = {}

    def store(key: Any, value: Any) -> None:
        storage[key] = value

    def recall(key: Any) -> Any:
        return storage[key] if key in storage else 'Memory not found'

    combined: dict[str, Callable[..., Any]] = {
        'store': store, 'recall': recall}
    return combined


print()
print('Testing memory vault...')
vault = memory_vault()
store_fn = vault['store']
recall_fn = vault['recall']
store_fn('Dragon', 'roar')
print('Stored key="Dragon" value="roar"')
print(f'Recall key="Dragon": {recall_fn('Dragon')}')
print(f'Recall key="Drago": {recall_fn('Drago')}')
