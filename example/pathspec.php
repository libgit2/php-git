<?php
$repo = git_repository_open(".");
$ps = git_pathspec_new(array("*.php"));
$list = git_pathspec_match_workdir($repo, GIT_PATHSPEC_FIND_FAILURES, $ps);
for ($i = 0; $i < git_pathspec_match_list_entrycount($list); $i++) {
    $entry = git_pathspec_match_list_entry($list, $i);
    printf("%s\n", $entry);
}
