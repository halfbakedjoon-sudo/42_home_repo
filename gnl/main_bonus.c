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
** The bonus requires get_next_line to correctly handle several file
** descriptors read in an interleaved fashion, without the static
** buffer(s) for one fd corrupting another's. This test opens 3 files
** with distinct, easily distinguishable content and reads from them
** in a round-robin / interleaved order, verifying every line lands
** on the fd it belongs to.
*/

int main(void)
{
	setbuf(stdout, NULL);
	system("mkdir -p /tmp/gnl_tests");

	write_file("/tmp/gnl_tests/fdA.txt", "A-line1\nA-line2\nA-line3\n");
	write_file("/tmp/gnl_tests/fdB.txt", "B-line1\nB-line2\n");
	write_file("/tmp/gnl_tests/fdC.txt", "C-line1\nC-line2\nC-line3\nC-line4\n");

	int fda = open("/tmp/gnl_tests/fdA.txt", O_RDONLY);
	int fdb = open("/tmp/gnl_tests/fdB.txt", O_RDONLY);
	int fdc = open("/tmp/gnl_tests/fdC.txt", O_RDONLY);

	if (fda < 0 || fdb < 0 || fdc < 0)
	{
		FAIL("open test files", "could not open one or more test files");
		return (1);
	}

	printf("\n--- interleaved reads across 3 fds ---\n");

	char *expected_a[] = {"A-line1\n", "A-line2\n", "A-line3\n", NULL};
	char *expected_b[] = {"B-line1\n", "B-line2\n", NULL};
	char *expected_c[] = {"C-line1\n", "C-line2\n", "C-line3\n", "C-line4\n", NULL};

	int ia = 0, ib = 0, ic = 0;
	int mismatch = 0;

	/* Interleave in a pattern that exercises A, C, B, A, C, C, B, A, C ... */
	int order[] = {0, 2, 1, 0, 2, 2, 1, 0, 2, 2}; /* 0=A, 1=B, 2=C */

	for (int step = 0; step < (int)(sizeof(order) / sizeof(order[0])); step++)
	{
		int which = order[step];
		char *line = NULL;
		char *expected = NULL;
		const char *label = NULL;

		if (which == 0)
		{
			line = get_next_line(fda);
			expected = expected_a[ia];
			label = "fdA";
			if (expected)
				ia++;
		}
		else if (which == 1)
		{
			line = get_next_line(fdb);
			expected = expected_b[ib];
			label = "fdB";
			if (expected)
				ib++;
		}
		else
		{
			line = get_next_line(fdc);
			expected = expected_c[ic];
			label = "fdC";
			if (expected)
				ic++;
		}

		if (expected == NULL)
		{
			/* this fd is already exhausted in our expectation table;
			   skip checking (shouldn't normally happen with this order) */
			free(line);
			continue;
		}

		if (line == NULL || strcmp(line, expected) != 0)
		{
			printf("    [%s] step %d: expected \"%s\", got \"%s\"\n",
				label, step, expected, line ? line : "(null)");
			mismatch = 1;
		}
		else
			printf("    [%s] step %d: got \"%s\" (matches)\n", label, step, line);

		free(line);
	}

	/* drain remaining lines on each fd to confirm nothing got corrupted */
	while (ia < 3)
	{
		char *line = get_next_line(fda);
		if (line == NULL || strcmp(line, expected_a[ia]) != 0)
		{
			printf("    [fdA] drain: expected \"%s\", got \"%s\"\n",
				expected_a[ia], line ? line : "(null)");
			mismatch = 1;
			free(line);
			break;
		}
		free(line);
		ia++;
	}
	while (ib < 2)
	{
		char *line = get_next_line(fdb);
		if (line == NULL || strcmp(line, expected_b[ib]) != 0)
		{
			printf("    [fdB] drain: expected \"%s\", got \"%s\"\n",
				expected_b[ib], line ? line : "(null)");
			mismatch = 1;
			free(line);
			break;
		}
		free(line);
		ib++;
	}
	while (ic < 4)
	{
		char *line = get_next_line(fdc);
		if (line == NULL || strcmp(line, expected_c[ic]) != 0)
		{
			printf("    [fdC] drain: expected \"%s\", got \"%s\"\n",
				expected_c[ic], line ? line : "(null)");
			mismatch = 1;
			free(line);
			break;
		}
		free(line);
		ic++;
	}

	/* all three should now be exhausted */
	char *la = get_next_line(fda);
	char *lb = get_next_line(fdb);
	char *lc = get_next_line(fdc);
	if (la != NULL || lb != NULL || lc != NULL)
	{
		printf("    one or more fds did not return NULL after full drain\n");
		mismatch = 1;
	}
	free(la);
	free(lb);
	free(lc);

	if (mismatch)
		FAIL("interleaved multi-fd read", "see details above");
	else
		OK("interleaved multi-fd read (no cross-contamination)");

	close(fda);
	close(fdb);
	close(fdc);

	printf("\n--- reopening a previously used fd number ---\n");
	{
		/*
		** Extra check some implementations get wrong: closing an fd and
		** later reopening a DIFFERENT file that reuses the same fd number
		** should not resume from stale static-buffer data.
		*/
		write_file("/tmp/gnl_tests/reuse1.txt", "first-file-line1\nfirst-file-line2\n");
		int fd1 = open("/tmp/gnl_tests/reuse1.txt", O_RDONLY);
		char *l1 = get_next_line(fd1); /* read only the first line, leave rest unread */
		int reused_ok = (l1 != NULL && strcmp(l1, "first-file-line1\n") == 0);
		free(l1);
		close(fd1); /* fd1's number may now be reused by the OS */

		write_file("/tmp/gnl_tests/reuse2.txt", "second-file-line1\nsecond-file-line2\n");
		int fd2 = open("/tmp/gnl_tests/reuse2.txt", O_RDONLY); /* likely same fd number as fd1 */
		char *l2 = get_next_line(fd2);
		int ok = reused_ok && l2 != NULL && strcmp(l2, "second-file-line1\n") == 0;
		if (ok)
			OK("reused fd number starts fresh (no stale buffer leaking across files)");
		else
		{
			printf("    got \"%s\" (expected \"second-file-line1\\n\")\n", l2 ? l2 : "(null)");
			FAIL("reused fd number starts fresh", "stale buffer likely leaked across fd reuse");
		}
		free(l2);
		close(fd2);
	}

	printf("\n==================================\n");
	printf("Tests run: %d, Failures: %d\n", g_tests, g_fails);
	printf("==================================\n");
	printf("\nNote: this only makes sense to compile against your BONUS\n");
	printf("get_next_line_bonus.c / get_next_line_utils_bonus.c files.\n");
	printf("Run under valgrind/leaks too, especially after interleaving.\n");

	return (g_fails != 0);
}
