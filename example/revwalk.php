<?php
$repo = git_repository_open("../");
$walker = git_revwalk_new($repo);
git_revwalk_push_range($walker, "HEAD~20..HEAD");

while ($id = git_revwalk_next($walker)) {
    echo $id . PHP_EOL;
}
