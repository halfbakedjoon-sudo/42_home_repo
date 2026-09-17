#!/usr/bin/env python3


def input_temperature(temp_str: str) -> int:
    value = int(temp_str)
    if value > 40:
        raise ValueError(f"{value}°C is too hot for plants (max 40°C)")
    elif value < 0:
        raise ValueError(f"{value}°C is too cold for plants (min 0°C)")
    return value


def test_temperature(test_value: list[str]) -> None:
    for value in test_value:
        try:
            print(f"Input data is '{value}'")
            result = input_temperature(value)
            print(f"Temperature is now {result}°C")
            print()
        except ValueError as e:
            print(f"Caught input_temperature error: {e}")
            print()


if __name__ == "__main__":
    test_value = ["25", "abc", "100", "-50"]
    print("=== Garden Temperature Checker ===")
    print()
    test_temperature(test_value)
    print("All tests completed - program didn't crash!")
