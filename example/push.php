<?php

$payload = array();
$repo    = git_repository_open(".");
$remote  = git_remote_load($repo, "origin");
$remote_callbacks = [
    "credentials" => function($url, $username_from_url, $allowed_types, &$payload) {
        // NOTE(chobie): you need to build with LibSSH2 when communicating with ssh protocol. */
        if ($allowed_types & GIT_CREDTYPE_USERPASS_PLAINTEXT) {
            return git_cred_userpass_plaintext_new("chobie", getenv("GITHUB_TOKEN"));
        } else {
            error_log("not supported allowed types");
        }
}];

git_remote_set_callbacks($remote, $remote_callbacks);
if (git_remote_connect($remote, GIT_DIRECTION_PUSH)) {
    $push = git_push_new($remote);

    git_push_add_refspec($push, "refs/heads/master:refs/heads/master");
    git_push_finish($push);
    git_push_unpack_ok($push);

    git_push_status_foreach($push, function($ref, $name, &$payload){
        var_dump($ref, $name, $payload);
    }, $payload);

    git_push_update_tips($push);
    git_remote_disconnect($remote);
}
