#!/usr/bin/env python3


class Plant:
    def __init__(self, name, height, age):
        self._name = name
        self._height = height
        self._age = age

    def show(self):
        print(f"{self._name.title()}: {self.get_height():.1f}cm, "
              f"{self.get_age():.0f} days old")

    def state(self):
        print(
            f"Current state: {self._name.title()}: {self.get_height():.1f}cm, "
            f"{self.get_age()} days old"
        )

    def set_height(self, new):
        if new >= 0:
            self._height = new
            print(f"Height updated: {self.get_height()}cm")
        else:
            print(f"{self._name.title()}: Error, height can't be negative")
            print("Height update rejected")

    def set_age(self, new):
        if new >= 0:
            self._age = new
            print(f"Age updated: {self.get_age()} days")
        else:
            print(f"{self._name.title()}: Error, age can't be negative")
            print("Age update rejected")

    def get_height(self):
        return self._height

    def get_age(self):
        return self._age


def ft_garden_security():
    rose = Plant("rOsE", 15, 10.0)

    print("=== Garden Security System ===")
    rose.show()
    print()
    rose.set_height(25)
    rose.set_age(30)
    print()
    rose.set_height(-1)
    rose.set_age(-1)
    print()
    rose.state()


if __name__ == "__main__":
    ft_garden_security()
