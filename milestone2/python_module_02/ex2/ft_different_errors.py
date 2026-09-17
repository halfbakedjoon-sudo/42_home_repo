#!/usr/bin/env python3


def garden_operations(operation_number: int) -> None:
    if operation_number == 0:
        int("abc")
    elif operation_number == 1:
        10 / 0
    elif operation_number == 2:
        open("/non/existent/file")
    elif operation_number == 3:
        "str" + 123
    else:
        return


def test_error_types(value: int) -> None:
    try:
        print(f"Testing operation {value}...")
        garden_operations(value)
    except ValueError as e:
        print(f"Caught ValueError: {e}")
    except ZeroDivisionError as e:
        print(f"Caught ZeroDivisionError: {e}")
    except FileNotFoundError as e:
        print(f"Caught FileNotFoundError: {e}")
    except TypeError as e:
        print(f"Caught TypeError: {e}")


if __name__ == "__main__":
    value = [0, 1, 2, 3, 4]
    print("=== Garden Error Types Demo ===")
    for i in value:
        test_error_types(i)
    print("Operation completed successfully!")
    print("\nAll error types tested successfully!")
