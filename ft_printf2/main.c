#include <stdio.h>
#include "ft_printf.h"
 
int g_tests = 0;
int g_fails = 0;
 
#define TEST(fmt, ...) \
	do { \
		int ret_mine; \
		int ret_ref; \
		g_tests++; \
		printf("---- fmt: \"%s\" ----\n", fmt); \
		fflush(stdout); \
		printf("expected : "); \
		fflush(stdout); \
		ret_ref = printf(fmt, ##__VA_ARGS__); \
		fflush(stdout); \
		printf("\n"); \
		fflush(stdout); \
		printf("got      : "); \
		fflush(stdout); \
		ret_mine = ft_printf(fmt, ##__VA_ARGS__); \
		fflush(stdout); \
		printf("\n"); \
		fflush(stdout); \
		if (ret_ref != ret_mine) { \
			printf("  \x1b[31mRETURN MISMATCH: expected %d, got %d\x1b[0m\n", ret_ref, ret_mine); \
			g_fails++; \
		} else { \
			printf("  \x1b[32mreturn OK (%d)\x1b[0m\n", ret_mine); \
		} \
		fflush(stdout); \
	} while (0)
 
int main(void)
{
	setbuf(stdout, NULL); // disable buffering so write() and printf() interleave correctly
 
	// %c
	TEST("%c", 'A');
	TEST("[%c]", 'z');
	TEST("%c%c%c", 'a', 'b', 'c');
 
	// %s
	TEST("%s", "hello world");
	TEST("%s", "");
	TEST("%s", (char *)NULL);
 
	// %p
	int x = 42;
	TEST("%p", &x);
	TEST("%p", (void *)NULL);
 
	// %d
	TEST("%d", 42);
	TEST("%d", -42);
	TEST("%d", 0);
	TEST("%d", 2147483647);
	TEST("%d", -2147483647);
 
	// %i
	TEST("%i", 42);
	TEST("%i", -42);
 
	// %u
	TEST("%u", 42);
	TEST("%u", 4294967295U);
 
	// %x
	TEST("%x", 255);
	TEST("%x", 0);
 
	// %X
	TEST("%X", 255);
	TEST("%X", 0);
 
	// %%
	TEST("100%%");
	TEST("%%%%");
 
	// no specifiers / empty
	TEST("no format specifiers here");
	TEST("");
 
	// mixed, multiple args
	TEST("%s has %d apples, grade %c (id %p)", "Alice", 5, 'A', &x);
	TEST("%d-%d-%d %s", 2024, 1, 1, "New Year");
	TEST("%x %X %u %d", 255, 255, 255, -255);
 
	printf("\n==================================\n");
	printf("Tests run: %d, Failures: %d\n", g_tests, g_fails);
	printf("==================================\n");
 
	return (g_fails != 0);
}
 
