<?php
$repo = git_repository_open(".");
$list = git_status_list_new($repo, array(
));

$payload = array();
printf("# Changes to be committed:\n");
printf("#   (use \"git reset HEAD <file>...\" to unstage)\n");
printf("#\n");

$cnt = git_status_list_entrycount($list);
for ($i = 0; $i < $cnt; $i++) {
    $entry = git_status_byindex($list, $i);
    $flags = $entry['status'];
    $stat = getStat($flags);

    if (is_array($entry['head_to_index'])) {
        printf("# %15s %s\n", $stat, $entry['head_to_index']['new_file']['path']);
    }
}

printf("#\n");
printf("# Changes not staged for commit:\n");
printf("#   (use \"git add <file>...\" to update what will be committed)\n");
printf("#   (use \"git checkout -- <file>...\" to discard changes in working directory)\n");
printf("#\n");

for ($i = 0; $i < $cnt; $i++) {
    $entry = git_status_byindex($list, $i);
    $flags = $entry['status'];
    $stat = getStat($flags);

    if (is_array($entry['index_to_workdir'])) {
        printf("# %15s %s\n", $stat, $entry['index_to_workdir']['new_file']['path']);
    }
}
printf("#\n");


function getStat($flags)
{
    $stat = "";
    if ($flags & GIT_STATUS_IGNORED) {
        return;
    }
    if ($flags == GIT_STATUS_CURRENT) {
        return;
    }
    if ($flags & GIT_STATUS_INDEX_NEW){
        $stat = "new file:";
    }
    if ($flags & GIT_STATUS_WT_NEW) {
        $stat = "untracked:";
    }
    if ($flags & GIT_STATUS_INDEX_MODIFIED ||$flags & GIT_STATUS_WT_MODIFIED) {
        $stat = "modified:";
    }
    if ($flags & GIT_STATUS_INDEX_DELETED || $flags & GIT_STATUS_WT_DELETED) {
        $stat = "deleted:";
    }
    if ($flags & GIT_STATUS_INDEX_RENAMED || $flags & GIT_STATUS_WT_RENAMED) {
        $stat = "renamed:";
    }
    if ($flags & GIT_STATUS_INDEX_TYPECHANGE || $flags & GIT_STATUS_WT_TYPECHANGE) {
        $stat = "typechange:";
    }
    return $stat;
}