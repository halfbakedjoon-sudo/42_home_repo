#!/usr/bin/env python3
import traceback


def kaboom_1() -> None:
    print("=== Kaboom 1 ===")
    print("Access to alchemy/grimoire/dark_spellbook.py directly")
    print("Test import now - THIS WILL RAISE AN UNCAUGHT EXCEPTION")
    try:
        from alchemy.grimoire.dark_spellbook import dark_spell_record
        result = dark_spell_record(
            'Fantasy', 'Earth, wind and fire')
        print(f"Testing record light spell: "
              f"{result}")
        print()
    except ImportError:
        traceback.print_exc()
        print()


if __name__ == "__main__":
    kaboom_1()
