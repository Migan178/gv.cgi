// SPDX-License-Identifier: GPL-2.0-only
// Copyright 2026 Siwoo Jeon
#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ESCAPED_LEFT_ARROW "&lt;"
#define ESCAPED_RIGHT_ARROW "&gt;"
#define ESCAPED_AT_SIGN "&amp;"
#define ESCAPED_SINGLE_QUOTE "&#39;"
#define ESCAPED_DOUBLE_QUOTE "&quot;"

static inline int check_left_arrow(char src) { return src == '<'; }
static inline int check_right_arrow(char src) { return src == '>'; }
static inline int check_at_sign(char src) { return src == '&'; }
static inline int check_single_qt(char src) { return src == '\''; }
static inline int check_double_qt(char src) { return src == '"'; }

static inline size_t get_len_to_add(char *src, size_t i)
{
	if (check_left_arrow(src[i]) || check_right_arrow(src[i]))
		return 3;

	if (check_at_sign(src[i]) || check_single_qt(src[i]))
		return 4;

	if (check_double_qt(src[i]))
		return 5;

	return 0;
}

// The function uses heap. you should free it.
char *escape_html(char *src, size_t len)
{
	size_t added_len = len, pos = 0;
	char *sanitized_html = NULL;

	for (size_t i = 0; i < len; i++)
		added_len += get_len_to_add(src, i);

	sanitized_html = (char *)malloc(added_len + 1);
	if (sanitized_html == NULL)
		return NULL;

	for (size_t i = 0; i < len; i++) {
		if (check_left_arrow(src[i])) {
			memcpy(&sanitized_html[pos], ESCAPED_LEFT_ARROW, 4);
			pos += 4;
			continue;
		}

		if (check_right_arrow(src[i])) {
			memcpy(&sanitized_html[pos], ESCAPED_RIGHT_ARROW, 4);
			pos += 4;
			continue;
		}

		if (check_at_sign(src[i])) {
			memcpy(&sanitized_html[pos], ESCAPED_AT_SIGN, 5);
			pos += 5;
			continue;
		}

		if (check_single_qt(src[i])) {
			memcpy(&sanitized_html[pos], ESCAPED_SINGLE_QUOTE, 5);
			pos += 5;
			continue;
		}

		if (check_double_qt(src[i])) {
			memcpy(&sanitized_html[pos], ESCAPED_DOUBLE_QUOTE, 6);
			pos += 6;
			continue;
		}

		sanitized_html[pos++] = src[i];
	}

	sanitized_html[pos] = '\0';

	return sanitized_html;
}

// Before use the function, YOU SHOULD USE escape_html when include untrusted
// text.
// It doesn't close html. you should close html tag.
void print_html_wo_body(const char *head)
{
	printf("<!DOCTYPE html>\n");
	printf("<html lang=\"en-US\">\n");
	printf("    <head>\n");
	printf("        <title>%s</title>\n", get_gv_config()->repo_root);
	if (head != NULL)
		printf("        %s\n", head);
	printf("    </head>\n");
}

// Before use the function, YOU SHOULD USE escape_html when include untrusted
// text.
void print_html(const char *head, const char *body)
{
	print_html_wo_body(head);
	printf("    <body>\n");
	printf("        %s\n", body);
	printf("    </body>\n");
	printf("</html>\n");
}
