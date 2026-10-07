from pydantic import BaseModel, Field, model_validator, ValidationError
import sys


class Config(BaseModel):
    width: int = Field(ge=2, le=50)
    height: int = Field(ge=2, le=50)
    entry: tuple[int, int]
    exit: tuple[int, int]
    output_file: str = Field(min_length=4, max_length=20)
    perfect: bool
    speed: float = 0.01
    solver: str = "BFS"

    @model_validator(mode="after")
    def config_check(self):
        x, y = self.entry
        v, w = self.exit
        if x >= self.width or v >= self.width:
            raise ValueError("Either entry or exit out of width range")
        if y >= self.height or w >= self.height:
            raise ValueError("Either entry or exit out of height range")
        if x is v and y is w:
            raise ValueError("Entry and exit cannot be the same")
        if self.solver not in ["BFS", "DFS"]:
            raise ValueError("Invalid solver")
        return self



def parsing() -> Config:
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
    except ValidationError as errors:
        for error in errors.errors():
            if error["loc"]:
                error_type = str(error["loc"][0])
                print(f'{error_type.capitalize()} - ', end="")
            msg = error["msg"].removeprefix("Value error, ")
            print(msg)
            sys.exit(1)
    return config
