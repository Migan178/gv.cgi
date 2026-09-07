// SPDX-License-Identifier: GPL-2.0-only
// Copyright 2026 Siwoo Jeon
#pragma once

#include <stddef.h>

char *escape_html(const char *src, size_t len);

char *escape_html_str(const char *src);

void print_html_wo_body(const char *head);

void print_html_close_body();

void print_html(const char *head, const char *body);
