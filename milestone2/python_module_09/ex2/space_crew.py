from pydantic import BaseModel, model_validator, Field, ValidationError
from enum import Enum
from datetime import datetime
import json


class Rank(str, Enum):
    CADET = "cadet"
    OFFICER = "officer"
    LIEUTENANT = "lieutenant"
    CAPTAIN = "captain"
    COMMANDER = "commander"


class CrewMember(BaseModel):
    member_id: str = Field(min_length=3, max_length=10)
    name: str = Field(min_length=2, max_length=50)
    rank: Rank
    age: int = Field(ge=18, le=80)
    specialization: str = Field(min_length=3, max_length=30)
    years_experience: int = Field(ge=0, le=50)
    is_active: bool = True


class SpaceMission(BaseModel):
    mission_id: str = Field(min_length=5, max_length=15)
    mission_name: str = Field(min_length=3, max_length=100)
    destination: str = Field(min_length=3, max_length=50)
    launch_date: datetime
    duration_days: int = Field(ge=1, le=3650)
    crew: list[CrewMember] = Field(min_length=1, max_length=12)
    mission_status: str = "Planned"
    budget_millions: float = Field(ge=1.0, le=10000.0)

    @model_validator(mode='after')
    def check(self):
        mode = 0
        if not self.mission_id.startswith("M"):
            raise ValueError("Mission ID must start with 'M'")
        for individual in self.crew:
            if individual.rank.value in ("commander", "captain"):
                mode += 1
        if not mode:
            raise ValueError("Mission must have at least one Commander or"
                             " Captain")
        if self.duration_days > 365:
            old = 0
            for crew in self.crew:
                if crew.years_experience > 5:
                    old += 1
            if not old >= len(self.crew):
                raise ValueError("Mission must have more than 50% "
                                 "experienced crew (5+ years)")
        for crew in self.crew:
            if not crew.is_active:
                raise ValueError("All crew meembers must be active")
        return self


def space_crew(mission: dict) -> None:
    try:
        test = SpaceMission(**mission)
        print(f"Mission: {test.mission_name}")
        print(f"ID: {test.mission_id}")
        print(f"Destination: {test.destination}")
        print(f"Duration: {test.duration_days} days")
        print(f"Budget: ${test.budget_millions}M")
        print(f"Crew size: {len(test.crew)}")
        print("Crew members:")
        for crew in test.crew:
            print(f"- {crew.name} ({crew.rank.value}) - {crew.specialization}")
    except ValidationError as e:
        msg = e.errors()[0]["msg"]
        print(msg.removeprefix("Value error, "))
    print()


def main() -> None:
    crews1: list[dict[str, str]] = [{"member_id": "001",
                                    "name": "Sarah Connor",
                                     "rank": "commander",
                                     "age": "40",
                                     "specialization": "Mission Command",
                                     "years_experience": "10",
                                     "is_active": "True"},
                                    {"member_id": "002",
                                    "name": "John Smith",
                                     "rank": "lieutenant",
                                     "age": "40",
                                     "specialization": "Navigation",
                                     "years_experience": "10",
                                     "is_active": "True"},
                                    {"member_id": "003",
                                    "name": "Alice Johnson",
                                     "rank": "officer",
                                     "age": "40",
                                     "specialization": "Engineering",
                                     "years_experience": "10",
                                     "is_active": "True"}]

    mission1 = {"mission_id": "M2024_MARS",
                "mission_name": "Mars Colony Establishment",
                "destination": "Mars",
                "launch_date": "2026-09-29",
                "duration_days": "900",
                "crew": crews1,
                "budget_millions": "2500.0"}

    crews2: list[dict[str, str]] = [{"member_id": "001",
                                     "name": "Sarah Connor",
                                     "rank": "officer",
                                     "age": "40",
                                     "specialization": "Mission Command",
                                     "years_experience": "10",
                                     "is_active": "True"},
                                    {"member_id": "002",
                                     "name": "John Smith",
                                     "rank": "lieutenant",
                                     "age": "40",
                                     "specialization": "Navigation",
                                     "years_experience": "10",
                                     "is_active": "True"},
                                    {"member_id": "003",
                                     "name": "Alice Johnson",
                                     "rank": "officer",
                                     "age": "40",
                                     "specialization": "Engineering",
                                     "years_experience": "10",
                                     "is_active": "True"}]

    mission2 = {"mission_id": "M2024_MARS",
                "mission_name": "Mars Colony Establishment",
                "destination": "Mars",
                "launch_date": "2026-09-29",
                "duration_days": "900",
                "crew": crews2,
                "budget_millions": "2500.0"}

    print("Space Mission Crew Validation")
    print("=========================================")
    print("Valid mission created:")
    space_crew(mission1)
    print("=========================================")
    print("Expected validation error:")
    space_crew(mission2)


def main2() -> None:
    try:
        from data_generator import CrewMissionGenerator, DataConfig
        config = DataConfig()
        space_gen = CrewMissionGenerator(config)
        missions = space_gen.generate_mission_data(2)
        for mission in missions:
            print("Space Mission Crew Validation")
            print("=========================================")
            print("Valid mission created:")
            space_crew(mission)
    except Exception as e:
        print(e)


def main4() -> None:
    try:
        with open("../generated_data/space_missions.json") as f:
            datas = json.load(f)

        for data in datas:
            print("Space Mission Crew Validation")
            print("=========================================")
            print("Valid mission created:")
            space_crew(data)
    except Exception as e:
        print(e)


if __name__ == "__main__":
    main()
    main2()
    main4()
