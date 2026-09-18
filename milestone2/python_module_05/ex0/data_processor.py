#!/usr/bin/env python3
import typing
import abc


class DataProcessor(abc.ABC):
    def __init__(self) -> None:
        self.storage: list[tuple[int, str]] = []
        self.rank = 0

    @abc.abstractmethod
    def validate(self, data: typing.Any) -> bool:
        pass

    @abc.abstractmethod
    def ingest(self, data: typing.Any) -> None:
        pass

    def output(self) -> tuple[int, str]:
        oldest = self.storage.pop(0)
        return oldest


class NumericProcessor(DataProcessor):
    def validate(self, data: typing.Any) -> bool:
        if isinstance(data, (int, float)):
            return True
        elif isinstance(data, list):
            return all((isinstance(x, (int, float)) for x in data))
        return False

    def ingest(self, data: int | float | list[int] | list[float] |
               list[int | float]) -> None:
        try:
            if not self.validate(data):
                raise TypeError(" Got exception: Improper numeric data")
            if isinstance(data, list):
                for num in data:
                    self.storage.append((self.rank, str(num)))
                    self.rank += 1
            else:
                self.storage.append((self.rank, str(data)))
                self.rank += 1
        except TypeError as e:
            print(f"{e}")


class TextProcessor(DataProcessor):
    def validate(self, data: typing.Any) -> bool:
        if isinstance(data, str):
            return True
        elif isinstance(data, list):
            return all(isinstance(x, str) for x in data)
        else:
            return False

    def ingest(self, data: str | list[str]) -> None:
        try:
            if not self.validate(data):
                raise TypeError(" Got exception: Improper text data")
            if isinstance(data, list):
                for string in data:
                    self.storage.append((self.rank, str(string)))
                    self.rank += 1
            else:
                self.storage.append((self.rank, str(data)))
                self.rank += 1
        except TypeError as e:
            print(f"{e}")


class LogProcessor(DataProcessor):
    def validate(self, data: typing.Any) -> bool:
        if isinstance(data, dict):
            return (
                    all(isinstance(x, str) for x in data.keys())
                    and all(isinstance(y, str) for y in data.values())
                    )
        elif isinstance(data, list):
            for z in data:
                if isinstance(z, dict):
                    if not (
                        all(isinstance(x, str) for x in z.keys())
                        and all(isinstance(y, str) for y in z.values())
                    ):
                        return False
                else:
                    return False
            return True
        else:
            return False

    def ingest(self, data: typing.Union[dict[str, str],
               list[dict[str, str]]]) -> None:
        try:
            if not self.validate(data):
                raise TypeError(" Got exception: Improper log data")
            if isinstance(data, list):
                for entry in data:
                    self.storage.append((self.rank, ": ".join(entry.values())))
                    self.rank += 1
            else:
                self.storage.append((self.rank, ": ".join(entry.values())))
                self.rank += 1
        except TypeError as e:
            print(f"{e}")


def numeric_rank_value(processor: NumericProcessor) -> None:
    x, y = processor.output()
    print(f"Numeric value {x}: {y}")


def text_rank_value(processor: TextProcessor) -> None:
    x, y = processor.output()
    print(f"Text value {x}: {y}")


def log_rank_value(processor: LogProcessor) -> None:
    x, y = processor.output()
    print(f"Log entry {x}: {y}")


if __name__ == "__main__":
    data1 = [1, 2, 3, 4, 5]
    data2 = ['Hello', 'Nexus', 'World']
    data3 = [{'log_level': 'NOTICE', 'log_message': 'Connection to server'},
             {'log_level': 'ERROR', 'log_message': 'Unauthorized access!!'}]

    numeric = NumericProcessor()
    text = TextProcessor()
    log = LogProcessor()

    print("=== Core Nexus - Data Processor ===\n")
    print("Testing Numeric Processor...")
    print(f" Trying to validate input '42': {numeric.validate(42)}")
    print(f" Trying to validate input 'Hello': {numeric.validate('Hello')}")
    print(" Test invalid ingestion of string 'foo' without prior validation:")
    numeric.ingest("foo")
    print(f" Processing data: {data1}")
    numeric.ingest(data1)
    print(" Extracting 3 values...")
    for i in range(3):
        numeric_rank_value(numeric)

    print("\nTesting Text Processor...")
    print(f" Trying to validate input '42': {text.validate(42)}")
    print(f" Processing data: {data2}")
    text.ingest(data2)
    print(" Extracting 1 value...")
    for i in range(1):
        text_rank_value(text)

    print("\nTesting Log Processor...")
    print(f" Trying to validate input 'Hello': {log.validate('Hello')}")
    log.ingest(data3)
    for i in range(2):
        log_rank_value(log)

    print("\n=== Testing Extra Stuffs ===")
    print("\nTesting Extra Numeric Processor...")
    print(" Test invalid ingestion of list '42, 24, \"Hello\"' "
          "without prior validation:")
    numeric.ingest([42, 24, "Hello"])
    print(" Test with a list with mix of int and float "
          "'42, 24.0, 50, 33.5")
    print(f" {numeric.validate([42, 24.0, 50, 33.5])}")
    numeric.ingest([42, 24.0, 50, 33.5])
    for i in range(6):
        numeric_rank_value(numeric)

    print("\nTesting Extra Text Processor...")
    print(" Test invalid ingestion of int '42' without prior validation:")
    text.ingest(42)
    print(" Test invalid ingestion of list '42, 24, \"Hello\"' "
          "without prior validation:")
    text.ingest([42, 24, "Hello"])

    print("\nTesting Extra Log Processor...")
    print(" Test invalid ingestion of dict ['key': 42] "
          "without prior validation: ")
    log.ingest([{'key': 42}])
    print(" Test invalid ingestion list of dict ['key': '42'], ['key2']: 42 "
          "without prior validation: ")
    log.ingest([{'key': '42', 'key2': 42}])
