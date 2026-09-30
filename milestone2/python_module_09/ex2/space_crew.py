from pydantic import BaseModel, model_validator, Field, ValidationError
from enum import Enum
from datetime import datetime
from data_generator import CrewMissionGenerator, DataConfig


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


def main() -> None:
    config = DataConfig()
    space_gen = CrewMissionGenerator(config)
    missions = space_gen.generate_mission_data(2)
    print()
    print("Space Mission Crew Validation")
    print("=========================================")
    print("Valid mission created:")
    crews: list[CrewMember] = []
    try:
        for crew in missions[0]['crew']:
            crews.append(CrewMember(member_id=crew['member_id'],
                                    name=crew['name'],
                                    rank=crew['rank'],
                                    age=crew['age'],
                                    specialization=crew['specialization'],
                                    years_experience=crew['years_experience'],
                                    is_active=crew['is_active']))

        test = SpaceMission(mission_id="M2024_MARS",
                            mission_name="Mars Colony Establishment",
                            destination="Mars",
                            launch_date="2026-09-29",
                            duration_days=900,
                            crew=crews,
                            budget_millions=2500.0)
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
    print("=========================================")
    print("Expected validation error:")
    crews2: list[CrewMember] = []
    try:
        for crew in missions[1]['crew']:
            crews2.append(CrewMember(member_id=crew['member_id'],
                                     name=crew['name'],
                                     rank="cadet",
                                     age=crew['age'],
                                     specialization=crew['specialization'],
                                     years_experience=crew['years_experience'],
                                     is_active=crew['is_active']))
        test = SpaceMission(mission_id="M2024_MARS",
                            mission_name="Mars Colony Establishment",
                            destination="Mars",
                            launch_date="2026-09-29",
                            duration_days=900,
                            crew=crews2,
                            budget_millions=2500.0)
    except ValidationError as e:
        msg = e.errors()[0]["msg"]
        print(msg.removeprefix("Value error, "))
    print()
    crews3: list[CrewMember] = []
    try:
        for crew in missions[1]['crew']:
            crews3.append(CrewMember(member_id=crew['member_id'],
                                     name=crew['name'],
                                     rank=crew['rank'],
                                     age=crew['age'],
                                     specialization=crew['specialization'],
                                     years_experience=1,
                                     is_active=crew['is_active']))
        test = SpaceMission(mission_id="M2024_MARS",
                            mission_name="Mars Colony Establishment",
                            destination="Mars",
                            launch_date="2026-09-29",
                            duration_days=900,
                            crew=crews3,
                            budget_millions=2500.0)
    except ValidationError as e:
        msg = e.errors()[0]["msg"]
        print(msg.removeprefix("Value error, "))
    print()
    crews4: list[CrewMember] = []
    try:
        for crew in missions[1]['crew']:
            crews4.append(CrewMember(member_id=crew['member_id'],
                                     name=crew['name'],
                                     rank=crew['rank'],
                                     age=crew['age'],
                                     specialization=crew['specialization'],
                                     years_experience=crew['years_experience'],
                                     is_active=False))
        test = SpaceMission(mission_id="M2024_MARS",
                            mission_name="Mars Colony Establishment",
                            destination="Mars",
                            launch_date="2026-09-29",
                            duration_days=900,
                            crew=crews4,
                            budget_millions=2500.0)
    except ValidationError as e:
        msg = e.errors()[0]["msg"]
        print(msg.removeprefix("Value error, "))
    print()
    crews5: list[CrewMember] = []
    try:
        for crew in missions[1]['crew']:
            crews5.append(CrewMember(member_id=crew['member_id'],
                                     name=crew['name'],
                                     rank=crew['rank'],
                                     age=crew['age'],
                                     specialization=crew['specialization'],
                                     years_experience=crew['years_experience'],
                                     is_active=crew['is_active']))
        test = SpaceMission(mission_id="2024_MARS",
                            mission_name="Mars Colony Establishment",
                            destination="Mars",
                            launch_date="2026-09-29",
                            duration_days=900,
                            crew=crews5,
                            budget_millions=2500.0)
    except ValidationError as e:
        msg = e.errors()[0]["msg"]
        print(msg.removeprefix("Value error, "))

    # for mission in missions:
    #     try:
    #         for crew in mission['crew']:
    #             crews.append(CrewMember(
    #                 member_id=crew['member_id'],
    #                 name=crew['name'],
    #                 rank=crew['rank'],
    #                 age=crew['age'],
    #                 specialization=crew['specialization'],
    #                 years_experience=crew['years_experience'],
    #                 is_active=crew['is_active']))

    #         test = SpaceMission(mission_id=mission['mission_id'],
    #                             mission_name=mission['mission_name'],
    #                             destination=mission['destination'],
    #                             launch_date=mission['launch_date'],
    #                             duration_days=mission['duration_days'],
    #                             crew=mission['crew'],
    #                             mission_status=mission['mission_status'],
    #                             budget_millions=mission['budget_millions'])
    #         print()
    #         print(f"Mission: {test.mission_name}")
    #         print(f"ID: {test.mission_id}")
    #         print(f"Destination: {test.destination}")
    #         print(f"Duration: {test.duration_days} days")
    #         print(f"Budget: ${test.budget_millions}M")
    #         print(f"Crew size: {len(test.crew)}")
    #         print("Crew members:")
    #         for crew in test.crew:
    #             print(f"- {crew.name} ({crew.rank.value}) - "
    #                   f"{crew.specialization}")
    #     except ValidationError as e:
    #         print(e.errors()[0]["msg"])


if __name__ == "__main__":
    main()
