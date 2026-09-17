*This project has been created as part of the 42 curriculum by thdexmun.*

## Description:

The purpose of this project is to teach students the concept of variadic arguments and familiarise them with their usages.


## Instructions:

to create the **libftprintf.a** library, run ```make```/```make all```/```make libftprintf.a```.

to remove all object files (\*.o) only, run ```make clean```.

to remove all object files, temporary files and remove the library, run ```make fclean```.

to remove object files and the library, then immediately recreate the library,
run ```make re```.

to create the **libftprintf.a** library for bonus functions, run ```make bonus```.

to use **libftprintf.a** library, include the project header file **ft_printf.h** and compile
your c file with the library. Example: ```cc -Wall -Werror -Wextra main.c libftprintf.a```.

## Resources:

The behaviour of each functions was created based on the details in ```man``` and research done on
websites like stackoverflow and geeksforgeeks. 

This website was used during the creation of the Makefile. To understand certain patterns and the documented behavior.

http://www.chiark.greenend.org.uk/doc/make-doc/make.html/Rules.html

AI was used only as a research tool to understand
the behaviour of flag in printf and what flags affect each conversion.

It was also used to understand behaviors of certain Makefile patterns when attempting to achieve certain goals, mainly the feasibility of some methods.

## Detailes:

This library contains the main `ft_printf` function and all it's utility functions.

To complete this project mandatory portion, the conversion is passed to it's utility functions to directly determine what to output next.

To complete this project bonus portion, the conversion and all it's flags are passed to it's utility functions together in the form of a typedef structure `t_print`, they are then processed by the individual conversion functions for more flexibility.

`t_print` contains a processed version of the flags that contains which flags to handle for that conversion. That way the conversion functions just need to check the `t_print` given to decide which flags to handle.