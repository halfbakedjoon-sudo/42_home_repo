#!/usr/bin/env python3
import random


def gen_player_achievement() -> None:
    achievements = sorted(set([
        "Protagonist Plot Armor", "Domain Expansion", "ORA ORA ORA!",
        "Explosion!!! Mastery", "10 Years Player", "GG EZ",
        "Plus Ultra!", "Omae Wa Mou Shindeiru",
        "It\'s Over 9000!", "Isekai\'d By a Truck",
        "Speedrun Any%", "No Waifu No Life",
        "Grinding Since Day 1", "Git Gud", "Aura Farming",
        "Aura Farming", "Git Gud"]))

    luke = sorted(random.sample(achievements, k=random.randint(6, 9)))
    nate = sorted(random.sample(achievements, k=random.randint(6, 9)))
    dex = sorted(random.sample(achievements, k=random.randint(6, 9)))
    chia = sorted(random.sample(achievements, k=random.randint(6, 9)))
    elysia = sorted(random.sample(achievements, k=random.randint(6, 9)))
    print(f"Player Luke:   {luke}")
    print(f"Player Nate:   {nate}")
    print(f"Player Dex:    {dex}")
    print(f"Player Chia:   {chia}")
    print(f"Player Elysia: {elysia}")

    all_unique = set(luke).union(nate, dex, chia, elysia)
    print(f"\nAll distinc achievements: {all_unique}")

    all_common = set(luke).intersection(nate, dex, chia, elysia)
    print(f"\nCommon achievements: {all_common}")

    print(f"\nOnly Luke has: {set(luke).difference(nate, dex, chia, elysia)}")
    print(f"Only Nate has: {set(nate).difference(luke, dex, chia, elysia)}")
    print(f"Only Dex has: {set(dex).difference(luke, nate, chia, elysia)}")
    print(f"Only Chia has: {set(chia).difference(luke, nate, dex, elysia)}")
    print(f"Only Elysia has: {set(elysia).difference(luke, nate, dex, chia)}")

    print(f"\nLuke is missing: {sorted(set(achievements).difference(luke))}")
    print(f"Nate is missing: {sorted(set(achievements).difference(nate))}")
    print(f"Dex is missing: {sorted(set(achievements).difference(dex))}")
    print(f"Chia is missing: {sorted(set(achievements).difference(chia))}")
    print(f"Elysia is missing: {sorted(set(achievements).difference(elysia))}")


if __name__ == "__main__":
    gen_player_achievement()
