#!/usr/bin/env python3
import random


class Plant:
    def __init__(self, name, height, age, water_level):
        self.name = name
        self.height = height
        self.day = age
        self.water = water_level

    def grow(self):
        if self.name.title() == "Rose":
            self.height += 0.8
        elif self.name.title() == "Oak":
            if self.water > 4:
                growth = 20 / (self.height + 5)
                self.height += growth
            else:
                self.height = round(self.height +
                                    random.uniform(0.00, 1.00), 1)
            self.water -= 0.5

    def age(self):
        self.day += 1

    def age_and_grow(self):
        self.grow()
        self.age()

    def show(self):
        print(f"{self.name.title()}: {round(self.height, 1)}cm, "
              f"{self.day} days old")


def ft_plant_growth():
    rose = Plant("rOsE", round(25.0, 1), 30, 5)

    print("=== Garden Plant Growth ===")
    rose.show()
    original = rose.height
    for i in range(1, 8):
        rose.age_and_grow()
        print(f"=== Day {i} ===")
        rose.show()
    print(f"Growth this week: {round(rose.height - original, 1)}cm")


if __name__ == "__main__":
    ft_plant_growth()
