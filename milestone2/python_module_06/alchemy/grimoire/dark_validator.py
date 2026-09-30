#!/usr/bin/env python3
from .dark_spellbook import dark_spell_allowed_ingredients


def validate_ingredients(ingredients: str) -> str:
    ing_list = ingredients.replace(",", "").split(" ")
    allowed = dark_spell_allowed_ingredients()
    for allow in allowed:
        for ing in ing_list:
            if ing.lower() == allow.lower():
                return ("VALID")
    return ("INVALID")
