// SPDX-License-Identifier: GPL-2.0-only
// Copyright 2026 Siwoo Jeon
#include "html.h"
#include "http.h"
#include "main_page.h"
#include "path.h"
#include "repo_pages.h"

#include <git2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	int err = 0;
	int init_count = 0;
	const git_error *git_err;

	char *method = NULL;
	char *path_info = NULL;
	size_t segments, max_segments = 16;
	char path[max_segments][256];

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
	} else {
		segments = parse_path(path_info, path, max_segments);
		if (segments == 0) {
			printf(HEADER, CONTENT_TYPE_HTML, HEADER_SEPARATOR);
			printf(HEADER, STATUS_400, CONTENT_SEPARATOR);
			print_html(NULL, "<h1>wrong location</h1>");
			goto out_git_shutdown;
		}

		if (segments == 1) {
			err = print_repo_summary_page(path[0]);
		}
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
