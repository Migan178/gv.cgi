// SPDX-License-Identifier: GPL-2.0-only
// Copyright 2026 Siwoo Jeon
#pragma once

#include <stddef.h>

size_t parse_path(const char *path, char (*parsed_path)[256],
                  size_t max_segments);
