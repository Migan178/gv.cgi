// SPDX-License-Identifier: GPL-2.0-only
// Copyright 2026 Siwoo Jeon
#include <stdlib.h>

struct gv_config {
	char *repo_root;
	char *title;
};

static int initialized = 0;
static struct gv_config config;

static inline void set_gv_config(void)
{
	initialized = 1;

	config.repo_root = getenv("GV_PATH");
	if (config.repo_root == NULL)
		config.repo_root = "/var/git";

	config.title = getenv("GV_TITLE");
	if (config.title == NULL)
		config.title = "gv.cgi";
}

const struct gv_config *get_gv_config(void)
{
	if (!initialized)
		set_gv_config();

	return &config;
}
