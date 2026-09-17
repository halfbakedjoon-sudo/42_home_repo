#include <stdio.h>
#include <string.h>
#include "ft_printf.h"

int g_tests = 0;
int g_fails = 0;

void check_str(const char *label, const char *fmt, ...)
{
	va_list ap;
	char buf1[1024];
	char buf2[1024];
	int ret1;
	int ret2;

	va_start(ap, fmt);
	ret1 = vsnprintf(buf1, sizeof(buf1), fmt, ap);
	va_end(ap);

	// ft_printf doesn't take va_list directly here, so we call it
	// via its own varargs wrapper below in run_case().
	(void)ret2;
	(void)buf2;
	(void)label;
}

/*
** Since ft_printf and printf both take variadic args directly,
** the cleanest way to compare them is to call both with the SAME
** literal args in a macro, capturing return values and output.
*/

#define TEST(fmt, ...) \
	do { \
		int ret_mine; \
		int ret_ref; \
		g_tests++; \
		printf("---- fmt: \"%s\" ----\n", fmt); \
		printf("expected : "); \
		ret_ref = printf(fmt, ##__VA_ARGS__); \
		printf("\n"); \
		printf("got      : "); \
		ret_mine = ft_printf(fmt, ##__VA_ARGS__); \
		printf("\n"); \
		if (ret_ref != ret_mine) { \
			printf("  \x1b[31mRETURN MISMATCH: expected %d, got %d\x1b[0m\n", ret_ref, ret_mine); \
			g_fails++; \
		} else { \
			printf("  \x1b[32mreturn OK (%d)\x1b[0m\n", ret_mine); \
		} \
	} while (0)

int main(void)
{
	// %c
	TEST("%c", 'A');
	TEST("[%c]", 'z');

	// %s
	TEST("%s", "hello world");
	TEST("%s", "");
	TEST("%s", (char *)NULL);

	// %p
	int x = 42;
	TEST("%p", &x);
	TEST("%p", (void *)NULL);

	// %d / %i
	TEST("%d", 42);
	TEST("%d", -42);
	TEST("%d", 0);
	TEST("%i", -2147483647);
	TEST("%d", 2147483647);

	// %u
	TEST("%u", 42);
	TEST("%u", 4294967295U);

	// %x / %X
	TEST("%x", 255);
	TEST("%X", 255);
	TEST("%x", 0);
	TEST("%#x", 255);

	// %%
	TEST("100%%");

	// Flags / width / precision
	TEST("[%5d]", 42);
	TEST("[%-5d]", 42);
	TEST("[%05d]", 42);
	TEST("[%+d]", 42);
	TEST("[%+d]", -42);
	TEST("[% d]", 42);
	TEST("[%10s]", "hi");
	TEST("[%-10s]", "hi");
	TEST("[%.3s]", "hello");
	TEST("[%10.3s]", "hello");
	TEST("[%-10.3s]", "hello");
	TEST("[%.5d]", 42);
	TEST("[%10.5d]", 42);
	TEST("[%-10.5d]", 42);
	TEST("[%010d]", 42);
	TEST("[%0-10d]", 42); // 0 flag ignored when - present

	// Combos
	TEST("%s has %d apples and %c grade (%.2f%%)", "Alice", 5, 'A', 91.5);
	// note: remove the %f test above if your ft_printf doesn't require floats

	// Multiple args, mixed
	TEST("%d-%d-%d %s", 2024, 1, 1, "New Year");
	TEST("%x %X %#x %#X", 255, 255, 255, 255);

	// Edge cases
	TEST("no format specifiers here");
	TEST("");
	TEST("%%%%");
	TEST("%c%c%c", 'a', 'b', 'c');

	printf("\n==================================\n");
	printf("Tests run: %d, Failures: %d\n", g_tests, g_fails);
	printf("==================================\n");

	return (g_fails != 0);
}
