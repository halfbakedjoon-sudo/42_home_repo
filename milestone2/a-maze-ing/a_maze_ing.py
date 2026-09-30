#!/usr/bin/env python3
from pydantic import BaseModel, Field, model_validator, ValidationError


class Config(BaseModel):
    width: int = Field(ge=2, le=50)
    height: int = Field(ge=2, le=50)
    entry: tuple[int, int]
    exit: tuple[int, int]
    output_file: str = Field(min_length=4, max_length=20)
    perfect: bool

    @model_validator(mode="after")
    def config_check(self):
        x, y = self.entry
        v, w = self.exit
        if x > self.width or v > self.width:
            raise ValueError("Either entry or exit out of width range")
        if y > self.height or w > self.height:
            raise ValueError("Either entry or exit out of height range")
        return self


def parsing() -> None:
    try:
        with open("config.txt", "r") as fd:
            content = fd.read().splitlines()
        for line in content:
            if line.startswith("#"):
                content.remove(line)
        content_p: dict = {}
        for line in content:
            x, y = line.split("=")
            content_p[x] = y
        entry: tuple[int, int] = content_p["ENTRY"].split(",")
        exit: tuple[int, int] = content_p["EXIT"].split(",")
        config = Config(width=content_p["WIDTH"],
                        height=content_p["HEIGHT"],
                        entry=entry,
                        exit=exit,
                        output_file=content_p["OUTPUT_FILE"],
                        perfect=content_p["PERFECT"])
        print(config)
    except ValidationError as e:
        errors = str(e)
        print(e)
        print(errors.splitlines())


if __name__ == "__main__":
    parsing()
