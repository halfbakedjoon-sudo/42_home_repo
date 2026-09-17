#!/usr/bin/env python3
import sys


def ft_score_analytics() -> None:
    scores: list[int] = []
    print("=== Player Score Analytics ===")
    for i in sys.argv[1:]:
        try:
            scores.append(int(i))
        except ValueError:
            print(f"Invalid parameter: {i}")
    if not scores:
        print("No scores provided. Usage: "
              "python3 ft_score_analytic.py <score1> <score2> ...")
    else:
        print(f"Scores processed: {scores}")
        print(f"Total players: {len(scores)}")
        print(f"Total score: {sum(scores)}")
        print(f"Average score: {sum(scores)/len(scores)}")
        print(f"High score: {max(scores)}")
        print(f"Low score: {min(scores)}")
        print(f"Score range: {max(scores)-min(scores)}")


if __name__ == "__main__":
    ft_score_analytics()
