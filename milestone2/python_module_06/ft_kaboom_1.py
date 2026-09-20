#!/usr/bin/env python3
import traceback


if __name__ == "__main__":
    print("=== Kaboom 1 ===")
    print("Access to alchemy/grimoire/dark_spellbook.py directly")
    print("Test import now - THIS WILL RAISE AN UNCAUGHT EXCEPTION")
    try:
        from alchemy.grimoire.dark_spellbook import dark_spell_record
        result = dark_spell_record(
            'Fantasy', 'Earth, wind and fire')
    except ImportError:
        traceback.print_exc()
