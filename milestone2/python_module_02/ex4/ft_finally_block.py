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


def water_plant(plant_name: str) -> str:
    try:
        for plant in plant_name:
            str(plant)
    except TypeError:
        raise
    if plant_name == plant_name.capitalize():
        return (f"Watering {plant_name}: [OK]")
    else:
        raise PlantError(f"Invalid plant name to water: '{plant_name}'")


def test_watering_system(test_plants: list[str]) -> None:
    print("Opening watering system")
    try:
        for plants in test_plants:
            print(f"{water_plant(plants)}")
    except PlantError as e:
        print(f"Caught PlantError: {e}")
        print(".. ending tests and returning to main")
    except TypeError as e:
        print(f"Caught PlantError: {e}")
        print(f"Invalid plant name to water: '{plants}'")
        print(".. ending tests and returning to main")
    finally:
        print("Closing watering system")


if __name__ == "__main__":
    valid_plants = ["Tomato", "Lettuce", "Carrots"]
    invalid_plants = ["Tomato", "lettuce", "Carrots"]
    print("=== Garden Watering System ===")
    print()
    print("Testing valid plants...")
    test_watering_system(valid_plants)
    print()
    print("Testing invalid plants...")
    test_watering_system(invalid_plants)
    print()
    print("Cleanup always happens, even with errors!")
