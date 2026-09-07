// SPDX-License-Identifier: GPL-2.0-only
// Copyright 2026 Siwoo Jeon
#pragma once

struct gv_config {
	char *repo_root;
	char *title;
};

const struct gv_config *get_gv_config(void);
