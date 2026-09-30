#!/usr/bin/env python3
from pydantic import BaseModel, Field, ValidationError, model_validator
from datetime import datetime
from data_generator import AlienContactGenerator, DataConfig
from enum import Enum


class ContactType(str, Enum):
    RADIO = "radio"
    VISUAL = "visual"
    PHYSICAL = "physical"
    TELEPATHIC = "telepathic"


class Testing(BaseModel):
    contact_id: str = Field(min_length=5, max_length=15)
    timestamp: datetime
    location: str = Field(min_length=3, max_length=100)
    contact_type: ContactType
    signal_strength: float = Field(ge=0.0, le=10.0)
    duration_minutes: int = Field(ge=1, le=1440)
    witness_count: int = Field(ge=1, le=100)
    message_received: str | None = Field(max_length=500, default=None)
    is_verified: bool = False

    @model_validator(mode="after")
    def check_contact(self):
        if not isinstance(self.contact_type, ContactType):
            raise ValidationError("Unauthorized contact type!")
        if (self.contact_type == "physical" and
           self.is_verified is False):
            raise ValueError("Physical contact not verified!")
        if (self.contact_type == "telepathic" and
           self.witness_count < 3):
            raise ValueError("Telepathic contact requires at least 3"
                             " witnesses")
        if (self.signal_strength > 7.0 and
           not self.message_received):
            raise ValueError(f"Signal strong ({self.signal_strength}) but no"
                             " message received!")
        if not self.contact_id.startswith("AC"):
            raise ValueError("ID should start with 'AC'!")
        return self


def main():
    print()
    print("Alien Contact Log Validation")
    print("========================================")
    print("Valid contact report:")
    try:
        test = Testing(contact_id="AC_2024_001",
                       timestamp="2026-09-29",
                       location="Area 51, Nevada",
                       contact_type="radio",
                       signal_strength=8.5,
                       duration_minutes=45,
                       witness_count=5,
                       message_received="Greetings from Zeta Reticuli")

        print(f"ID: {test.contact_id}")
        print(f"Type: {test.contact_type.value}")
        print(f"Location: {test.location}")
        print(f"Signal: {test.signal_strength}/10")
        print(f"Duration.: {test.duration_minutes} minutes")
        print(f"Witness: {test.witness_count}")
        print(f"Message: '{test.message_received}'")
    except ValidationError as e:
        msg = e.errors()[0]["msg"]
        print(msg.removeprefix("Value error, "))

    print()
    print("========================================")
    print("Expected validation error:")
    try:
        test = Testing(contact_id="AC_2024_001",
                       timestamp="2026-09-29",
                       location="Area 51, Nevada",
                       contact_type="telepathic",
                       signal_strength=8.5,
                       duration_minutes=45,
                       witness_count=2,
                       message_received="Greetings from Zeta Reticuli")
    except ValidationError as e:
        msg = e.errors()[0]["msg"]
        print(msg.removeprefix("Value error, "))
    print()
    print("Expected validation error:")
    try:
        test = Testing(contact_id="AC_2024_001",
                       timestamp="2026-09-29",
                       location="Area 51, Nevada",
                       contact_type="physical",
                       signal_strength=8.5,
                       duration_minutes=45,
                       witness_count=2,
                       message_received="Greetings from Zeta Reticuli")
    except ValidationError as e:
        msg = e.errors()[0]["msg"]
        print(msg.removeprefix("Value error, "))
    print()
    print("Expected validation error:")
    try:
        test = Testing(contact_id="A_2024_001",
                       timestamp="2026-09-29",
                       location="Area 51, Nevada",
                       contact_type="radio",
                       signal_strength=8.5,
                       duration_minutes=45,
                       witness_count=5,
                       message_received="Greetings from Zeta Reticuli")
    except ValidationError as e:
        msg = e.errors()[0]["msg"]
        print(msg.removeprefix("Value error, "))
    print()
    print("Expected validation error:")
    try:
        test = Testing(contact_id="AC_2024_001",
                       timestamp="2026-09-29",
                       location="Area 51, Nevada",
                       contact_type="radio",
                       signal_strength=8.5,
                       duration_minutes=45,
                       witness_count=5,
                       message_received="")
    except ValidationError as e:
        msg = e.errors()[0]["msg"]
        print(msg.removeprefix("Value error, "))

    config = DataConfig()
    contact_gen = AlienContactGenerator(config)
    contacts = contact_gen.generate_contact_data(0)

    for contact in contacts:
        try:
            test = Testing(contact_id=contact['contact_id'],
                           timestamp=contact['timestamp'],
                           location=contact['location'],
                           contact_type=contact['contact_type'],
                           signal_strength=contact['signal_strength'],
                           duration_minutes=contact['duration_minutes'],
                           witness_count=contact['witness_count'],
                           message_received=contact['message_received'],
                           is_verified=contact['is_verified'])
            print()
            print("Alien Contact Log Validation")
            print("========================================")
            print("Valid contact report:")
            print(f"ID: {test.contact_id}")
            print(f"Time: {test.timestamp}")
            print(f"Location: {test.location}")
            print(f"Type: {test.contact_type.value}")
            print(f"Signal: {test.signal_strength}/10")
            print(f"Duration.: {test.duration_minutes} minutes")
            print(f"Witness: {test.witness_count}")
            print(f"Message: {test.message_received}")
            if test.is_verified:
                print("Status: Verified")
            else:
                print("Status: Unverified")
        except ValidationError as e:
            print(e.errors()[0]["msg"])


if __name__ == "__main__":
    main()
