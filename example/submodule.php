<?php
$repo = git_repository_open(".");
$payload = array();

// NOTE(chobie): currently, information support only
git_submodule_foreach($repo, function($sm, $name, &$payload){
    var_dump($sm); // resource submodule
    var_dump($name);
}, $payload);
