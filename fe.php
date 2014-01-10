<?php
// php fe.php reference.c
$data = file_get_contents($_SERVER['argv'][1]);

if (preg_match_all("/PHP_FUNCTION\((.+?)\)/", $data, $match)) {
    foreach ($match[1] as $m) {
        printf("\tPHP_FE(%s, arginfo_%s)\n", $m, $m);
    }
}