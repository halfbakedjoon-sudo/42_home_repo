*This project has been created as part of the 42 curriculum by johiew*

# GET_NEXT_LINE

## Description

`get_next_line` is a 42 School project that implements a function to read a text file line by line, one call at a time, regardless of file size or buffer size.

`get_next_line` reads from a file descriptor and returns exactly one line per call, including the trailing `\n` if present. It works no matter how small or large `BUFFER_SIZE` is, and it correctly resumes reading where the previous call left off — even across multiple file descriptors.

The core challenge is that `read()` doesn't respect line boundaries, so the function has to buffer leftover data between calls using a `static` variable that persists across invocations.

1. **Read into a buffer.** Each call to `read()` pulls at most `BUFFER_SIZE` bytes from the file descriptor.
2. **Accumulate into `stash`.** A `static char *stash` holds everything read so far that hasn't been returned yet. New data is joined onto it with each `read()` until a `\n` is found or `read()` returns 0 (EOF).
3. **Extract one line.** Once `stash` contains a `\n` (or we've hit EOF), the function copies everything up to and including the `\n` into a new string — that's the line returned to the caller.
4. **Save the remainder.** Whatever is left in `stash` after the extracted line is kept for the next call, so the function can resume exactly where it left off.
5. **Repeat.** Each call to `get_next_line` continues from the saved `stash`, reading more only if needed.


### Function breakdown

| Function | Responsibility |
|---|---|
| `get_next_line` | Orchestrates the process: calls the reader, checks the stash, extracts a line, updates the stash |
| `ft_read` | Reads from `fd` and joins new data into `stash` until a `\n` is found or EOF is reached |
| `check_stash` | Returns whether `stash` has content left to process, and frees/nulls it if not |
| `ft_put_line` | Copies the current line (up to and including `\n`) out of `stash` into the return buffer |

### ⚠️ Key implementation details

- **`stash` is `static`**, so it retains its value between separate calls to `get_next_line`. This is what allows the function to "remember" leftover data.
- **Pointer parameters that need to persist a change back to the caller use `char **`.** For example, `check_stash(char **stash)` sets `*stash = NULL` so the change is visible outside the function — a plain `char *` parameter would only modify a local copy, not the caller's variable. See the note on pass-by-value vs pass-by-reference below.
- **`stash + n` vs `stash + n + 1`:** after locating the `\n` at index `n`, the remainder of the buffer starts exactly at `stash + n` — using `n + 1` skips a character and silently corrupts every subsequent line.
- **EOF with no trailing newline** is handled by returning whatever remains in `stash` as the final line, then freeing and nulling `stash` on the next call.

### 📚 What this project teaches

- Static variables and state that persists across function calls
- Pass-by-value semantics in C, and when `char **` is required instead of `char *`
- Manual memory management (`malloc`/`free`) without leaks
- Buffered I/O and reading a stream in fixed-size chunks

#### A note on pointers-to-pointers

A recurring gotcha in this project: passing `char *stash` into a helper function only gives that function a *copy* of the pointer. Writing through it (`stash[0] = 'x'`) affects the caller's data, but reassigning it (`stash = new_address`) does not — the caller's original pointer is untouched. Any helper that needs to change *what address* `stash` points to (e.g. pointing it at a newly allocated string, or setting it to `NULL`) must take a `char **` and write through it with `*stash = ...`.

## Instruction

### 🚀 Usage

```c
#include "get_next_line.h"

int main(void)
{
    int   fd;
    char  *line;

    fd = open("file.txt", O_RDONLY);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

### 🔧 Compilation

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
```

`BUFFER_SIZE` can be set to any value at compile time to test edge cases:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 get_next_line.c get_next_line_utils.c main.c -o gnl
```

### 🧪 Testing checklist

- [ ] Small `BUFFER_SIZE` (e.g. `1`) — stresses multi-read accumulation
- [ ] Large `BUFFER_SIZE` (e.g. `9999`) — single-read path
- [ ] File with no trailing newline on the last line
- [ ] Empty file
- [ ] File containing only `\n` characters
- [ ] Multiple file descriptors read in an interleaved order
- [ ] Reading until EOF, then confirming `NULL` is returned on subsequent calls
- [ ] `valgrind --leak-check=full` for memory leaks and invalid reads

### 📁 Files

```
.
├── get_next_line.c        # main logic: get_next_line, ft_read, check_stash, ft_put_line
├── get_next_line_utils.c  # helper functions (ft_strchr, ft_strjoin ft_strdup, etc.)
└── get_next_line.h         # header with prototypes and BUFFER_SIZE fallback
```


### 🧪 Testing checklist

- [ ] Small `BUFFER_SIZE` (e.g. `1`) — stresses multi-read accumulation
- [ ] Large `BUFFER_SIZE` (e.g. `9999`) — single-read path
- [ ] File with no trailing newline on the last line
- [ ] Empty file
- [ ] File containing only `\n` characters
- [ ] Multiple file descriptors read in an interleaved order
- [ ] Reading until EOF, then confirming `NULL` is returned on subsequent calls
- [ ] `valgrind --leak-check=full` for memory leaks and invalid reads

## Resources

### 🤖 AI usage

AI was used during development as a debugging and learning aid, not as a code generator. Specifically:

* Explaining C semantics — clarifying pass-by-value behavior for pointers, and when a helper function needs char ** instead of char * to modify the caller's variable (e.g. check_stash, ft_read).
* Explaining a compiler warning — diagnosing an "uninitialized variable" error caused by passing an unused tmp parameter into ft_read.
* Generating a test harness (main.c) to exercise the function across different BUFFER_SIZE values, file edge cases, and multiple file descriptors.

All core logic, function design, and the fixes themselves were written and understood by me. AI was not used to generate the get_next_line implementation from scratch — it was used to explain why something was broken so I could fix it myself and understand the underlying C concepts (pointer semantics, static storage duration, buffered reads).

### Online References

* https://en.wikipedia.org/wiki/Static_variable