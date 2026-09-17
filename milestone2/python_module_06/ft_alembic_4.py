#!/usr/bin/env python3
import alchemy


if __name__ == "__main__":
    try:
        print(alchemy.create_air())
        print(alchemy.create_earth())
    except AttributeError as e:
        print(e)
