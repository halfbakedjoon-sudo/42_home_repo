#!/usr/bin/env python3
import sys


class RedundantError(Exception):
    def __init__(self, message: str = "Unknown Redundant Error") -> None:
        self.message = message
        super().__init__(message)


def ft_inventory_system(inv: dict[str, int]) -> None:
    for i in sys.argv[1:]:
        try:
            key, value = i.split(":")
        except ValueError:
            print(f"Error - invalid parameter '{i}'")
            continue
        try:
            if key in inv:
                raise RedundantError(f"Redundant item '{key}' - discarding")
        except RedundantError as e:
            print(f"{e}")
            continue
        try:
            inv[key] = int(value)
        except ValueError as e:
            print(f"Quantity error for '{key}': {e}")
            continue


if __name__ == "__main__":
    inv: dict[str, int] = {"magic_item": 1}
    new_inv: dict[str, int] = {}

    ft_inventory_system(new_inv)
    if new_inv:
        print(f"Got inventory: {new_inv}")
        print(f"Total quantity of the {len(new_inv.keys())} items: "
              f"{sum(new_inv.values())}")
        for key in new_inv:
            print(f"Item {key} represents "
                  f"{round(new_inv[key] / sum(new_inv.values()) * 100, 1)}%")

        most = max(new_inv.values())
        for key in new_inv:
            if new_inv[key] == most:
                print(f"Item most abundant: {key} with quantity {most}")
                break

        least = min(new_inv.values())
        for key in new_inv:
            if new_inv[key] == least:
                print(f"Item least abundant: {key} with quantity {least}")
                break

        new_inv.update(inv)
        print(f"Updated inventory: {new_inv}")
    else:
        print(f"No update to inventory: {inv}")
