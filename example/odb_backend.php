<?php

class Pool
{
    public static $pool = array();
}

$a = array(
    "read" => function($oid){
        echo "\e[32m# read $oid\e[m\n";
        return array(
            Pool::$pool[$oid][0],
            Pool::$pool[$oid][1],
        );
    },
    "read_prefix" => function($short_oid){
            echo "\e[32m# read_prefix $short_oid\e[m\n";

            $actual_oid = null;
            foreach (Pool::$pool as $key => $value) {
                if (preg_match("/^{$short_oid}/", $key)) {
                    $actual_oid = $key;
                    break;
                }
            }

            return array(
                Pool::$pool[$actual_oid][0],
                Pool::$pool[$actual_oid][1],
                $actual_oid,
            );
    },
    "read_header" => function($oid) {
            echo "\e[32m# read header$oid\e[m\n";
            return array(
                strlen(Pool::$pool[$oid][0]),
                Pool::$pool[$oid][1],
            );
    },
    "write" => function($oid, $buffer, $otype) {
            echo "\e[32m# write $oid\e[m\n";
            Pool::$pool[$oid] = array($buffer, $otype);
    },
    "writestream" => function() {

    },
    "readstream" => function() {

    },
    "exists" => function($oid) {
            $retval = 0;
            if (isset(Pool::$pool[$oid])) {
                $retval = 1;
            }

            echo "\e[32m# exists $retval\e[m\n";
            return $retval;
    },
    "refresh" => function() {
            echo "\e[32m# refreshed!\e[m\n";
    },
    "foreach" => function($foreach_cb, &$payload) { // this payload was passed by git_odb_foreach callback.
            echo "\e[32m# foreach (iterate all backends)\e[m\n";
            foreach (Pool::$pool as $oid => $value) {
                $retval = $foreach_cb($oid, $payload);
                if ($retval == GIT_EUSER) {
                    return $retval;
                }
            }
            return 0;
    },
    "writepack" => function() {

    },
    "free" => function() {
            echo "\e[32m# free'd!\e[m\n";
    }
);
$memory_backend = git_odb_backend_new($a);

$repo = git_repository_open(".");
$odb = git_repository_odb($repo);
git_odb_add_backend($odb, $memory_backend, 1000);

$oid = git_odb_write($odb, "Helo World(php memory backend)", GIT_OBJ_BLOB);
$obj = git_odb_read($odb, $oid);

echo git_odb_object_data($obj);
echo "\n";

$header = git_odb_read_header($odb, $oid);
var_dump($header); // size, otype

$obj = git_odb_read_prefix($odb, substr($oid, 0, 10));
var_dump($obj);

$payload = array();
git_odb_foreach($odb, function($oid, &$payload) {
    echo ".";
}, $payload);
echo PHP_EOL;
git_odb_refresh($odb);
exit;
