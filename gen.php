<?php
// slipshod template generator.
//
// flag:
//   0 => generate header
//   1 => generate source
//
// filter:
//   - prefix: don't show matched keywords
//             e.g ) -cred
//                   will ignore codes which have `cred` keyword
//   default: show matched keywords only
//             e.g ) cred
//                   will show codes which have `cred` keyword
//
// php gen.php libgit2/include/git2/<target>.h (0|1) [filter] > target.h or target.c

$data = file_get_contents($_SERVER['argv'][1]);

$table = array();
$buffer = "";
if (preg_match_all("/GIT_EXTERN\((.+?)\)\s*([a-zA-Z0-9_-]+)\((.+?)\);/s", $data, $match)) {

    for ($i = 0; $i < count($match[0]); $i++) {
        $tmp = array(
            "args" => array(),
        );

        $list = array_map("trim", explode(",", $match[3][$i]));

        $tmp['name'] = $match[2][$i];
        $tmp['retval'] = $match[1][$i];

        $d = count($list);
        if ((preg_match("/(\*\*|out)/", $list[0]) || preg_match("/(write|create|new)/", $match[2][$i]))) {
            $d--;
        }


        if (isset($_SERVER['argv'][3])) {
            if ($_SERVER['argv'][3][0] == "-") {
                $_SERVER['argv'][3] = substr($_SERVER['argv'][3][0], 1);
                $flag = true;
            } else {
                $flag = false;
            }
            if (preg_match("/{$_SERVER['argv'][3]}/", $match[2][$i]) == $flag) {
                continue;
            }
        }

        $match[3][$i] = trim(preg_replace("/\r?\n/", "", $match[3][$i]));
        $match[3][$i] = trim(preg_replace("/\t/", " ", $match[3][$i]));

        if ($_SERVER['argv'][2] == "0") {
            $buffer .= "ZEND_BEGIN_ARG_INFO_EX(arginfo_{$match[2][$i]}, 0, 0, $d)\n";
        }

        $o = 0;
        foreach ($list as $l) {
            $b = array_map(function($l){return trim($l, " *");}, explode(" ", $l));
            $type = substr($l, 0, strrpos($l, " "));

            $n = array_pop($b);
            $b = array_pop($b);

            if ($o == 0 && (preg_match("/(\*\*|out)/", $l) || preg_match("/(write|create|new)/", $match[2][$i]))) {
                $w = 1;
                $tmp['retval'] = "resource";
            }else {
                $w = 0;
            }

            if (!$w) {
                $tmp['args'][] = array(
                    "write" => $w,
                    "name" => $n,
                    "type" => $type,
                );
                if ($_SERVER['argv'][2] == "0") {
                    $buffer .= "\tZEND_ARG_INFO(0, $n)\n";
                }
            }

            $o++;
        }

        if ($_SERVER['argv'][2] == "0") {
            $buffer .= "ZEND_END_ARG_INFO()\n";
            $buffer .= "\n";

        }

        $table[] = $tmp;
    }
}

if ($_SERVER['argv'][2] == "1") {
    $buffer .= '#include "php_git2.h"' . "\n";
    $buffer .= '#include "php_git2_priv.h"' . "\n";
    $buffer .= '#include ".h"' . "\n";
}


foreach ($table as $func) {
    $ret = getReturnType($func['retval']);

    $t = array();
    foreach ($func['args'] as $a) {
        $t[] = $a['name'];
    }
    $sig = join(", ", $t);

    $buffer .= "/* {{{ proto $ret {$func['name']}($sig)\n";
    $buffer .= "*/\n";

    if ($_SERVER['argv'][2] == "0") {
        $buffer .= "PHP_FUNCTION({$func['name']});\n";
        $buffer .= "\n";
    } else {
        $buffer .= "PHP_FUNCTION({$func['name']})\n";
        $buffer .= "{\n";
        $buffer .= getDeclarations($func);

        $buffer .= "\t/* TODO(chobie): implement this */\n";
        $buffer .= "\tphp_error_docref(NULL TSRMLS_CC, E_WARNING, " . '"' . "{$func['name']} not implemented yet" . '"' . ");\n";
        $buffer .= "\treturn;\n\n";

        $buffer .= "\tif (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,\n";
        $buffer .= "\t\t" . sprintf('"%s", %s) == FAILURE) {%s', getParseStr($func), getParseStr2($func), "\n");
        $buffer .= "\t\treturn;\n";
        $buffer .= "\t}\n";
        if (hasResource($func)) {
            $t = $func['args'][0];
            $buffer .= "\tZEND_FETCH_RESOURCE(_{$t['name']}, php_git2_t*, &{$t['name']}, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);\n";
        }
        $buffer .= "}\n";
        $buffer .= "\n";
    }
}

echo $buffer;


function hasResource($func)
{
    $result = false;
    foreach ($func['args'] as $arg) {
        if (preg_match("/char/", $arg['type'])) {
        } else if (preg_match("/git_oid/", $arg['type'])) {
        } else if (preg_match("/git_/", $arg['type'])) {
            $result = true;
        }
    }
    return $result;
}

function getDeclarations($func)
{
    $result = array();
    foreach ($func['args'] as $arg) {
        if (preg_match("/char/", $arg['type'])) {
            $result[] = "\tchar *" . $arg['name'] . " = {0};";
            $result[] = "\tint " . $arg['name'] . "_len;";
        } else if (preg_match("/int/", $arg['type'])) {
            $result[] = "\tlong " . $arg['name'] . ";";
        } else if (preg_match("/git_oid/", $arg['type'])) {
            $result[] = "\tchar *" . $arg['name'] . " = {0};";
            $result[] = "\tint " . $arg['name'] . "_len;";
        } else if (preg_match("/git_/", $arg['type'])) {
            $result[] = "\tzval *" . $arg['name'] . ";";
            $result[] = "\tphp_git2_t *_" . $arg['name'] . ";";
        }
    }
    $result[] = "";
    $result[] = "";

    return join("\n", $result);
}

function getParseStr($func)
{
    $result = array();
    foreach ($func['args'] as $arg) {
        if (preg_match("/char/", $arg['type'])) {
            $result[] = "s";
        } else if (preg_match("/git_oid/", $arg['type'])) {
                $result[] = "s";
        } else if (preg_match("/int/", $arg['type'])) {
            $result[] = "l";
        } else if (preg_match("/git_/", $arg['type'])) {
            $result[] = "r";
        }
    }

    return join("", $result);
}

function getParseStr2($func)
{
    $result = array();
    foreach ($func['args'] as $arg) {
        $result[] = "&" . $arg['name'];
        if (preg_match("/char/", $arg['type'])) {
            $result[] = "&" . $arg['name'] . "_len";
        } else if (preg_match("/git_oid/", $arg['type'])) {
            $result[] = "&" . $arg['name'] . "_len";
        }
    }

    return join(", ", $result);
}

function getReturnType($name)
{
    switch($name) {
        case "int":
            return "long";
        case "void":
            return "void";
        default:
            return "resource";
    }
}