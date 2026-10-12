#!/usr/bin/env python3
from pydantic import BaseModel, Field, ValidationError
from datetime import datetime
from data_generator import SpaceStationGenerator, DataConfig


class Testing(BaseModel):
    station_id: str = Field(min_length=3, max_length=10)
    name: str = Field(min_length=1, max_length=50)
    crew_size: int = Field(ge=1, le=20)
    power_level: float = Field(ge=0.0, le=100.0)
    oxygen_level: float = Field(ge=0.0, le=100.0)
    last_maintenance: datetime
    is_operational: bool = True
    notes: str | None = Field(max_length=200, default=None, strict=True)


def space_station(station: dict[str, str]) -> None:
    try:
        test = Testing(**station)
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


def main() -> None:
    station1: dict[str, str] = {"station_id": "ISS001",
                                "name": "International Space Station",
                                "crew_size": "6",
                                "power_level": "85.5",
                                "oxygen_level": "92.3",
                                "last_maintenance": "2026-09-28",
                                "is_operational": "True"}
    station2: dict[str, str] = {"station_id": "ISS001",
                                "name": "International Space Station",
                                "crew_size": "21",
                                "power_level": "85.5",
                                "oxygen_level": "92.3",
                                "last_maintenance": "2026-09-28",
                                "is_operational": "True"}
    space_station(station1)
    print()
    print("========================================")
    print("Expected validation error:")
    space_station(station2)


def main2() -> None:
    config = DataConfig()
    station_gen = SpaceStationGenerator(config)
    stations = station_gen.generate_station_data(5)
    for station in stations:
        space_station(station)


if __name__ == "__main__":
    main()
    main2()
