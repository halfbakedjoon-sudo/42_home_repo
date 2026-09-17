#define _DEFAULT_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "libft.h"

int g_tests = 0;
int g_fails = 0;

#define OK(name) do { g_tests++; printf("\x1b[32m[OK]\x1b[0m %s\n", name); } while (0)
#define FAIL(name, detail) do { g_tests++; g_fails++; printf("\x1b[31m[FAIL]\x1b[0m %s -> %s\n", name, detail); } while (0)

/* ---- integer/char checks ---- */
#define CHECK_INT(name, mine, ref) \
	do { \
		int _m = (mine); \
		int _r = (ref); \
		if (_m == _r) OK(name); \
		else { char _buf[128]; snprintf(_buf, sizeof(_buf), "got %d, expected %d", _m, _r); FAIL(name, _buf); } \
	} while (0)

/* ---- string checks (handles NULL) ---- */
#define CHECK_STR(name, mine, ref) \
	do { \
		char *_m = (mine); \
		char *_r = (ref); \
		if ((_m == NULL && _r == NULL) || (_m && _r && strcmp(_m, _r) == 0)) OK(name); \
		else { char _buf[256]; snprintf(_buf, sizeof(_buf), "got \"%s\", expected \"%s\"", _m ? _m : "(null)", _r ? _r : "(null)"); FAIL(name, _buf); } \
	} while (0)

/* ---- memory buffer checks ---- */
#define CHECK_MEM(name, mine, ref, len) \
	do { \
		if (memcmp((mine), (ref), (len)) == 0) OK(name); \
		else FAIL(name, "buffer mismatch"); \
	} while (0)

/* ---- pointer checks (e.g. for return value == first arg) ---- */
#define CHECK_PTR_EQ(name, mine, ref) \
	do { \
		if ((mine) == (ref)) OK(name); \
		else FAIL(name, "pointer mismatch"); \
	} while (0)

/* ---- portable reference implementations ----
** strlcpy / strlcat / strnstr are BSD functions and don't exist on
** Linux glibc, so we implement reference versions here instead of
** depending on the platform's libc (keeps this test buildable
** identically on macOS and Linux).
*/
static size_t ref_strlcpy(char *dst, const char *src, size_t size)
{
	size_t srclen = strlen(src);
	if (size != 0)
	{
		size_t copylen = srclen < size - 1 ? srclen : size - 1;
		memcpy(dst, src, copylen);
		dst[copylen] = '\0';
	}
	return (srclen);
}

static size_t ref_strlcat(char *dst, const char *src, size_t size)
{
	size_t dstlen = strlen(dst);
	size_t srclen = strlen(src);
	if (dstlen >= size)
		return (size + srclen);
	size_t space = size - dstlen - 1;
	size_t copylen = srclen < space ? srclen : space;
	memcpy(dst + dstlen, src, copylen);
	dst[dstlen + copylen] = '\0';
	return (dstlen + srclen);
}

static char *ref_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t needle_len = strlen(needle);
	if (needle_len == 0)
		return ((char *)haystack);
	for (size_t i = 0; haystack[i] && i + needle_len <= len; i++)
	{
		size_t j = 0;
		while (j < needle_len && haystack[i + j] == needle[j])
			j++;
		if (j == needle_len)
			return ((char *)(haystack + i));
	}
	return (NULL);
}

void test_ctype(void)
{
	CHECK_INT("ft_isalpha('a')", !!ft_isalpha('a'), !!isalpha('a'));
	CHECK_INT("ft_isalpha('9')", !!ft_isalpha('9'), !!isalpha('9'));
	CHECK_INT("ft_isdigit('5')", !!ft_isdigit('5'), !!isdigit('5'));
	CHECK_INT("ft_isdigit('a')", !!ft_isdigit('a'), !!isdigit('a'));
	CHECK_INT("ft_isalnum('a')", !!ft_isalnum('a'), !!isalnum('a'));
	CHECK_INT("ft_isalnum('!')", !!ft_isalnum('!'), !!isalnum('!'));
	CHECK_INT("ft_isascii(65)", !!ft_isascii(65), !!isascii(65));
	CHECK_INT("ft_isascii(200)", !!ft_isascii(200), !!isascii(200));
	CHECK_INT("ft_isprint('A')", !!ft_isprint('A'), !!isprint('A'));
	CHECK_INT("ft_isprint('\\n')", !!ft_isprint('\n'), !!isprint('\n'));
	CHECK_INT("ft_toupper('a')", ft_toupper('a'), toupper('a'));
	CHECK_INT("ft_toupper('A')", ft_toupper('A'), toupper('A'));
	CHECK_INT("ft_toupper('1')", ft_toupper('1'), toupper('1'));
	CHECK_INT("ft_tolower('A')", ft_tolower('A'), tolower('A'));
	CHECK_INT("ft_tolower('a')", ft_tolower('a'), tolower('a'));
}

void test_strlen(void)
{
	printf("\n--- ft_strlen ---\n");
	CHECK_INT("ft_strlen(\"hello\")", (int)ft_strlen("hello"), (int)strlen("hello"));
	CHECK_INT("ft_strlen(\"\")", (int)ft_strlen(""), (int)strlen(""));
}

void test_mem_funcs(void)
{
	char a[20];
	char b[20];

	printf("\n--- memory functions ---\n");

	memset(a, 'x', 20);
	ft_memset(b, 'x', 20);
	CHECK_MEM("ft_memset", b, a, 20);

	memset(a, 'y', 10);
	memset(a, 0, 5);
	ft_memset(b, 'y', 10);
	ft_bzero(b, 5);
	memset(a + 5, 0, 5); // align comparison since bzero zeroes first 5, not offset -- adjust below

	{
		char ref[10];
		char mine[10];
		memset(ref, 'z', 10);
		memset(ref, 0, 4);
		memset(mine, 'z', 10);
		ft_bzero(mine, 4);
		CHECK_MEM("ft_bzero", mine, ref, 10);
	}

	{
		char src[20] = "memcpy test string";
		char ref[20];
		char mine[20];
		memcpy(ref, src, 20);
		ft_memcpy(mine, src, 20);
		CHECK_MEM("ft_memcpy", mine, ref, 20);
	}

	{
		char buf1[30] = "overlap test buffer contents";
		char buf2[30] = "overlap test buffer contents";
		memmove(buf1 + 5, buf1, 10);
		ft_memmove(buf2 + 5, buf2, 10);
		CHECK_MEM("ft_memmove (overlap)", buf2, buf1, 30);
	}

	{
		char s1[] = "hello world";
		char s2[] = "hello world";
		CHECK_INT("ft_memcmp (equal)", ft_memcmp(s1, s2, 11) == 0, memcmp(s1, s2, 11) == 0);
		s2[0] = 'H';
		CHECK_INT("ft_memcmp (diff sign)", (ft_memcmp(s1, s2, 11) > 0), (memcmp(s1, s2, 11) > 0));
	}

	{
		char s[] = "hello world";
		void *m = ft_memchr(s, 'w', 11);
		void *r = memchr(s, 'w', 11);
		CHECK_PTR_EQ("ft_memchr (found, offset check)", m - (void *)s, r - (void *)s);
		CHECK_INT("ft_memchr (not found)", ft_memchr(s, 'z', 11) == NULL, memchr(s, 'z', 11) == NULL);
	}
}

void test_strlcpy_strlcat(void)
{
	printf("\n--- ft_strlcpy / ft_strlcat ---\n");
	{
		char dst_ref[20];
		char dst_mine[20];
		size_t r1 = ref_strlcpy(dst_ref, "hello", sizeof(dst_ref));
		size_t r2 = ft_strlcpy(dst_mine, "hello", sizeof(dst_mine));
		CHECK_STR("ft_strlcpy (content)", dst_mine, dst_ref);
		CHECK_INT("ft_strlcpy (return)", (int)r2, (int)r1);
	}
	{
		// truncation case
		char dst_ref[5];
		char dst_mine[5];
		size_t r1 = ref_strlcpy(dst_ref, "hello world", sizeof(dst_ref));
		size_t r2 = ft_strlcpy(dst_mine, "hello world", sizeof(dst_mine));
		CHECK_STR("ft_strlcpy (truncated content)", dst_mine, dst_ref);
		CHECK_INT("ft_strlcpy (truncated return)", (int)r2, (int)r1);
	}
	{
		char dst_ref[20] = "foo";
		char dst_mine[20] = "foo";
		size_t r1 = ref_strlcat(dst_ref, "bar", sizeof(dst_ref));
		size_t r2 = ft_strlcat(dst_mine, "bar", sizeof(dst_mine));
		CHECK_STR("ft_strlcat (content)", dst_mine, dst_ref);
		CHECK_INT("ft_strlcat (return)", (int)r2, (int)r1);
	}
	{
		// truncation case
		char dst_ref[6] = "foo";
		char dst_mine[6] = "foo";
		size_t r1 = ref_strlcat(dst_ref, "barbaz", sizeof(dst_ref));
		size_t r2 = ft_strlcat(dst_mine, "barbaz", sizeof(dst_mine));
		CHECK_STR("ft_strlcat (truncated content)", dst_mine, dst_ref);
		CHECK_INT("ft_strlcat (truncated return)", (int)r2, (int)r1);
	}
}

void test_strchr_strrchr(void)
{
	char s[] = "hello world";

	printf("\n--- ft_strchr / ft_strrchr ---\n");
	CHECK_PTR_EQ("ft_strchr (found)", ft_strchr(s, 'o') - s, strchr(s, 'o') - s);
	CHECK_INT("ft_strchr (not found)", ft_strchr(s, 'z') == NULL, strchr(s, 'z') == NULL);
	CHECK_PTR_EQ("ft_strchr ('\\0')", ft_strchr(s, '\0') - s, strchr(s, '\0') - s);
	CHECK_PTR_EQ("ft_strrchr (found)", ft_strrchr(s, 'o') - s, strrchr(s, 'o') - s);
	CHECK_INT("ft_strrchr (not found)", ft_strrchr(s, 'z') == NULL, strrchr(s, 'z') == NULL);
}

void test_strncmp(void)
{
	printf("\n--- ft_strncmp ---\n");
	CHECK_INT("ft_strncmp (equal)", ft_strncmp("hello", "hello", 5) == 0, strncmp("hello", "hello", 5) == 0);
	CHECK_INT("ft_strncmp (diff sign)", (ft_strncmp("hello", "world", 5) > 0) == (strncmp("hello", "world", 5) > 0), 1);
	CHECK_INT("ft_strncmp (n=0)", ft_strncmp("abc", "xyz", 0), strncmp("abc", "xyz", 0));
	CHECK_INT("ft_strncmp (partial)", ft_strncmp("hello", "help", 3) == 0, strncmp("hello", "help", 3) == 0);
}

void test_strnstr(void)
{
	char s[] = "this is a haystack string";

	printf("\n--- ft_strnstr ---\n");
	{
		char *m = ft_strnstr(s, "haystack", strlen(s));
		char *r = ref_strnstr(s, "haystack", strlen(s));
		CHECK_PTR_EQ("ft_strnstr (found)", m - s, r - s);
	}
	CHECK_INT("ft_strnstr (not found)", ft_strnstr(s, "zzz", strlen(s)) == NULL, 1);
	{
		char *m = ft_strnstr(s, "", strlen(s));
		CHECK_PTR_EQ("ft_strnstr (empty needle)", m, s);
	}
}

void test_atoi(void)
{
	printf("\n--- ft_atoi ---\n");
	CHECK_INT("ft_atoi (\"42\")", ft_atoi("42"), atoi("42"));
	CHECK_INT("ft_atoi (\"-42\")", ft_atoi("-42"), atoi("-42"));
	CHECK_INT("ft_atoi (\"   42\")", ft_atoi("   42"), atoi("   42"));
	CHECK_INT("ft_atoi (\"+42\")", ft_atoi("+42"), atoi("+42"));
	CHECK_INT("ft_atoi (\"42abc\")", ft_atoi("42abc"), atoi("42abc"));
	CHECK_INT("ft_atoi (\"abc\")", ft_atoi("abc"), atoi("abc"));
	CHECK_INT("ft_atoi (\"\")", ft_atoi(""), atoi(""));
	CHECK_INT("ft_atoi (\"-0\")", ft_atoi("-0"), atoi("-0"));
	CHECK_INT("ft_atoi (\"2147483647\")", ft_atoi("2147483647"), atoi("2147483647"));
}

void test_calloc(void)
{
	printf("\n--- ft_calloc ---\n");
	{
		unsigned char *p = ft_calloc(10, 1);
		int all_zero = 1;
		for (int i = 0; i < 10; i++)
			if (p[i] != 0)
				all_zero = 0;
		if (all_zero) OK("ft_calloc (zeroed)");
		else FAIL("ft_calloc (zeroed)", "buffer not zeroed");
		free(p);
	}
}

void test_strdup(void)
{
	printf("\n--- ft_strdup ---\n");
	{
		char *m = ft_strdup("duplicate me");
		CHECK_STR("ft_strdup", m, "duplicate me");
		free(m);
	}
}

void test_substr(void)
{
	printf("\n--- ft_substr ---\n");
	{
		char *m = ft_substr("hello world", 6, 5);
		CHECK_STR("ft_substr (normal)", m, "world");
		free(m);
	}
	{
		char *m = ft_substr("hello world", 6, 100);
		CHECK_STR("ft_substr (len > available)", m, "world");
		free(m);
	}
	{
		char *m = ft_substr("hello world", 50, 5);
		CHECK_STR("ft_substr (start beyond len)", m, "");
		free(m);
	}
}

void test_strjoin(void)
{
	printf("\n--- ft_strjoin ---\n");
	{
		char *m = ft_strjoin("hello ", "world");
		CHECK_STR("ft_strjoin", m, "hello world");
		free(m);
	}
	{
		char *m = ft_strjoin("", "world");
		CHECK_STR("ft_strjoin (empty s1)", m, "world");
		free(m);
	}
}

void test_strtrim(void)
{
	printf("\n--- ft_strtrim ---\n");
	{
		char *m = ft_strtrim("   hello world   ", " ");
		CHECK_STR("ft_strtrim (spaces)", m, "hello world");
		free(m);
	}
	{
		char *m = ft_strtrim("xxhelloxx", "x");
		CHECK_STR("ft_strtrim (custom set)", m, "hello");
		free(m);
	}
	{
		char *m = ft_strtrim("xxxx", "x");
		CHECK_STR("ft_strtrim (all trimmed)", m, "");
		free(m);
	}
}

void test_split(void)
{
	printf("\n--- ft_split ---\n");
	{
		char **m = ft_split("hello world foo", ' ');
		int ok = m && !strcmp(m[0], "hello") && !strcmp(m[1], "world")
			&& !strcmp(m[2], "foo") && m[3] == NULL;
		if (ok) OK("ft_split (basic)");
		else FAIL("ft_split (basic)", "mismatch");
		if (m)
			for (int i = 0; m[i]; i++)
				free(m[i]);
		free(m);
	}
	{
		char **m = ft_split("   a   b   ", ' ');
		int ok = m && !strcmp(m[0], "a") && !strcmp(m[1], "b") && m[2] == NULL;
		if (ok) OK("ft_split (extra delimiters)");
		else FAIL("ft_split (extra delimiters)", "mismatch");
		if (m)
			for (int i = 0; m[i]; i++)
				free(m[i]);
		free(m);
	}
	{
		char **m = ft_split("", ' ');
		int ok = m && m[0] == NULL;
		if (ok) OK("ft_split (empty string)");
		else FAIL("ft_split (empty string)", "mismatch");
		free(m);
	}
}

void test_itoa(void)
{
	printf("\n--- ft_itoa ---\n");
	{
		char *m = ft_itoa(42);
		CHECK_STR("ft_itoa (positive)", m, "42");
		free(m);
	}
	{
		char *m = ft_itoa(-42);
		CHECK_STR("ft_itoa (negative)", m, "-42");
		free(m);
	}
	{
		char *m = ft_itoa(0);
		CHECK_STR("ft_itoa (zero)", m, "0");
		free(m);
	}
	{
		char *m = ft_itoa(2147483647);
		CHECK_STR("ft_itoa (INT_MAX)", m, "2147483647");
		free(m);
	}
	{
		char *m = ft_itoa(-2147483648);
		CHECK_STR("ft_itoa (INT_MIN)", m, "-2147483648");
		free(m);
	}
}

char map_upper(unsigned int i, char c)
{
	(void)i;
	return (toupper(c));
}

void iter_upper(unsigned int i, char *c)
{
	(void)i;
	*c = toupper(*c);
}

void test_strmapi_striteri(void)
{
	printf("\n--- ft_strmapi / ft_striteri ---\n");
	{
		char *m = ft_strmapi("hello", map_upper);
		CHECK_STR("ft_strmapi", m, "HELLO");
		free(m);
	}
	{
		char s[] = "hello";
		ft_striteri(s, iter_upper);
		CHECK_STR("ft_striteri", s, "HELLO");
	}
}

void test_put_fd_funcs(void)
{
	printf("\n--- ft_put*_fd functions (visual check only, no fd 1 return value to compare) ---\n");
	printf("expected : Hd");
	fputc('H', stdout);
	fputc('d', stdout);
	printf("\ngot      : ");
	ft_putchar_fd('H', 1);
	ft_putchar_fd('d', 1);
	printf("\n");

	printf("expected : hello\ngot      : ");
	ft_putstr_fd("hello", 1);
	printf("\n");

	printf("expected : hello\\n\ngot      : ");
	ft_putendl_fd("hello", 1);

	printf("expected : -42\ngot      : ");
	ft_putnbr_fd(-42, 1);
	printf("\n");

	printf("expected : 2147483647\ngot      : ");
	ft_putnbr_fd(2147483647, 1);
	printf("\n");

	printf("expected : -2147483648\ngot      : ");
	ft_putnbr_fd(-2147483648, 1);
	printf("\n");

	printf("(visually verify the lines above match)\n");
}

/* ==================== BONUS: linked list ==================== */

void del_int(void *content)
{
	free(content);
}

int *new_int(int v)
{
	int *p = malloc(sizeof(int));
	*p = v;
	return (p);
}

void *map_double(void *content)
{
	int *p = malloc(sizeof(int));
	*p = (*(int *)content) * 2;
	return (p);
}

int g_iter_sum = 0;
void iter_sum(void *content)
{
	g_iter_sum += *(int *)content;
}

void test_lstnew(void)
{
	printf("\n--- ft_lstnew ---\n");
	{
		int *v = new_int(42);
		t_list *node = ft_lstnew(v);
		if (node && node->content == v && node->next == NULL)
			OK("ft_lstnew (content + next==NULL)");
		else
			FAIL("ft_lstnew (content + next==NULL)", "bad node");
		free(v);
		free(node);
	}
}

void test_lstadd_front(void)
{
	printf("\n--- ft_lstadd_front ---\n");
	{
		t_list *a = ft_lstnew(new_int(1));
		t_list *b = ft_lstnew(new_int(2));
		t_list *c = ft_lstnew(new_int(3));

		ft_lstadd_front(&a, b); // list: b -> a
		ft_lstadd_front(&a, c); // list: c -> b -> a

		int ok = (a == c) && (c->next == b) && (b->next != NULL) && (b->next->next == NULL);
		if (ok)
			OK("ft_lstadd_front (order)");
		else
			FAIL("ft_lstadd_front (order)", "unexpected list shape");

		ft_lstclear(&a, del_int);
		CHECK_INT("ft_lstadd_front (list cleared)", a == NULL, 1);
	}
}

void test_lstsize(void)
{
	printf("\n--- ft_lstsize ---\n");
	{
		t_list *lst = NULL;
		CHECK_INT("ft_lstsize (empty)", ft_lstsize(lst), 0);

		ft_lstadd_front(&lst, ft_lstnew(new_int(1)));
		ft_lstadd_front(&lst, ft_lstnew(new_int(2)));
		ft_lstadd_front(&lst, ft_lstnew(new_int(3)));
		CHECK_INT("ft_lstsize (3 elements)", ft_lstsize(lst), 3);

		ft_lstclear(&lst, del_int);
	}
}

void test_lstlast(void)
{
	printf("\n--- ft_lstlast ---\n");
	{
		t_list *lst = ft_lstnew(new_int(1));
		t_list *b = ft_lstnew(new_int(2));
		t_list *c = ft_lstnew(new_int(3));
		ft_lstadd_back(&lst, b);
		ft_lstadd_back(&lst, c);

		CHECK_PTR_EQ("ft_lstlast (returns last node)", ft_lstlast(lst), c);

		ft_lstclear(&lst, del_int);
	}
	{
		CHECK_INT("ft_lstlast (empty list -> NULL)", ft_lstlast(NULL) == NULL, 1);
	}
}

void test_lstadd_back(void)
{
	printf("\n--- ft_lstadd_back ---\n");
	{
		t_list *lst = ft_lstnew(new_int(1));
		ft_lstadd_back(&lst, ft_lstnew(new_int(2)));
		ft_lstadd_back(&lst, ft_lstnew(new_int(3)));

		int ok = *(int *)lst->content == 1
			&& *(int *)lst->next->content == 2
			&& *(int *)lst->next->next->content == 3
			&& lst->next->next->next == NULL;
		if (ok)
			OK("ft_lstadd_back (order)");
		else
			FAIL("ft_lstadd_back (order)", "unexpected list shape");

		ft_lstclear(&lst, del_int);
	}
	{
		// adding to an empty list (NULL) should set *lst to new node
		t_list *lst = NULL;
		t_list *node = ft_lstnew(new_int(99));
		ft_lstadd_back(&lst, node);
		CHECK_PTR_EQ("ft_lstadd_back (empty list becomes node)", lst, node);
		ft_lstclear(&lst, del_int);
	}
}

void test_lstdelone(void)
{
	printf("\n--- ft_lstdelone ---\n");
	{
		int *v = new_int(7);
		t_list *node = ft_lstnew(v);
		ft_lstdelone(node, del_int);
		// content freed, node itself freed by ft_lstdelone -- nothing to assert directly
		// without valgrind, so we just confirm the program didn't crash.
		OK("ft_lstdelone (ran without crashing)");
	}
}

void test_lstclear(void)
{
	printf("\n--- ft_lstclear ---\n");
	{
		t_list *lst = ft_lstnew(new_int(1));
		ft_lstadd_back(&lst, ft_lstnew(new_int(2)));
		ft_lstadd_back(&lst, ft_lstnew(new_int(3)));

		ft_lstclear(&lst, del_int);
		CHECK_INT("ft_lstclear (list becomes NULL)", lst == NULL, 1);
	}
}

void test_lstiter(void)
{
	printf("\n--- ft_lstiter ---\n");
	{
		t_list *lst = ft_lstnew(new_int(1));
		ft_lstadd_back(&lst, ft_lstnew(new_int(2)));
		ft_lstadd_back(&lst, ft_lstnew(new_int(3)));

		g_iter_sum = 0;
		ft_lstiter(lst, iter_sum);
		CHECK_INT("ft_lstiter (sum of contents)", g_iter_sum, 6);

		ft_lstclear(&lst, del_int);
	}
}

void test_lstmap(void)
{
	printf("\n--- ft_lstmap ---\n");
	{
		t_list *lst = ft_lstnew(new_int(1));
		ft_lstadd_back(&lst, ft_lstnew(new_int(2)));
		ft_lstadd_back(&lst, ft_lstnew(new_int(3)));

		t_list *mapped = ft_lstmap(lst, map_double, del_int);

		int ok = mapped
			&& *(int *)mapped->content == 2
			&& *(int *)mapped->next->content == 4
			&& *(int *)mapped->next->next->content == 6
			&& mapped->next->next->next == NULL;
		if (ok)
			OK("ft_lstmap (doubled values)");
		else
			FAIL("ft_lstmap (doubled values)", "unexpected mapped list");

		CHECK_INT("ft_lstmap (original list untouched)", *(int *)lst->content, 1);

		ft_lstclear(&lst, del_int);
		ft_lstclear(&mapped, del_int);
	}
	{
		// mapping an empty list should return NULL
		t_list *mapped = ft_lstmap(NULL, map_double, del_int);
		CHECK_INT("ft_lstmap (empty list -> NULL)", mapped == NULL, 1);
	}
}

void test_linked_list_bonus(void)
{
	test_lstnew();
	test_lstadd_front();
	test_lstsize();
	test_lstlast();
	test_lstadd_back();
	test_lstdelone();
	test_lstclear();
	test_lstiter();
	test_lstmap();
}

int main(void)
{
	setbuf(stdout, NULL);

	test_ctype();
	test_strlen();
	test_mem_funcs();
	test_strlcpy_strlcat();
	test_strchr_strrchr();
	test_strncmp();
	test_strnstr();
	test_atoi();
	test_calloc();
	test_strdup();
	test_substr();
	test_strjoin();
	test_strtrim();
	test_split();
	test_itoa();
	test_strmapi_striteri();
	test_put_fd_funcs();

	printf("\n=========== BONUS: linked list ===========\n");
	test_linked_list_bonus();

	printf("\n==================================\n");
	printf("Tests run: %d, Failures: %d\n", g_tests, g_fails);
	printf("==================================\n");

	return (g_fails != 0);
}
