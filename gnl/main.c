#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"

int g_tests = 0;
int g_fails = 0;

#define OK(name) do { g_tests++; printf("\x1b[32m[OK]\x1b[0m %s\n", name); } while (0)
#define FAIL(name, detail) do { g_tests++; g_fails++; printf("\x1b[31m[FAIL]\x1b[0m %s -> %s\n", name, detail); } while (0)

/* ---- helpers ---- */

static void write_file(const char *path, const char *content)
{
	int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("write_file: open");
		exit(1);
	}
	write(fd, content, strlen(content));
	close(fd);
}

/*
** Splits `content` the way we expect get_next_line to return it:
** each element is one line INCLUDING its trailing '\n' if the
** original had one, except possibly the last line if the file
** doesn't end in '\n'. Returns a NULL-terminated array (caller frees).
*/
static char **expected_lines(const char *content)
{
	int count = 0;
	const char *p = content;

	if (*p == '\0')
	{
		char **arr = malloc(sizeof(char *));
		arr[0] = NULL;
		return (arr);
	}
	while (*p)
	{
		count++;
		while (*p && *p != '\n')
			p++;
		if (*p == '\n')
			p++;
	}
	char **arr = malloc(sizeof(char *) * (count + 1));
	p = content;
	int i = 0;
	while (*p)
	{
		const char *start = p;
		while (*p && *p != '\n')
			p++;
		if (*p == '\n')
			p++;
		size_t len = p - start;
		arr[i] = malloc(len + 1);
		memcpy(arr[i], start, len);
		arr[i][len] = '\0';
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

static void free_arr(char **arr)
{
	for (int i = 0; arr[i]; i++)
		free(arr[i]);
	free(arr);
}

/* Runs get_next_line on `path` and checks output against `content` */
static void run_case(const char *name, const char *path, const char *content)
{
	int fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		FAIL(name, "could not open test file");
		return;
	}

	char **exp = expected_lines(content);
	int i = 0;
	int mismatch = 0;
	char *line;

	while ((line = get_next_line(fd)) != NULL)
	{
		if (exp[i] == NULL)
		{
			printf("    extra line returned: \"%s\"\n", line);
			mismatch = 1;
			free(line);
			break;
		}
		if (strcmp(line, exp[i]) != 0)
		{
			printf("    line %d mismatch:\n      expected: \"%s\"\n      got     : \"%s\"\n",
				i, exp[i], line);
			mismatch = 1;
		}
		free(line);
		i++;
	}
	if (!mismatch && exp[i] != NULL)
	{
		printf("    missing line %d: expected \"%s\", got NULL\n", i, exp[i]);
		mismatch = 1;
	}

	/* calling again after EOF must keep returning NULL, never crash */
	char *after_eof = get_next_line(fd);
	if (after_eof != NULL)
	{
		printf("    calling after EOF did not return NULL (\"%s\")\n", after_eof);
		free(after_eof);
		mismatch = 1;
	}

	if (mismatch)
		FAIL(name, "see details above");
	else
		OK(name);

	free_arr(exp);
	close(fd);
}

int main(void)
{
	setbuf(stdout, NULL);
	system("mkdir -p /tmp/gnl_tests");

	write_file("/tmp/gnl_tests/basic.txt", "hello\nworld\nfoo\n");
	run_case("basic multi-line, trailing newline", "/tmp/gnl_tests/basic.txt",
		"hello\nworld\nfoo\n");

	write_file("/tmp/gnl_tests/no_trailing_nl.txt", "hello\nworld\nfoo");
	run_case("last line without trailing newline", "/tmp/gnl_tests/no_trailing_nl.txt",
		"hello\nworld\nfoo");

	write_file("/tmp/gnl_tests/empty.txt", "");
	run_case("empty file", "/tmp/gnl_tests/empty.txt", "");

	write_file("/tmp/gnl_tests/single_no_nl.txt", "onlyoneline");
	run_case("single line, no newline", "/tmp/gnl_tests/single_no_nl.txt", "onlyoneline");

	write_file("/tmp/gnl_tests/single_with_nl.txt", "onlyoneline\n");
	run_case("single line, with newline", "/tmp/gnl_tests/single_with_nl.txt", "onlyoneline\n");

	write_file("/tmp/gnl_tests/blank_lines.txt", "\n\n\nhello\n\n");
	run_case("consecutive blank lines", "/tmp/gnl_tests/blank_lines.txt", "\n\n\nhello\n\n");

	write_file("/tmp/gnl_tests/only_newline.txt", "\n");
	run_case("file containing only a newline", "/tmp/gnl_tests/only_newline.txt", "\n");

	{
		/* long line, several multiples of common BUFFER_SIZE values (1, 5, 42, 1024...) */
		char *big = malloc(10000 + 1);
		for (int i = 0; i < 10000; i++)
			big[i] = 'a' + (i % 26);
		big[10000] = '\0';
		char *content = malloc(10010);
		snprintf(content, 10010, "%s\nshort\n", big);
		write_file("/tmp/gnl_tests/long_line.txt", content);
		run_case("very long line (10000 chars)", "/tmp/gnl_tests/long_line.txt", content);
		free(big);
		free(content);
	}

	printf("\n--- invalid fd ---\n");
	{
		char *line = get_next_line(-1);
		if (line == NULL)
			OK("get_next_line(-1) returns NULL");
		else
		{
			FAIL("get_next_line(-1) returns NULL", "did not return NULL");
			free(line);
		}
	}

	printf("\n==================================\n");
	printf("Tests run: %d, Failures: %d\n", g_tests, g_fails);
	printf("==================================\n");
	printf("\nNote: run this under valgrind/leaks to confirm no memory leaks,\n");
	printf("especially on the long-line and empty-file cases.\n");

	return (g_fails != 0);
}