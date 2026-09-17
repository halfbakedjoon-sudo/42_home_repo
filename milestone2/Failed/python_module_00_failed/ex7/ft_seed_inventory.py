def ft_seed_inventory(seed_type: str, quantity: int, unit: str) -> None:
    unit_type = ["packets", "grams", "area"]
    if unit not in unit_type:
        print("Unknown unit type")
        return

    print(f"{seed_type.title()} seeds: {quantity} {unit} ", end="")
    if unit == "packets":
        print("available")
    if unit == "grams":
        print("total")
    if unit == "area":
        print("square meters")
