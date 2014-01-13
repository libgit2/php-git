<?php
$repo = git_repository_open("../");
$obj = git_revparse_single($repo, "HEAD^{tree}");

$payload = array();
git_tree_walk($obj, GIT_TREEWALK_PRE, function($root, $entry, &$payload) {
    echo git_tree_entry_name($entry) . PHP_EOL;
}, $payload);
