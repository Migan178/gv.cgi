// SPDX-License-Identifier: GPL-2.0-only
// Copyright 2026 Siwoo Jeon
// #include "html.h"
#include "config.h"
#include "html.h"

#include <dirent.h>
#include <git2.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int print_main_page(void)
{
	const struct gv_config *config = get_gv_config();

	int err = 0;
	DIR *dir = NULL;
	struct dirent *entry = NULL;

	dir = opendir(config->repo_root);
	if (dir == NULL) {
		err = 1;
		goto out;
	}

	print_html_wo_body(NULL);
	printf("    <body>\n");
	printf("        <ul>\n");

	while ((entry = readdir(dir)) != NULL) {
		char full_path[PATH_MAX];
		int git_err = 0;
		char *sanitized_html = NULL;

		if (entry->d_type != DT_DIR)
			continue;

		if (strcmp(entry->d_name, ".") == 0 ||
		    strcmp(entry->d_name, "..") == 0)
			continue;

		snprintf(full_path, PATH_MAX, "%s/%s", config->repo_root,
		         entry->d_name);

		git_err = git_repository_open_ext(
		    NULL, full_path, GIT_REPOSITORY_OPEN_NO_SEARCH, NULL);
		if (git_err != 0)
			continue;

		sanitized_html =
		    escape_html(entry->d_name, strlen(entry->d_name));
		if (sanitized_html == NULL)
			continue;

		printf("            <li>%s</li>\n", sanitized_html);

		free(sanitized_html);
	}

	printf("        </ul>\n");
	printf("    </body>\n");
	printf("</html>\n");

	closedir(dir);

out:
	return err;
}
