#!/usr/bin/env python3
# from .light_spellbook import light_spell_allowed_ingredients
from . import light_spellbook


def validate_ingredients(ingredients: str) -> str:
    ing_list = ingredients.replace(",", "").split(" ")
    allowed = light_spellbook.light_spell_allowed_ingredients()
    for allow in allowed:
        for ing in ing_list:
            if ing.lower() == allow.lower():
                return ("VALID")
    return ("INVALID")
