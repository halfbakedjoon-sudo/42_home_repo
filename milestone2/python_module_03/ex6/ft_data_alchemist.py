#!/usr/bin/env python3
import random


if __name__ == "__main__":
    actions: list[str] = ["run", "eat", "sleep", "move", "climb", "swim",
                          "release", "use", "grab"]
    players: list[str] = ['Alice', 'bob', 'Charlie', 'dylan',
                          'Emma', 'Gregory', 'john', 'kevin',
                          'Liam']
    c_players: list[str] = []
    oc_players: list[str] = []

    for i in players:
        c_players.append(i.capitalize())
    for i in players:
        if i.capitalize() == i:
            oc_players.append(i)

    print("=== Game Data Alchemist ===")
    print(f"Initial list of players: {players}")
    print(f"New list with all names capitalized: {c_players}")
    print(f"New list of capitalized name only: {oc_players}")

    player_score: dict[str, int] = {}

    for player in c_players:
        player_score[player] = int(random.randint(0, 999))

    print(f"Score dict: {player_score}")

    average = round(sum(player_score.values())/len(player_score.values()), 2)
    print(f"Score average is {average}")

    up_average: dict[str, int] = {}
    for player in player_score:
        if player_score[player] > average:
            up_average[player] = player_score[player]
    print(f"High scores: {up_average}")
