// SPDX-License-Identifier: GPL-2.0-only
// Copyright 2026 Siwoo Jeon
#include "html.h"
#include "main_page.h"

#include <git2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HEADER "%s%s"
#define CONTENT_TYPE_HTML "Content-Type: text/html"
#define HEADER_SEPARATOR "\r\n"
#define CONTENT_SEPARATOR "\r\n\r\n"

#define STATUS_405 "Status: 405 Method Not Allowed"
#define STATUS_500 "Status: 500 Internal Server Error"

int main(void)
{
	int err = 0;
	int init_count = 0;
	const git_error *git_err;

	char *method = NULL;
	char *path_info = NULL;

	init_count = git_libgit2_init();
	if (init_count < 0) {
		printf(HEADER, CONTENT_TYPE_HTML, HEADER_SEPARATOR);
		printf(HEADER, STATUS_500, CONTENT_SEPARATOR);
		print_html(NULL, "<h1>Failed to initialize server</h1>");

		goto out;
	}

	method = getenv("REQUEST_METHOD");
	if (method == NULL || strcmp(method, "GET") != 0) {
		printf(HEADER, CONTENT_TYPE_HTML, HEADER_SEPARATOR);
		printf(HEADER, STATUS_405, CONTENT_SEPARATOR);
		print_html(NULL, "<h1>Wrong Method</h1>");

		goto out_git_shutdown;
	}

	path_info = getenv("PATH_INFO");
	if (path_info == NULL || strcmp(path_info, "/") == 0 ||
	    path_info[0] == '\0') {
		err = print_main_page();
	}

out_git_shutdown:
	init_count = git_libgit2_shutdown();
out:
	if (err < 0 || init_count < 0) {
		git_err = git_error_last();
		if (git_err != NULL && git_err->message != NULL)
			fprintf(stderr, "%s\n", git_err->message);

		if (err < 1)
			err = 1;
	}

	return err;
}
