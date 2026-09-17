#!/usr/bin/env python3


class Plant():
    def __init__(self, name: str, health: int, water: int):
        self.name = name
        self.health = health
        self.water = water


class GardenError(Exception):
    def __init__(self, message: str = "Unknown garden error") -> None:
        self.message = message
        super().__init__(message)


class PlantError(GardenError):
    def __init__(self, message: str = "Unknown plant error") -> None:
        self.message = message
        super().__init__(message)


class WaterError(GardenError):
    def __init__(self, message: str = "Unknown water error") -> None:
        self.message = message
        super().__init__(message)


def check_water(plant: Plant) -> None:
    if plant.water < 50:
        raise WaterError("Not enough water in the tank!")


def check_plant(plant: Plant) -> None:
    if plant.health < 50:
        raise PlantError(f"The {plant.name} plant is wilting!")


if __name__ == "__main__":
    tomato = Plant("tomato", 49, 49)
    print("=== Custom Garden Errors Demo ===")
    print()
    print("Testing PlantError...")
    try:
        check_plant(tomato)
    except PlantError as e:
        print(f"Caught PlantError: {e}")
    print()
    print("Testing WaterError...")
    try:
        check_water(tomato)
    except WaterError as e:
        print(f"Caught WaterError: {e}")
    print()
    print("Testing catching all garden errors...")
    try:
        check_plant(tomato)
    except GardenError as e:
        print(f"Caught GardenError: {e}")
    try:
        check_water(tomato)
    except GardenError as e:
        print(f"Caught GardenError: {e}")
        print()
    print("All custom error types work correctly!")
