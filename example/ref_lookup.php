<?php
$repo = git_repository_open("../");

$ref = git_reference_dwim($repo, "functions");
$obj =  git_reference_peel($ref, GIT_OBJ_ANY);
echo git_object_id($obj);
