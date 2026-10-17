#!/usr/bin/env python3
from collections.abc import Callable


# Higher Realm Test Data
# Use these in your test functions:
test_values = [12, 17, 8]
test_targets = ['Dragon', 'Goblin', 'Wizard', 'Knight']

# def spell(target: str, power: int) -> str


def heal(target: str, power: int) -> str:
    return f"Heal restores {target} for {power} HP"


def fireball(target: str, power: int) -> str:
    return f"Fireball hits {target} for {power} HP"

# spell_combiner(spell1, spell2) - Combine two spells:
# • Return a new function that calls both spells with the same arguments
# • The combined spell should return a tuple of both results
# • Example: combined = spell_combiner(fireball, heal)


def spell_combiner(
        spell1: Callable[[str, int], str], spell2: Callable[[str, int], str]
        ) -> Callable[[str, int], tuple[str, str]]:
    def new_spell(target: str, power: int) -> tuple[str, str]:
        return (spell1(target, power), spell2(target, power))
    return new_spell


combined = spell_combiner(fireball, heal)
print()
print('Testing spell combiner...')
print('Combined spell result: ', end="")
print(f'{combined('Dragon', 12)[0]}, {combined('Dragon', 12)[1]}')

# power_amplifier(base_spell, multiplier) - Amplify spell power:
# • Returns a function with the same signature as the original spell
# • Returns a new spell where the power is multiplied before casting.
# • Example: mega_fireball = power_amplifier(fireball, 3)


def power_amplifier(
        base_spell: Callable[[str, int], str], multiplier: int
        ) -> Callable[[str, int], str]:
    def powerup(target: str, power: int) -> str:
        return base_spell(target, power * multiplier)
    return powerup


mega_fireball = power_amplifier(fireball, 3)
print()
print('Testing power amplifier...')
print(f'Original: {fireball('Dragon', 10)}')
print(f'Amplified: {mega_fireball('Dragon', 10)}')


# conditional_caster(condition, spell) - Cast spell conditionally:
# • Returns a new spell that only casts if a condition is True.
# • If condition fails, return "Spell fizzled"
# • Both condition and spell receive the same arguments


def condition(target: str, power: int) -> bool:
    if target == 'Dragon' and power <= 20:
        return False
    else:
        return True


def conditional_caster(
        condition: Callable[[str, int], bool], spell: Callable[[str, int], str]
        ) -> Callable[[str, int], str]:
    def spell50(target: str, power: int) -> str:
        if not condition(target, power):
            return 'Spell fizzled'
        else:
            return f'{spell(target, power)}'
    return spell50


print()
print('Testing conditional caster...')
possible = conditional_caster(condition, fireball)
print(possible('Dragon', 20))
print(possible('Dragon', 21))


# spell_sequence(spells) - Create spell sequence:
# • Return a function that casts all spells in order
# • Each spell receives the same arguments
# • Returns a list of all spell results


def spell_sequence(
        spells: list[Callable[[str, int], str]]
        ) -> Callable[[str, int], list[str]]:
    def spell_auto(target: str, power: int) -> list[str]:
        casted_spell: list[str] = []
        for spell in spells:
            casted_spell.append(spell(target, power))
        return casted_spell
    return spell_auto


auto_cast = spell_sequence([fireball, heal])
casted: list[str] = auto_cast('Dragon', 10)

print()
print('Testing spell sequence...')
for cast in casted:
    print(cast)
