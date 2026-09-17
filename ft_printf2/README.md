*This project has been created as part of the 42 curriculum by johiew.*

# FT_PRINTF

## Description

**Libftprintf** is one of the library project in the 42 curriculum. The objective is to replicate the basic function of **printf** to gain deeper understanding on how to implement the functions and also understand the flags, width and precision of the function.

### Format specification

-> flags -> width -> .precision -> speficier

The format-string is read left to right. When the first format specification is found, the value of the first argument after the format-string is converted and printed according to the format specification. The second format specification causes the second argument after the format-string to be converted and printed, and so on through the end of the format-string. If there are more arguments than there are format specifications, the extra arguments are evaluated and ignored. The results are undefined if there are not enough arguments for all the format specifications.

## Instructions

### Compilation

Build the library:

```
make
```

Available Makefile rules:

```
make        # Build libftprintf.a
make clean  # Remove object files
make fclean # Remove object files and libftprintf.a
make re     # Rebuild the library
```

### Using the Library

Include the header file:

```
#include "libftprintf.h"
```

Compile your program with the library:

```
cc main.c libftprintf.a
```

or

```
cc main.c -L. -lft
```

---

## Resources

### References

Useful online references:

* https://www.ibm.com/docs/en/i/7.4.0?topic=p-print-formatted-characters-printf
* https://en.wikipedia.org/wiki/Variadic_function