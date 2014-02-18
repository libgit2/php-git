<?php
$repo = git_repository_open(".");
$options = git_blame_options_new();
$blame = git_blame_file($repo, "README.md", $options);
$obj = git_revparse_single($repo, "HEAD:README.md");
$id = git_object_id($obj);
$blob = git_blob_lookup($repo, $id);
$raw = git_blob_rawcontent($blob);

$i = 0;
$lines = explode("\n", $raw);
foreach ($lines as $data) {
    $hunk = git_blame_get_hunk_byline($blame, $i+1);
    if (!$hunk) {
        continue;
    }

    $sig = sprintf("%s <%s>", $hunk['final_signature']['name'], $hunk['final_signature']['email']);
    printf("%s ( %-30s, %4d) %s\n", substr($hunk['final_commit_id'], 10),
        $sig,
        $i+1,
        $data
    );
    $i++;
}