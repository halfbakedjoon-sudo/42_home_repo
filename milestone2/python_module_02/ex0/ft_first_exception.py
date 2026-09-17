#!/usr/bin/env python3

def input_temperature(temp_str: str) -> int:
    return int(temp_str)


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
    test_value = ["25", "abc"]
    print("=== Garden Temperature ===")
    print()
    test_temperature(test_value)
    print("All tests completed - program didn't crash!")
