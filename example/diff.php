<?php
$repo = git_repository_open(".");
$tree = git_tree_lookup($repo, "e14ccb8e18d632d78ce2f0aeb06597a03f42b237");
$diff = git_diff_tree_to_workdir($repo, $tree, array());

$p = array();
git_diff_print($diff, GIT_DIFF_FORMAT_PATCH, function($diff_delta, $diff_hunk, $diff_line, $payload){
    if ($diff_line['origin'] == "-" || $diff_line['origin'] == "+") {
        echo $diff_line['origin'];
    }
    echo $diff_line['content'];
}, $p);
