#!/usr/bin/env python3


class Plant:
    def __init__(self, name, starting_height, starting_age):
        self.name = name
        self.height = starting_height
        self.day = starting_age

    def age(self):
        self.day += 1

    def age_and_grow(self):
        self.grow()
        self.age()

    def show(self):
        print(f"{self.name.title()}: {self.height:.1f}cm, "
              f"{self.day:.0f} days old")


def ft_plant_factory():
    rose = Plant("rOsE", 25, 30.0)
    oak = Plant("oAk", 200, 365)
    cactus = Plant("cAcTuS", 5, 90)
    sunflower = Plant("sUnFlOwEr", 80, 45)
    fern = Plant("fErN", 15, 120)

    print("=== Plant Factory Output ===")
    print("Created: ", end="")
    rose.show()
    print("Created: ", end="")
    oak.show()
    print("Created: ", end="")
    cactus.show()
    print("Created: ", end="")
    sunflower.show()
    print("Created: ", end="")
    fern.show()


if __name__ == "__main__":
    ft_plant_factory()
