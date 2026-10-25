# Coders / Dongles Simulation (42 "Philosophers" variant)

Personal reference notes. No code, only the spec and design thinking.

---

## 1. What this project is

A reskinned **Dining Philosophers Problem**.

| This project | Classic version |
|---|---|
| Coder | Philosopher |
| USB dongle | Fork |
| Compiling | Eating |
| Debugging | Sleeping |
| Refactoring | Thinking |
| Burnout | Starvation |

**Why it exists:** it models independent threads competing for limited shared resources where each one needs more than one resource at once (multiple mutexes, multiple DB rows, file handles).

**What it teaches:**
1. Thread creation and management, with unpredictable scheduling
2. Protecting shared data with mutexes (avoiding data races)
3. **Deadlock**: everyone grabs one dongle and waits forever for the second
4. **Starvation**: no deadlock, but someone never gets both dongles in time
5. Designing a strategy using only local decisions (coders don't communicate)
6. Precise timing and monitoring

**Why the constraints exist:**
- Circular table, as many dongles as coders: creates circular wait
- Two dongles needed at once: creates hold-and-wait
- No communication and no knowledge of others: no central coordinator allowed
- Burnout ends the simulation: a clear, testable failure condition

---

## 2. The scenario

- Coders sit in a circle. A shared Quantum Compiler is in the center.
- Each coder cycles: **compile -> debug -> refactor -> compile ...** (never two at once).
- There are as many dongles as coders.
- Compiling needs **two dongles at once** (left and right).
- After compiling, the coder puts both dongles back, then debugs, then refactors, then immediately tries to compile again.
- The simulation stops when a coder burns out.
- Coders must never burn out.

---

## 3. Program arguments (all mandatory)

```
number_of_coders time_to_burnout time_to_compile time_to_debug time_to_refactor number_of_compiles_required dongle_cooldown scheduler
```

| Argument | Meaning |
|---|---|
| `number_of_coders` | Number of coders and also number of dongles |
| `time_to_burnout` (ms) | A coder burns out if they have not *started* compiling within this time since the start of their last compile (or the start of the simulation) |
| `time_to_compile` (ms) | Duration of compiling; two dongles held throughout |
| `time_to_debug` (ms) | Duration of debugging |
| `time_to_refactor` (ms) | Duration of refactoring; afterwards the coder immediately tries to get dongles again |
| `number_of_compiles_required` | If all coders compiled at least this many times, the simulation stops |
| `dongle_cooldown` (ms) | After release, a dongle is unavailable until the cooldown has passed |
| `scheduler` | Exactly `fifo` or `edf` |

**Validation:** reject anything invalid: wrong argument count (must be exactly 8), negative numbers, non-integers, or a scheduler other than `fifo` / `edf`.

**Seating:** coders are numbered 1 to N. Coder 1 sits next to coder N. Any other coder K sits between K-1 and K+1.

### Schedulers
- **fifo**: First In, First Out. The dongle goes to whoever requested first.
- **edf**: Earliest Deadline First, where `deadline = last_compile_start + time_to_burnout`. The coder closest to burning out wins.

---

## 4. Logging

Format, one state change per line:

```
timestamp_in_ms X has taken a dongle
timestamp_in_ms X is compiling
timestamp_in_ms X is debugging
timestamp_in_ms X is refactoring
timestamp_in_ms X burned out
```

- `timestamp_in_ms` = current time in ms, `X` = coder number.
- Messages must never be mixed up or interleave on a line.
- The burnout message must appear **no more than 10 ms** after the actual burnout (a small tolerance is allowed when testing).
- `gettimeofday()` is acceptable for real-time measurement.

---

## 5. Mandatory rules

- **No global variables.**
- Each coder is a thread (`pthread_create`).
- One dongle between each pair of coders. With **1 coder there is only 1 dongle**.
- Each dongle's state is protected by a mutex (`pthread_mutex_t`). A condition variable (`pthread_cond_t`) may be used for waiting queues.
- **Cooldown is mandatory:** a released dongle can't be taken again until `dongle_cooldown` ms have passed.
- **Fair arbitration is mandatory:** when several coders request the same dongle, grant by the scheduler (fifo = arrival order, edf = earliest deadline). A **deterministic tie-breaker** is required for equal EDF deadlines.
- **Liveness:** under `edf`, no coder may starve and burn out, provided the parameters are feasible.
- A **separate monitor thread** detects burnout precisely and stops the simulation.
- Logging is serialized with a mutex.
- Stop conditions: a coder burns out, **or** every coder has compiled at least `number_of_compiles_required` times.
- Must compile with `-Wall -Wextra -Werror -pthread`.
- You must implement your own **priority queue (heap)** for fifo/edf. No standard-library priority queue.
- All memory allocated and freed (no leaks).

---

## 6. Allowed functions

### Threads
- **`pthread_create(&thread, attr, routine, arg)`**: starts a thread running `routine(arg)`. `attr` may be `NULL`. `arg` is one `void *`, so pass a pointer to a struct. Returns 0 on success or an error number (does not set `errno`).
- **`pthread_join(thread, &retval)`**: waits for a thread to finish. `retval` may be `NULL`.

### Mutexes
- **`pthread_mutex_init`**: prepare a mutex (`NULL` attr = default).
- **`pthread_mutex_lock`**: block until you own it. One owner at a time.
- **`pthread_mutex_unlock`**: release it. Only the owner should unlock.
- **`pthread_mutex_destroy`**: free it. Only when unlocked and unused.

### Condition variables
A condition variable lets a thread sleep until a condition becomes true, instead of busy-looping. Always paired with a mutex guarding the data the condition depends on.

- **`pthread_cond_init` / `pthread_cond_destroy`**: like the mutex versions.
- **`pthread_cond_wait(&cond, &mutex)`**: call with the mutex locked. Atomically unlocks and sleeps, then re-locks before returning.
  - Wakeups can be spurious and state can change between signal and wake, so **always re-check the condition in a loop**, never a single `if`.
  - The condition lives in *your* data, not in the cond variable.
- **`pthread_cond_timedwait(&cond, &mutex, &abstime)`**: same, but gives up at a deadline.
  - Time is **absolute** (a `struct timespec`), not "wait N ms".
  - Returns `ETIMEDOUT` on timeout, mutex re-locked.
  - Good fit for cooldowns and for waking up to notice a stop request.
- **`pthread_cond_signal`**: wake at least one waiter.
- **`pthread_cond_broadcast`**: wake all waiters. Choosing between the two depends on whether any waiter could be the right one to proceed.

### Time
- **`gettimeofday(&tv, NULL)`**: seconds + microseconds since 1970 (wall clock). Can jump if the system clock is adjusted.
- **`clock_gettime(clock_id, &ts)`**: seconds + nanoseconds in a `struct timespec`.
  - `CLOCK_MONOTONIC` never goes backward (best for elapsed time).
  - `CLOCK_REALTIME` is wall-clock.
  - `pthread_cond_timedwait` measures against `CLOCK_REALTIME` by default, so keep clocks consistent when building deadlines.
- **`usleep(microseconds)`**: sleeps *at least* that long, often slightly more. A single long sleep can't notice your stop flag. For the 10 ms rule, **sleep in short slices** and re-check the time or the stop flag.

---

## 7. Design notes

### 7.1 Structure (no globals)
Everything threads need must be reachable through a pointer passed in. Typical layout:
- One shared **simulation** struct: parsed parameters, stop flag, start time, log mutex, array of dongles.
- One **coder** struct per coder: ID, last compile start, compile count, pointers to its left/right dongle, pointer back to the simulation struct.

### 7.2 Dongle layout
- N coders -> N dongles. Dongle i sits between coder i and coder i+1 (last wraps to first).
- With 1 coder, left and right dongle are the same one, so they can never get two. Decide how this case ends (the monitor should handle it naturally via burnout).

### 7.3 What each dongle owns
- A mutex and a condition variable
- A "taken" state
- An "available again at" time (release time + cooldown)
- A waiting queue (the heap)

A coder gets the dongle only when **all three** are true:
1. It's free
2. The cooldown has passed
3. The coder is first in the queue

### 7.4 The heap
One heap implementation serves both schedulers; only the comparison changes.
- `fifo`: order by arrival (request counter or arrival timestamp)
- `edf`: order by `last_compile_start + time_to_burnout`
- **Tie-breaker** (required): something stable and explainable, such as the coder ID.

Questions to settle:
- How large must each dongle's heap be? (How many coders can ever request the same dongle at once?)
- What happens to a coder's queue entry if it stops waiting because the simulation ended?

### 7.5 Liveness has two parts
- **Deadlock:** arbitration alone does not remove hold-and-wait. Think about whether a coder should ever wait on a second dongle while holding the first, and find a local rule that breaks the circular wait.
- **Starvation:** EDF addresses this, but the deadline must be read from up-to-date data since it changes after every compile.

### 7.6 Burnout deadline
It counts from the **start** of the last compile, not the end. Store exactly that timestamp per coder and protect it: the monitor reads it while the coder writes it.

### 7.7 The monitor thread
- Reads each coder's last compile start safely.
- Polls often enough for the 10 ms rule (choose an interval with margin).
- Also detects "everyone has compiled enough times".
- On stop, **wakes every thread sleeping on a dongle's condition variable**, otherwise `pthread_join` hangs.
- Ensures no other coder prints after the burnout message.

### 7.8 Responsiveness
Waits and sleeps can't be one big blocking call. Think about how a coder waiting on a dongle or sleeping through debugging notices the stop flag, and how the monitor's interval relates to 10 ms.

### 7.9 Clock consistency
`pthread_cond_timedwait` takes an absolute time. Build deadlines from one consistent clock family, and be careful converting milliseconds into seconds + nanoseconds.

### 7.10 Logging
One output mutex. Do the **stop check and the print together under it**, so nothing slips out after the burnout line.

### 7.11 Cleanup
- Every mutex/cond init needs a matching destroy.
- Every `malloc` needs a free.
- Include error paths, e.g. a failed `pthread_create` partway through startup.

### 7.12 Edge cases to decide early
- 1 coder
- Argument validation (exactly 8 args, non-negative integers only, scheduler exactly `fifo` or `edf`)
- What "stop" means when all coders reach the required compile count

---

## 8. Suggested build order

1. Parse and validate arguments
2. Write the structs
3. Write and test the **heap** on its own (no threads needed)
4. Get a single coder's lifecycle working with correct timings and logging (no contention)
5. Add dongle acquire/release (cooldown, queue, scheduler)
6. Add the deadlock-avoidance rule (reason about 3 coders acting at the same instant)
7. Add the monitor thread and clean shutdown
8. Test with tricky parameters: 1 coder, 2 coders, odd and even counts, tight burnout times, large cooldowns
9. Check leaks and races (valgrind, `-fsanitize=thread`) and compile with `-Wall -Wextra -Werror -pthread`

**Test each stage before moving on.** Concurrency bugs are much harder to find once everything is stacked together.

---

## 9. Open questions to answer for myself

- What is the simplest rule that stops everyone grabbing their left dongle first?
- What exactly does each dongle's queue store per entry?
- What poll interval gives the monitor enough margin under 10 ms?
- How do I guarantee nothing is printed after a burnout line?