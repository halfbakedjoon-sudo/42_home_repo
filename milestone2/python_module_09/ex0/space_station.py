#!/usr/bin/env python3
from pydantic import BaseModel, Field, ValidationError
from datetime import datetime
from data_generator import SpaceStationGenerator, DataConfig


class Testing(BaseModel):
    station_id: str = Field(min_length=3, max_length=10)
    name: str = Field(min_length=1, max_length=50)
    crew_size: int = Field(ge=1, le=20, strict=True)
    power_level: float = Field(ge=0.0, le=100.0)
    oxygen_level: float = Field(ge=0.0, le=100.0)
    last_maintenance: datetime
    is_operational: bool = True
    notes: str | None = Field(max_length=200, default=None, strict=True)


def main():
    try:
        test = Testing(station_id="ISS001",
                       name="International Space Station",
                       crew_size=6,
                       power_level=85.5,
                       oxygen_level=92.3,
                       last_maintenance="2026-09-28",
                       is_operational=True)
        print()
        print("Space Station Data Validation")
        print("========================================")
        print("Valid station created:")
        print(f"ID: {test.station_id}")
        print(f"Name: {test.name}")
        print(f"Crew: {test.crew_size} people")
        print(f"Power: {test.power_level}%")
        print(f"Oxygen: {test.oxygen_level}%")
        print(f"Last M.: {test.last_maintenance}")
        if test.is_operational:
            print("Status: Operational")
        else:
            print("Status: Non-operational")
    except ValidationError as e:
        print(e.errors()[0]["msg"])

    print()
    print("========================================")
    print("Expected validation error:")
    try:
        test2 = Testing(station_id="ISS001",
                        name="International Space Station",
                        crew_size=21,
                        power_level=85.5,
                        oxygen_level=92.3,
                        last_maintenance="2026-09-28",
                        is_operational=True)
        print()
        print("Space Station Data Validation")
        print("========================================")
        print("Valid station created:")
        print(f"ID: {test2.station_id}")
        print(f"Name: {test2.name}")
        print(f"Crew: {test2.crew_size} people")
        print(f"Power: {test2.power_level}%")
        print(f"Oxygen: {test2.oxygen_level}%")
        print(f"Last M.: {test2.last_maintenance}")
        if test2.is_operational:
            print("Status: Operational")
        else:
            print("Status: Non-operational")
    except ValidationError as e:
        print(e.errors()[0]["msg"])

    config = DataConfig()
    station_gen = SpaceStationGenerator(config)
    stations = station_gen.generate_station_data(2)
    print()
    print("Expected validation error:")
    for station in stations:
        try:
            test3 = Testing(station_id=station['station_id'],
                            name=station['name'],
                            crew_size=station['crew_size'],
                            power_level=station['power_level'],
                            oxygen_level=station['oxygen_level'],
                            last_maintenance=station['last_maintenance'],
                            is_operational=station['is_operational'])
            print()
            print("Space Station Data Validation")
            print("========================================")
            print("Valid station created:")
            print(f"ID: {test3.station_id}")
            print(f"Name: {test3.name}")
            print(f"Crew: {test3.crew_size} people")
            print(f"Power: {test3.power_level}%")
            print(f"Oxygen: {test3.oxygen_level}%")
            print(f"Last M.: {test3.last_maintenance}")
            if test3.is_operational:
                print("Status: Operational")
            else:
                print("Status: Non-operational")
        except ValidationError as e:
            print(e.errors()[0]["msg"])


if __name__ == "__main__":
    main()
