<?php
$repo = git_repository_open("../");
$reflog = git_reflog_read($repo, "HEAD");

$count = git_reflog_entrycount($reflog);
for ($i = 0; $i < $count; $i++) {
    $entry = git_reflog_entry_byindex($reflog, $i);
    var_dump(git_reflog_entry_committer($entry));
}
