#!/usr/bin/env python3
from .dark_spellbook import dark_spell_allowed_ingredients


def validate_ingredients(ingredients: str) -> str:
    arry = ingredients.replace(",", "").split(" ")
    targets = dark_spell_allowed_ingredients()
    for inv in targets:
        for target in arry:
            if target.lower() == inv.lower():
                return ("VALID")
    return ("INVALID")
