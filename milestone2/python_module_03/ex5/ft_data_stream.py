#!/usr/bin/env python3
import random
from typing import Generator


def gen_event(actions: list[str],
              players: list[str]
              ) -> Generator[tuple[str, str], None, None]:
    yield (random.choice(players), random.choice(actions))


def consume_event(log: list[tuple[str, str]]) -> None:
    revent = random.choice(log)
    log.remove(revent)
    print(f"Got event from list: {revent}")


if __name__ == "__main__":
    actions: list[str] = ["run", "eat", "sleep", "move", "climb", "swim",
                          "release", "use", "grab"]
    players: list[str] = ["alice", "bob", "charlie", "dylan"]
    print("=== Game Data Stream Processor ===")
    log1: list[tuple[str, str]] = []
    for i in range(1000):
        events = gen_event(actions, players)
        event = next(events)
        log1.append(event)
        print(f"Event {i}: Player {event[0]} did action {event[1]}")

    log2: list[tuple[str, str]] = []
    for i in range(10):
        events = gen_event(actions, players)
        event = next(events)
        log2.append(event)
    print(f"Built list of 10 events: {log2}")
    while log2:
        consume_event(log2)
        print(f"Remains in list: {log2}")
