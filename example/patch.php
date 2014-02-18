<?php
$repo = git_repository_open(".");
$tree = git_tree_lookup($repo, "e14ccb8e18d632d78ce2f0aeb06597a03f42b237");
$diff = git_diff_tree_to_workdir($repo, $tree, git_diff_options_init());

$payload = array();
$patch = git_patch_from_diff($diff, 1);
git_patch_print($patch, function($diff_delta, $diff_hunk, $diff_line, $payload){
    if ($diff_line['origin'] == "-" || $diff_line['origin'] == "+") {
        echo $diff_line['origin'];
    }
    echo $diff_line['content'];
}, $payload);