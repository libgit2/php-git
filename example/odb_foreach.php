<?php
$repo = git_repository_open(".");
$odb = git_repository_odb($repo);

$payload = array();
git_odb_foreach($odb, function($oid, &$payload) {
    echo $oid . PHP_EOL;
}, $payload);