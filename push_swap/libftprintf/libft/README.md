*This project has been created as part of the 42 curriculum by thdexmun.*

## Description:

The purpose of this project is to familiarise students with various C programming concept,
such as iterative and recursive functions, link lists, prototyping etc.

Other than that, students also get to create their own utility library in the process and can
rely on them instead of external functions.


## Instructions:

to create the **libft.a** library, run ```make```/```make all```/```make libft.a```.

to remove all object files (\*.o) only, run ```make clean```.

to remove all object files and remove the library, run ```make fclean```.

to remove object files and the library, then immediately recreate the library,
run ```make re```.

to use **libft.a** library, include the project header file **libft.h** and compile
your c file with the library. Example: ```cc -Wall -Werror -Wextra main.c libft.a```.

## Resources:

The behaviour of each functions was created based on the details in ```man``` and research done on
websites like stackoverflow and geeksforgeeks. 

AI was used only as a research tool to understand
the behaviour of each functions and the difference of functionally similar functions.

## Details:

This library containes 43 utility C functions, each function will be detailed below.

### The following functions check whether a character is a specific classification, returns 1 if it is and returns 0 if it is not.

ft\_isalpha		-	checks whether a character is classified as an alphabet.

ft\_isdigit		-	checks whether a character is classified as a digit.

ft\_isalnum		-	checks whether a character is classified as an alphabet or a digit.

ft\_isascii		-	checks whether a character is classified as an ascii character.

ft\_isprint		-	checks whether a character is classified as a printable character.

### The following functions will return a value corresponding to it's purpose

ft\_strlen		-	the amount of characters excluding the NULL terminator in the string.

ft\_toupper		-	the upper cased alphabet corresponding to the lower cased alphabet
				given to it. Returns the given value if not a lower cased alphabet.

ft\_tolower		-	the lower cased alphabet corresponding to the upper cased alphabet
				given to it. Returns the given value if not a upper cased alphabet.

ft\_atoi		-	an integer converted from a string, Example: "-123" returns int -123.

ft\_strncmp		-	the first difference of a string, 0 if there is no difference.

ft\_memcmp		-	the first difference in (n) bytes in a memory,
				0 if there is no difference.

### The following functions will modify the string/memory given to it

ft\_memset		-	sets (n) bytes starting from the memory address
				given to it to a value, then returns the original memory address.

ft\_bzero		-	sets (n) bytes of the memory address given
				to it to 0.

ft\_memcpy		-	copies (n) bytes from one address to another, disregarding memory
				address overlapping. returns the destination memory address.

ft\_memmove		-	copies (n) bytes from one address to another, takes account to
				overlapping memory addresses. returns the destinarion memory address.

ft\_strlcpy		-	copies (n) characters from the source string to destination
				string. returns the size of the source string.

ft\_strlcat		-	concatanates characters from the source string to destination
				string so that the destination string is at least (n) characters long
				including the NULL terminator. returns the size of source string plus
				the amount of characters already whithin (n) characters of the destination
				string before the NULL terminator.

ft\_striteri	-	applies a function (f) to each character in string (s) based on it's index and value

### The following functions will return an address based on it's purpose

ft\_strchr		-	returns the address of the first occurance of the character given to it
				inside the given string, including the NULL terminator.
				returns NULL if not found.

ft\_strrchr		-	returns the address of the last occurance of the character given to it
				inside the given string, including the NULL terminator.
				returns NULL if not found.

ft\_memchr		-	searhes up to (n) bytes and returns the address of the first occurance
				of the value given to it inside the given memory address,
				returns NULL if not found.

ft\_strnstr		-	returns the address of the first address of the first occurance
				of a string (needle) given to it inside the given string (haystack),
				including the NULL terminator. returns NULL if not found.

### The following functions return an address allocated by ```malloc``` based on it's purpose

ft\_calloc		-	returns an allocated address that has each byte set to 0.

ft\_strdup		-	duplicates the given string into a newly allocated address and returns it.

ft\_substr		-	copies up to (len) characters starting from the (start) index in the given string into a newly allocated address, then returns it.

ft\_strjoin		-	allocates a new address, copies (s1) to the allocated address, then concatanates (s2) to the back of the allocated address. then returns it.

ft\_strtrim		-	create a copy of (s1) without any characters in (set) at the beginning or end and returns it.

ft\_split		-	allocates an array of strings, then copies each word, delimited by (c) into the array, then returns it with the last element being NULL.

ft\_itoa		-	returns a string version of an integer. Example: int -123 returns "-123"

ft\_strmapi		-	allocates a new address, then applies a function (f) to each character in string (s) based on it's index and value, then put the result into the allocated address and returns it.

### The following functions will write it's given argument to the (fd) file

ft\_putchar\_fd	-	writes a character.

ft\_putstr\_fd	-	writes a string.

ft\_putendl\_fd	-	writes a string and a new line at the end.

ft\_putnbr\_fd	-	writes a number. Example: writes "-123" to (fd) when given int -123.

### The following functions will be used to manage a linked list

ft\_lstnew			-	creates a new node for the linked list with ```malloc```, sets the node's content to (content) and sets the node's next to NULL.
	
ft\_lstadd\_front	-	links the node (new) to the front of (lst).

ft\_lstadd\_back	-	links the node (new) to the back of (lst).

ft\_lstsize			-	returns the amount of linked nodes in the list

ft\_lstlast			-	returns the last linked node in the list

ft\_lstdelone		-	applies the (del) function to the content of (lst) to free it, then free only (lst) itself.

ft\_lstclear		-	applies the (del) function to the content of each node in (lst) to free it, then free every node in (lst) and set the first node in (lst) to NULL.

ft\_lstiter			-	applies the (f) function to every linked node's content starting with the (lst) node.

ft\_lstmap			-	applies the (f) function to every linked node's content starting with the (lst) node and save it to a newly allocated linked list using ```malloc```
