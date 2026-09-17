*This project has been created as part of the 42 curriculum by thdexmun, johiew.*

# push_swap

## Description

`push_swap` is a 42 School algorithmic project. The goal is to sort a stack of integers using the smallest reasonable number of operations, working with only two stacks (`a` and `b`) and a small, fixed set of stack manipulation instructions — no arrays, no random access, no built-in sort functions.

`push_swap` takes a list of integers as arguments, validates them, and prints the sequence of operations needed to sort them into ascending order using stack `a` and stack `b` as a workspace. A `checker` (bonus) program reads a sequence of operations from stdin and verifies whether applying them to the given input actually produces a sorted stack.

The project's core challenge is algorithmic: the same sort can be done in wildly different numbers of operations depending on the strategy used, so a large part of the project is choosing, implementing, and benchmarking sorting strategies against operation-count thresholds rather than simply "getting it to sort."

## Allowed operations

| Operation | Description |
|---|---|
| `sa` | Swap the first 2 elements at the top of stack `a` |
| `sb` | Swap the first 2 elements at the top of stack `b` |
| `ss` | `sa` and `sb` at the same time |
| `pa` | Push the top of `b` onto `a` |
| `pb` | Push the top of `a` onto `b` |
| `ra` | Rotate `a` up (first element becomes last) |
| `rb` | Rotate `b` up |
| `rr` | `ra` and `rb` at the same time |
| `rra` | Reverse rotate `a` (last element becomes first) |
| `rrb` | Reverse rotate `b` |
| `rrr` | `rra` and `rrb` at the same time |

## Instructions

### Compilation

```bash
make              # builds push_swap
make push_swap    # builds push_swap
make debug        # builds push_swap with memory leak checking
make bonus        # builds checker
make bonus_debug  # builds checker with memory leak checking
make clean        # removes object files
make fclean       # removes object files and binaries
make re           # fclean + all
make re_bonus     # fclean + bonus
```

Requires a C compiler (`cc`) and `make`. No external dependencies beyond the project's own libft/libftprintf.

### Running push_swap

#### Regular Usage

```bash
./push_swap "4 67 3 87 23"
./push_swap 4 67 3 87 23
```

#### Force Simple Algorithm Usage

```bash
./push_swap --simple "4 67 3 87 23"
./push_swap --simple 4 67 3 87 23
```

#### Force Medium Algorithm Usage

```bash
./push_swap --medium "4 67 3 87 23"
./push_swap --medium 4 67 3 87 23
```

#### Force Complex Algorithm Usage

```bash
./push_swap --complex "4 67 3 87 23"
./push_swap --complex 4 67 3 87 23
```

#### Force Adaptive Algorithm Usage (Default)

```bash
./push_swap --adaptive "4 67 3 87 23"
./push_swap --adaptive 4 67 3 87 23
```

If no arguments are given, or arguments are invalid (non-integers, values outside `INT_MIN`/`INT_MAX`, duplicate values), the program prints `Error` to **stderr** and exits without sorting anything. Already-sorted input produces no output (zero operations needed).

### Running checker (bonus)

```bash
./push_swap "3 1 2" | ./checker "3 1 2"
```

`checker` reads a sequence of operations from stdin (one per line — `sa`, `pb`, `ra`, etc.), applies them to the given input, and prints `OK` if the result is sorted with nothing left in stack `b`, or `KO` otherwise.

### Benchmark mode

```bash
./push_swap --bench --complex "4 67 3 87 23"
./push_swap --bench 4 67 3 87 23
```

Passing the benchmark flag prints operation-count diagnostics to **stderr** (never stdout, so it never interferes with the operation stream a checker reads from stdout).

## Algorithms

Several sorting strategies were implemented and benchmarked against each other before settling on a final approach, since the same result (a sorted stack) can be reached with very different operation counts depending on the strategy:

- **Insertion sort — O(n²), smaller constant than bubble sort.** Builds a sorted stack `b` one element at a time: each element from `a` is pushed to `b` after rotating `b` (in whichever direction is cheaper) until the correct insertion point is found, then rotating back to restore `b`'s order before the next insertion. Meaningfully fewer operations than bubble sort in practice because each element is only positioned once, rather than repeatedly compared against every other element every pass.

- **Bucket / chunk sort — O(n·√n).** Splits the value range (converted to ranks 0..n-1) into chunks and processes them in order: for each chunk, every element in that chunk's range is pulled out and inserted into `b` in sorted position, before moving to the next chunk. This bounds the search cost of each insertion to the current chunk rather than the whole of `b`, which lowers the operation count compared to plain insertion sort, at the cost of extra scanning passes to find each chunk's members.

- **Binary radix sort — O(n log n).** Values are first converted to ranks (0..n-1) so only non-negative, bounded values need to be handled. The stack is then processed bit by bit, least significant bit first: on each pass, every element with a `0` bit is pushed to `b`, everything else is rotated past, and `b` is pushed back onto `a` before the next bit. Since only `⌈log₂ n⌉` bits are needed to distinguish n elements, this requires far fewer passes than a value-range approach, and each pass costs O(n) — giving O(n log n) total, the best asymptotic result achieved in this project.

### Complexity verification

Rather than relying on the Big-O label alone, operation counts were measured empirically across a range of input sizes (100 to 1000, in steps of 100) and checked against the theoretical growth rate: for a genuine O(f(n)) algorithm, `operations / f(n)` should stay roughly constant as n grows, while it will trend upward or downward if f(n) is the wrong fit. Testing `ops/n`, `ops/(n·log₂n)`, `ops/(n·√n)` and `ops/n²` against the measured data confirmed the insertion sort implementation behaves as O(n²) (flat `ops/n²` ratio) and the binary radix implementation behaves as O(n log n) (flat `ops/(n·log₂n)` ratio), consistent with their theoretical design.

## Resources

- [42 push_swap subject](https://cdn.intra.42.fr/pdf/pdf/push_swap.en.pdf) — project requirements and grading criteria.
- Classic algorithm references on insertion sort, bubble sort, radix sort, and bucket sort (CLRS, *Introduction to Algorithms*, and general algorithm complexity resources) for the underlying sorting concepts adapted here to a two-stack model.
- 42 community write-ups on push_swap-specific strategies (chunk-based / "Turkish" style algorithms, radix sort adaptations) for inspiration on adapting classic algorithms to a stack-only operation set.

### AI usage

An AI assistant was used throughout development as a debugging and design-discussion partner, specifically for:
- Reviewing hand-written C code for bugs (pointer/reference errors, off-by-one errors, type mismatches, infinite-loop conditions) in the parsing, stack-operation, and sorting-algorithm code.
- Discussing and comparing algorithm design tradeoffs (insertion sort vs. radix vs. chunk-based approaches) before implementation.
- Explaining the theory behind algorithmic complexity classes (O(n), O(n log n), O(n√n), O(n²)) and how to empirically verify which class an implementation actually falls into.
- Generating test datasets (random integer sets with specified disorder levels) used to benchmark operation counts.
- General Makefile and git workflow troubleshooting.

All algorithm design decisions, final implementations, and correctness verification (including hand-tracing test cases) were done and confirmed by the project author; AI-suggested code was reviewed, tested, and adapted rather than used unmodified.

## Performance targets

| n | Pass | Good | Excellent |
|---|---|---|---|
| 100 | < 2000 ops | < 1500 ops | < 700 ops |
| 500 | < 12000 ops | < 8000 ops | < 5500 ops |