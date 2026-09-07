// SPDX-License-Identifier: GPL-2.0-only
// Copyright 2026 Siwoo Jeon
#include "config.h"
#include "html.h"
#include "http.h"

#include <git2.h>
#include <limits.h>
#include <stdio.h>

int print_repo_summary_page(char *repo_path)
{
	const struct gv_config *config = get_gv_config();
	int err = 0;
	int status = 200;
	int i = 0;

	git_repository *repo = NULL;
	git_revwalk *walk = NULL;
	struct git_oid id;

	char full_path[PATH_MAX];

	snprintf(full_path, PATH_MAX, "%s/%s", config->repo_root, repo_path);

	err = git_repository_open_ext(&repo, full_path,
	                              GIT_REPOSITORY_OPEN_NO_SEARCH, NULL);
	if (err != 0) {
		status = 404;
		goto out;
	}

	err = git_revwalk_new(&walk, repo);
	if (err != 0) {
		status = 500;
		goto out_repo_free;
	}

	err = git_revwalk_push_head(walk);
	if (err != 0) {
		status = 500;
		goto out_revwalk_free;
	}

	printf(HEADER, CONTENT_TYPE_HTML, CONTENT_SEPARATOR);
	print_html_wo_body(NULL);

	while (i < 10 && !git_revwalk_next(&id, walk)) {
		git_commit *commit = NULL;
		char *sanitized_html = NULL;

		err = git_commit_lookup(&commit, repo, &id);
		if (err != 0) {
			i++;
			continue;
		}

		sanitized_html = escape_html_str(git_commit_message(commit));
		if (sanitized_html == NULL) {
			i++;
			git_commit_free(commit);
			continue;
		}

		printf("        <h1>%s</h1>\n", sanitized_html);

		free(sanitized_html);

		git_commit_free(commit);

		i++;
	}

	print_html_close_body();

out_revwalk_free:
	git_revwalk_free(walk);
out_repo_free:
	git_repository_free(repo);
out:
	switch (status) {
	case 404:
		printf(HEADER, STATUS_404, HEADER_SEPARATOR);
		printf(HEADER, CONTENT_TYPE_HTML, CONTENT_SEPARATOR);
		print_html(NULL, "<h1>the repo not found</h1>");
		break;
	case 500:
		printf(HEADER, STATUS_500, HEADER_SEPARATOR);
		printf(HEADER, CONTENT_TYPE_HTML, CONTENT_SEPARATOR);
		print_html(NULL, "<h1>invalid repo</h1>");
		break;
	case 200:
	default:
		break;
	}
	return err;
}
