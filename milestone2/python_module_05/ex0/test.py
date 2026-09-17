import abc
import typing


class DataProcessor(abc.ABC):
    """Common interface shared by all data processors."""

    def __init__(self) -> None:
        self.storage: list[tuple[int, str]] = []
        self._next_rank: int = 1

    @abc.abstractmethod
    def validate(self, data: typing.Any) -> bool:
        """Return True if `data` can be ingested by this processor."""
        ...

    @abc.abstractmethod
    def ingest(self, data: typing.Any) -> None:
        """Process and store `data`. Must raise if data is invalid."""
        ...

    def _store(self, value: str) -> None:
        """Shared helper: append one converted item with an incrementing rank."""
        self.storage.append((self._next_rank, value))
        self._next_rank += 1

    def output(self) -> tuple[int, str]:
        """Extract and remove the oldest stored item, with its rank."""
        if not self.storage:
            raise IndexError("No data available to output.")
        return self.storage.pop(0)


class NumericProcessor(DataProcessor):
    def validate(self, data: typing.Any) -> bool:
        if isinstance(data, bool):
            return False
        if isinstance(data, (int, float)):
            return True
        if isinstance(data, list):
            return all(
                isinstance(x, (int, float)) and not isinstance(x, bool)
                for x in data
            )
        return False

    def ingest(self, data: typing.Union[int, float, typing.Sequence[typing.Union[int, float]]]) -> None:
        if not self.validate(data):
            raise TypeError(f"Invalid data for NumericProcessor: {data!r}")

        if isinstance(data, list):
            for number in data:
                self._store(str(number))
        else:
            self._store(str(data))


class TextProcessor(DataProcessor):
    def validate(self, data: typing.Any) -> bool:
        if isinstance(data, str):
            return True
        if isinstance(data, list):
            return all(isinstance(x, str) for x in data)
        return False

    def ingest(self, data: typing.Union[str, typing.Sequence[str]]) -> None:
        if not self.validate(data):
            raise TypeError(f"Invalid data for TextProcessor: {data!r}")

        if isinstance(data, str):
            self._store(data)
        else:
            for text in data:
                self._store(text)


class LogProcessor(DataProcessor):
    def validate(self, data: typing.Any) -> bool:
        def is_str_dict(d: typing.Any) -> bool:
            return (
                isinstance(d, dict)
                and all(isinstance(k, str) for k in d.keys())
                and all(isinstance(v, str) for v in d.values())
            )

        if is_str_dict(data):
            return True
        if isinstance(data, list):
            return all(is_str_dict(entry) for entry in data)
        return False

    def ingest(
        self,
        data: typing.Union[typing.Dict[str, str], typing.Sequence[typing.Dict[str, str]]],
    ) -> None:
        if not self.validate(data):
            raise TypeError(f"Invalid data for LogProcessor: {data!r}")

        if isinstance(data, list):
            for entry in data:
                self._store(str(entry))
        else:
            self._store(str(data))


if __name__ == "__main__":
    numeric = NumericProcessor()
    text = TextProcessor()
    log = LogProcessor()

    print("--- validate() checks ---")
    print("Numeric valid (int):", numeric.validate(42))
    print("Numeric valid (list mixed):", numeric.validate([1, 2.5, 3]))
    print("Numeric invalid (str):", numeric.validate("42"))
    print("Numeric invalid (list w/ str):", numeric.validate([1, "two"]))

    print("Text valid (str):", text.validate("hello"))
    print("Text valid (list):", text.validate(["a", "b"]))
    print("Text invalid (int):", text.validate(123))
    print("Text invalid (list w/ int):", text.validate(["a", 2]))

    print("Log valid (dict):", log.validate({"level": "INFO", "msg": "ok"}))
    print("Log valid (list of dicts):", log.validate([{"a": "1"}, {"b": "2"}]))
    print("Log invalid (non-str value):", log.validate({"level": 5}))
    print("Log invalid (not a dict):", log.validate(["not", "a", "dict"]))

    print("\n--- ingest() without validate: exception expected ---")
    try:
        numeric.ingest("not a number")  # type: ignore[arg-type]
    except TypeError as e:
        print("Caught expected exception:", e)

    print("\n--- ingest() valid data ---")
    numeric.ingest(10)
    numeric.ingest([1, 2.5, 3])
    text.ingest("hello")
    text.ingest(["foo", "bar"])
    log.ingest({"level": "INFO", "msg": "started"})
    log.ingest([{"level": "WARN", "msg": "low disk"}, {"level": "ERROR", "msg": "crash"}])

    print("\n--- output() extraction (FIFO with rank) ---")
    for _ in range(4):
        print("Numeric ->", numeric.output())
    for _ in range(3):
        print("Text ->", text.output())
    for _ in range(3):
        print("Log ->", log.output())

    print("\n--- output() on empty storage ---")
    try:
        numeric.output()
    except IndexError as e:
        print("Caught expected exception:", e)