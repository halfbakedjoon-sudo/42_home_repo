*This project has been created as part of the 42 curriculum by johiew.*

# Libft

## Description

**Libft** is the first library project in the 42 curriculum. The objective is to recreate a collection of commonly used C standard library functions while gaining a deeper understanding of pointers, memory management, strings, linked lists, and static libraries.

The project consists of 43 functions divided into three parts:

### Part 1 – Libc Functions (23)
Reimplement standard C library functions related to character checks, memory manipulation, string handling, and conversions.
* ft_isalpha
* ft_isdigit
* ft_isalnum
* ft_isascii
* ft_isprint
* ft_strlen
* ft_memset
* ft_bzero
* ft_memcpy
* ft_memmove
* ft_strlcpy
* ft_strlcat
* ft_toupper
* ft_tolower
* ft_strchr
* ft_strrchr
* ft_strncmp
* ft_memchr
* ft_memcmp
* ft_strnstr
* ft_atoi
* ft_calloc
* ft_strdup

### Part 2 – Additional Functions (11)
Implement useful utility functions such as string splitting, trimming, joining, integer conversion, and output functions.

* ft_substr
* ft_strjoin
* ft_strtrim
* ft_split
* ft_itoa
* ft_strmapi
* ft_striteri
* ft_putchar_fd
* ft_putstr_fd
* ft_putendl_fd
* ft_putnbr_fd

### Part 3 – Bonus Linked List Functions (9)
Implement a complete set of singly linked list operations, including node creation, insertion, deletion, iteration, and mapping.
* ft_lstnew
* ft_lstadd_front
* ft_lstsize
* ft_lstlast
* ft_lstadd_back
* ft_lstdelone
* ft_lstclear
* ft_lstiter
* ft_lstmap

The library is compiled into a static library named `libft.a`, which can be reused in future C projects.

---

## Instructions

### Compilation

Build the library:

```
make
```

Available Makefile rules:

```
make        # Build libft.a
make clean  # Remove object files
make fclean # Remove object files and libft.a
make re     # Rebuild the library
```

### Using the Library

Include the header file:

```
#include "libft.h"
```

Compile your program with the library:

```
cc main.c libft.a
```

or

```
cc main.c -L. -lft
```

---

## Resources

### References

* The Open Group Base Specifications (POSIX)
* Linux Manual Pages (man pages)
* ISO C Standard Library Documentation
* 42 Subject PDF (libft)

Useful online references:

* https://man7.org/linux/man-pages/
* https://pubs.opengroup.org/onlinepubs/
* https://en.cppreference.com/w/c

