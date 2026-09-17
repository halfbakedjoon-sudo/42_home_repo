#!/usr/bin/env python3


class Plant:
    class Stats:
        def __init__(self):
            self.grow_count = 0
            self.age_count = 0
            self.show_count = 0

        def show(self):
            print(f"Stats: {self.grow_count} grow, "
                  f"{self.age_count} age, "
                  f"{self.show_count} show")

    def __init__(self, name, height, day):
        self._name = name
        self._height = height
        self._age = day
        self.stats = self.Stats()

    def show(self):
        print(
            f"{self.get_name().capitalize()}: {self._height:.1f}cm, "
            f"{self._age} days old"
        )
        self.stats.show_count += 1

    def get_height(self):
        return self._height

    def get_age(self):
        return self._age

    def get_name(self):
        return self._name

    def grow(self, value):
        self._height += value
        self.stats.grow_count += 1

    def age(self, value):
        self._age += value
        self.stats.age_count += 1

    @staticmethod
    def is_365(age):
        print(f"Is {age} days more than a year?", end="")
        if age > 365:
            print(" -> True")
        else:
            print(" -> False")

    @classmethod
    def anonymous(cls):
        return cls("Unknown plant", 0.0, 0)


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
        super().show()
        print(f" Color: {self.get_color().lower()}")
        print(f" {self.get_name().title()} is blooming beautifully!")

    def grow_bloom(self, value):
        print(f"[asking the {self.get_name().lower()} to grow and bloom]")
        self.grow(value)
        self.bloom()


class Seed(Flower):
    def __init__(self, name, height, age, color, seed):
        super().__init__(name, height, age, color)
        self._seed = seed

    def get_seed(self):
        return self._seed

    def show(self):
        super().show()
        print(f" Seeds: {self.get_seed()}")

    def bloom(self):
        super().bloom()
        print(f" Seeds: {self.get_seed()}")

    def GAB(self, value_grow, value_age, value_seed):
        print(f"[make {self.get_name().lower()} grow, age and bloom]")
        self.grow(value_grow)
        self.age(value_age)
        self._seed += value_seed
        self.bloom()


class Tree(Plant):
    class Stats(Plant.Stats):
        def __init__(self):
            super().__init__()
            self._shade_count = 0

        def show(self):
            super().show()
            print(f" {self.get_shade_count()} shade")

        def get_shade_count(self):
            return self._shade_count

    def __init__(self, name, height, age, trunk_diameter):
        super().__init__(name, height, age)
        self._diameter = trunk_diameter

    def get_diameter(self):
        return self._diameter

    def show(self):
        super().show()
        print(f" Trunk diameter: {self.get_diameter():.1f}cm")

    def produce_shade(self):
        self.stats._shade_count += 1
        print(f"[asking the {self._name.lower()} to produce shade]")
        print(
            f"Tree {self.get_name().title()} now produces a shade of "
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


def output_stats(plant):
    print(f"[statistics for {plant.get_name().capitalize()}]")
    plant.stats.show()


def ft_garden_analytics():
    rose = Flower("rOsE", 15, 10, "rEd")
    oak = Tree("oAk", 200, 365, 5)
    sunflower = Seed("sUnFloWeR", 80, 45, "yellow", 0)
    whatthefuck = Plant.anonymous()

    print("=== Garden statistics ===")
    print("=== Check year-old")
    Plant.is_365(30)
    Plant.is_365(400)
    print()
    print("=== Flower")
    rose.show()
    output_stats(rose)
    rose.grow_bloom(8)
    output_stats(rose)
    print()
    print("=== Tree")
    oak.show()
    output_stats(oak)
    oak.produce_shade()
    output_stats(oak)
    print()
    print("=== Seed")
    sunflower.show()
    sunflower.GAB(30, 20, 42)
    output_stats(sunflower)
    print()
    print("=== Anonymous")
    whatthefuck.show()
    output_stats(whatthefuck)


if __name__ == "__main__":
    ft_garden_analytics()
