#!/usr/bin/env python3
from .light_spellbook import light_spell_allowed_ingredients


def validate_ingredients(ingredients: str) -> str:
    arry = ingredients.replace(",", "").split(" ")
    targets = light_spell_allowed_ingredients()
    for inv in targets:
        for target in arry:
            if target.lower() == inv.lower():
                return ("VALID")
    return ("INVALID")
