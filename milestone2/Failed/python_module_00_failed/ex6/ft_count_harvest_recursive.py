def ft_count_harvest_recursive():
    days_until = int(input("Days until harvest: "))
    count_down(1, days_until)


def count_down(count, days_until):
    if count <= days_until:
        print(f"Days {count}")
        count_down(count + 1, days_until)
    else:
        print("Harvest time!")
