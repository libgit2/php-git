<?php
$repo = git_repository_open(".");

$a = array(
    // attributes are white space separated string.
    // e.g) .gitattribute
    //   *.php filter=chobie
    //
    // will return $attr[0] = false, $attr[1] = "chobie" with *.php files. see check callback.
    "attributes" => "chobie filter",
    "initialize" => function () {
            echo "\e[32m# Initialize\e[m\n";
    },
    "check" => function ($payload, $src, $attr) {
            echo "\e[32m# Check\e[m\n";
            var_dump($src);
            var_dump($attr);

            // return true means apply filter to this file.
            return true;
    },
    "apply" => function ($payload, $from, $src) {
            echo "\e[32m# Apply\e[m\n";
            // apply function should return string or GIT_PASSTHROUGH
            return preg_replace("/\s/", "", $from);
    },
    "shutdown" => function () {
            echo "\n\e[32m# Shutdown\e[m\n";
    },
    "cleanup" => function () {
            echo "\e[32m# clean up\e[m\n";
    }
);

$v = git_filter_new($a);
git_filter_register("chobie", $v, 100);

$blob = git_blob_lookup($repo, "74f5770df516cbbef16372a7628a9528277637d6");
$l = git_filter_list_load($repo, $blob, "example/diff.php", GIT_FILTER_SMUDGE);

echo "\e[32m# <<< ORIGINAL CONTENT >>>\e[m\n";
echo git_blob_rawcontent($blob);

echo "\e[32m# <<< FILTERED CONTENT >>>\e[m\n";
$out = git_filter_list_apply_to_blob($l, $blob);
echo $out;
