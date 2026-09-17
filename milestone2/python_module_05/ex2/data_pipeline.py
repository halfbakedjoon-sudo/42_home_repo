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
               typing.Sequence[dict[str, str]]]) -> None:
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
    # print(f"Numeric value {x}: {y}")


def text_rank_value(processor: TextProcessor) -> None:
    x, y = processor.output()
    # print(f"Text value {x}: {y}")


def log_rank_value(processor: LogProcessor) -> None:
    x, y = processor.output()
    # print(f"Log entry {x}: {y}")


class ExportPlugin(typing.Protocol):
    def process_output(self, data: list[tuple[int, str]]) -> None:
        pass


class CSVExporter:
    def process_output(self, data: list[tuple[int, str]]) -> None:
        values = []
        for entry in data:
            x, y = entry
            values.append(y)

        joined = ",".join(values)
        print(f"CSV Output:\n{joined}")


class JSONxporter:
    def process_output(self, data: list[tuple[int, str]]) -> None:
        values: dict[str, str] = {}
        for entry in data:
            x, y = entry
            values[f"item_{x}"] = y

        print(f"JSON Output:\n{values}")


class DataStream:
    def __init__(self) -> None:
        self.procs: list[DataProcessor] = []

    def register_processor(self, proc: DataProcessor) -> None:
        self.procs.append(proc)

    def process_stream(self, stream: list[typing.Any]) -> None:
        for entry in stream:
            try:
                for proc in self.procs:
                    if proc.validate(entry):
                        proc.ingest(entry)
                        break
                else:
                    raise TypeError(f"DataStream error - Can't process "
                                    f"element in stream: {entry}")
            except TypeError as e:
                print(f"{e}")

    def print_processors_stats(self) -> None:
        for proc in self.procs:
            if isinstance(proc, NumericProcessor):
                print(f"Numeric Processor: total {proc.rank} items processed, "
                      f"remaining {len(proc.storage)} on processor")
            elif isinstance(proc, TextProcessor):
                print(f"Text Processor: total {proc.rank} items processed, "
                      f"remaining {len(proc.storage)} on processor")
            elif isinstance(proc, LogProcessor):
                print(f"Log Processor: total {proc.rank} items processed, "
                      f"remaining {len(proc.storage)} on processor")
            else:
                return

    def output_pipeline(self, nb: int, plugin: ExportPlugin) -> None:
        for proc in self.procs:
            temp: list[tuple[int, str]] = []
            for i in range(nb):
                if proc.storage:
                    temp2 = proc.output()
                    temp.append(temp2)
            plugin.process_output(temp)


if __name__ == "__main__":
    processor = DataStream()

    numeric = NumericProcessor()
    text = TextProcessor()
    log = LogProcessor()

    print("=== Core Nexus - Data Pipeline ===\n")
    print("Initialize Data Stream...")
    processor = DataStream()

    print("=== DataStream statistics ===")
    print("No processor found, no data\n")

    print("Registering Processors\n")
    processor.register_processor(numeric)
    processor.register_processor(text)
    processor.register_processor(log)

    testdata = ['Hello world', [3.14, -1, 2.71],
                [{'log_level': 'WARNING',
                  'log_message': 'Telnet access! Use ssh instead'},
                 {'log_level': 'INFO',
                  'log_message': 'User wil is connected'}],
                42, ['Hi', 'five']]
    print(f"Send first batch of data on stream: {testdata}")
    processor.process_stream(testdata)
    print("== DataStream statistics ==")
    processor.print_processors_stats()

    print("\nSend 3 processed data from each processor to a CSV plugin:")
    processor.output_pipeline(3, CSVExporter())
    print("\n== DataStream statistics ==")
    processor.print_processors_stats()

    testdata2 = [21, ['I love AI', 'LLMs are wonderful', 'Stay healthy'],
                 [{'log_level': ' ERROR', 'log_message': '500 server crash'},
                  {'log_level': 'NOTICE', 'log_message': 'Certificate expires '
                  'in 10 days'}], [32, 42, 64, 84, 128, 168], 'World hello']
    print(f"\nSend another batch of data: {testdata2}")
    processor.process_stream(testdata2)

    print("\n== DataStream statistics ==")
    processor.print_processors_stats()
    print("\nSend 5 processed data from each processor to a JSON plugin:")
    processor.output_pipeline(5, JSONxporter())

    print("\n== DataStream statistics ==")
    processor.print_processors_stats()
