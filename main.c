// SPDX-License-Identifier: GPL-2.0-only
// Copyright 2026 Siwoo Jeon
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CONTENT_TYPE_HTML "Content-Type: text/html"
#define SEPARATOR "\r\n\r\n"

int main(void)
{
	char *method = NULL;

	method = getenv("REQUEST_METHOD");
	if (method == NULL || strcmp(method, "GET") != 0) {
		printf("%s%s", CONTENT_TYPE_HTML, SEPARATOR);
		printf("<html><head><title>cgi</title></head><body><h1>WRONG "
		       "METHOD</h1></body></html>\n");
		return 1;
	}

	printf("%s%s", CONTENT_TYPE_HTML, SEPARATOR);
	printf("<html><head><title>cgi</title></head><body><h1>CORRECT "
	       "METHOD</h1></body></html>\n");
	return 0;
}
