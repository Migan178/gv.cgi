// SPDX-License-Identifier: GPL-2.0-only
// Copyright 2026 Siwoo Jeon
#include <stdlib.h>
#include <string.h>

// It returns segments count. If it failed, return 0.
size_t parse_path(const char *path, char (*parsed_path)[256],
                  size_t max_segments)
{
	size_t len = strlen(path);
	size_t pos1 = 0;

	char buf[256] = "";
	size_t pos2 = 0;

	for (size_t i = 0; i < len; i++) {
		if (i == 0 && path[i] == '/')
			continue;

		if (path[i] == '/') {
			if (pos2 == 0)
				return 0;

			if ((pos1 + 1) > max_segments)
				return 0;

			buf[pos2] = '\0';
			strcpy(parsed_path[pos1++], buf);
			pos2 = 0;
			memset(buf, 0, sizeof(buf));
			continue;
		}

		buf[pos2++] = path[i];
	}

	if (buf[0] != '\0') {
		if ((pos1 + 1) > max_segments)
			return 0;

		strcpy(parsed_path[pos1++], buf);
	}

	return pos1;
}
