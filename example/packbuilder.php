<?php

$repo = git_repository_open(".");
$pb = git_packbuilder_new($repo);


git_packbuilder_insert_commit($pb, "7a66238ef5f12f754b511f0dfec891c061dbc2e0");
git_packbuilder_insert_commit($pb, "c3b172cda6993b06e8ae6b1bc7f1364968e112c9");

$p = array();
git_packbuilder_set_callbacks($pb, function($stage, $current, $total, &$payload){
    echo $stage;
}, $p);
git_packbuilder_write($pb, "/tmp/pack", 0,function($stats, &$payload){
    var_dump($stats);
}, $p);
git_packbuilder_foreach($pb, function($b, $size, &$payload) {
    echo $size . PHP_EOL;
}, $p);
$hash = git_packbuilder_hash($pb);
var_dump($hash);