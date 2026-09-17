def ft_seed_inventory(seed_type: str, quantity: int, unit: str) -> None:
    unit_type = ["packets", "grams", "area"]
    if unit not in unit_type:
        print("Unknown unit type")
        return

    if unit == "packets":
        print(f"{seed_type.title()} seeds: {quantity} {unit} available")
    elif unit == "grams":
        print(f"{seed_type.title()} seeds: {quantity} {unit} total")
    elif unit == "area":
        print(f"{seed_type.title()} seeds: covers {quantity} square meters")
