#!/usr/bin/env python3


class Plant:
    def __init__(self, name, height, age):
        if height < 0 or age < 0:
            raise ValueError("Input error!")
        self._name = name
        self._height = height
        self._age = age

    def show(self):
        print(
            f"{self.get_name().title()}: {self._height:.1f}cm, "
            f"{self._age} days old"
        )

    def get_height(self):
        return self._height

    def get_age(self):
        return self._age

    def get_name(self):
        return self._name


class Flower(Plant):
    def __init__(self, name, height, age, color):
        super().__init__(name, height, age)
        self._color = color

    def get_color(self):
        return self._color

    def show(self):
        super().show()
        print(f" Color: {self.get_color().lower()}")
        print(f" {self.get_name().title()} has not bloomed yet")

    def bloom(self):
        print(f"[asking the {self.get_name().lower()} to bloom]")
        super().show()
        print(f" Color: {self.get_color().lower()}")
        print(f" {self.get_name().title()} is blooming beautifully!")


class Tree(Plant):
    def __init__(self, name, height, age, trunk_diameter):
        super().__init__(name, height, age)
        self._diameter = trunk_diameter

    def get_diameter(self):
        return self._diameter

    def show(self):
        super().show()
        print(f" Trunk diameter: {self.get_diameter():.1f}cm")

    def produce_shade(self):
        print(f"[asking the {self._name.lower()} to produce shade]")
        print(
            f"Tree {self.get_name().lower()} now produces a shade of "
            f"{self.get_height():.1f}cm "
            f"long and {self.get_diameter():.1f}cm wide."
        )


class Vegetable(Plant):
    def __init__(self, name, height, age, harvest_season, nutritional_value):
        super().__init__(name, height, age)
        self._harvest = harvest_season
        self._nutri = nutritional_value

    def get_harvest(self):
        return self._harvest

    def get_nutri(self):
        return self._nutri

    def show(self):
        super().show()
        print(f" Harvest season: {self.get_harvest().title()}")
        print(f" Nutritional value: {self.get_nutri()}")

    def age(self, value):
        self._age += value

    def grow(self):
        self._height += 42

    def up_nutri(self, value):
        self.grow()
        self.age(value)
        self._nutri += value
        print(
            f"[make {self.get_name().lower()} "
            f"grow and age for {value} days]"
        )
        self.show()


def ft_plant_types():
    rose = Flower("rOsE", 15, 10, "rEd")
    oak = Tree("oAk", 200, 365, 5)
    tomato = Vegetable("tOmAtO", 5, 10, "aPrIl", 0)

    print("=== Garden Plant Type ===")
    print("=== Flower")
    rose.show()
    rose.bloom()
    print()
    print("=== Tree")
    oak.show()
    oak.produce_shade()
    print()
    print("=== Vegetable")
    tomato.show()
    tomato.up_nutri(20)


if __name__ == "__main__":
    ft_plant_types()
