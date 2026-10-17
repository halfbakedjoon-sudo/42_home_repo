#!/usr/bin/env python3


# === Exercise 0 Test Data ===
# Lambda Sanctum Test Data
artifacts: list[dict] = [
    {'name': 'Crystal Orb', 'power': 110, 'type': 'accessory'},
    {'name': 'Wind Cloak', 'power': 87, 'type': 'relic'},
    {'name': 'Fire Staff', 'power': 117, 'type': 'weapon'},
    {'name': 'Lightning Rod', 'power': 93, 'type': 'focus'}]
mages: list[dict] = [
    {'name': 'Jordan', 'power': 98, 'element': 'fire'},
    {'name': 'Phoenix', 'power': 51, 'element': 'wind'},
    {'name': 'Luna', 'power': 92, 'element': 'wind'},
    {'name': 'Phoenix', 'power': 93, 'element': 'ice'},
    {'name': 'Alex', 'power': 82, 'element': 'shadow'}
    ]
spells = ['freeze', 'shield', 'tsunami', 'meteor']

# def artifact_sorter(artifacts: list[dict]) -> list[dict]
#  Use sorted() with a lambda to sort by ’power’ level (descending)
# {’name’: str, ’power’: int, ’type’: str}
# Return the sorted list

print()
print('Testing artifact sorter...')
artifacts = sorted(artifacts, key=lambda w: w['power'], reverse=True)
print(f'{artifacts[0]['name']} ({artifacts[0]['power']} power) comes '
      f'before {artifacts[1]['name']} ({artifacts[1]['power']} power)')
print()

# def power_filter(mages: list[dict], min_power: int) -> list[dict]
# Use filter() with a lambda to find mages with power >= min_power
# Each mage is a dict: {’name’: str, ’power’: int, ’element’: str}
# Return a list of filtered mages

print('Testing power filter...')
value: int = 69
strong_mages: list[dict] = list(filter(lambda mage: mage['power']
                                       >= value, mages))
for mage in strong_mages:
    print(f'{mage['name']} ({mage['power']} power) is a strong mage.')
print()

# def spell_transformer(spells: list[str]) -> list[str]
# Use map() with a lambda to add "* " prefix and " *" suffix
# Input: list of spell names (strings)
# Return a list of transformed spell names

spells = list(map(lambda spell: '* ' + spell + ' *', spells))
spell = ' '.join(spells)
print('Testing spell transformer...')
print(spell)
print()

# def mage_stats(mages: list[dict]) -> dict
# Use lambdas with max(), min() to find:
# Most powerful mage’s power level
# Least powerful mage’s power level
# Average power level (rounded to 2 decimals)
# Return dict: {’max_power’: int, ’min_power’: int, ’avg_power’: float}

most = max(mages, key=lambda mage: mage['power'])
weak = min(mages, key=lambda mage: mage['power'])
print('Testing mage stats...')
print(f'{most['name']} is the most powerful mage with {most['power']}')
print(f'{weak['name']} is the least powerful mage with {weak['power']}')
