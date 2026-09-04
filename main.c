// SPDX-License-Identifier: GPL-2.0-only
// Copyright 2026 Siwoo Jeon
#include <git2.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if (argc <= 1) {
		fprintf(stderr, "git repository must be provided!\n");
		return 1;
	}

	int err = 0;
	const git_error *git_err = NULL;

	struct git_repository *repo = NULL;
	struct git_revwalk *walk = NULL;
	git_oid oid;

	git_commit *commit = NULL;
	const struct git_signature *author = NULL;

	err = git_libgit2_init();
	if (err < 0) {
		goto out;
	}

	err = git_repository_open(&repo, argv[1]);
	if (err != 0) {
		goto out;
	}

	err = git_revwalk_new(&walk, repo);
	if (err != 0) {
		goto out_repo_free;
	}

	err = git_revwalk_push_head(walk);
	if (err != 0) {
		goto out_revwalk_free;
	}

	while (!git_revwalk_next(&oid, walk)) {
		if (git_commit_lookup(&commit, repo, &oid) != 0) {
			continue;
		}

		author = git_commit_author(commit);

		printf("commit %s\n", git_oid_tostr_s(git_commit_id(commit)));
		printf("Author:      %s <%s>\n", author->name, author->email);
		printf("Timestamp:   %lld\n", author->when.time);
		printf("\n   %s\n", git_commit_message(commit));

		git_commit_free(commit);
	}

out_revwalk_free:
	git_revwalk_free(walk);
out_repo_free:
	git_repository_free(repo);
out:
	if (err != 0) {
		git_err = git_error_last();
		fprintf(stderr, "%s\n", git_err->message);
	}

	git_libgit2_shutdown();

	return err;
}
