<?php

$data = 'GIT_EXTERN(int) git_revparse_single(
        git_object **out, git_repository *repo, const char *spec);';
$data = 'GIT_EXTERN(int) git_revparse_ext(
        git_object **object_out,
        git_reference **reference_out,
        git_repository *repo,
        const char *spec);';

class Func
{
    protected $name;
    protected $return_type;
    protected $args = array();
    protected $ptr = 0;
    protected $const;

    public function __construct($name, $return_type)
    {
        $this->name = $name;
        $this->return_type = preg_replace("/\*/", "", $return_type);

        for ($i = 0; $i < count($return_type); $i++) {
            if ($return_type[$i] == '*') {
                $this->ptr++;
            }
        }
    }

    public function getReturnType()
    {
        return $this->return_type;
    }

    public function isResourceCreator()
    {
        if (count($this->args)) {
            $first = $this->args[0];
            if (preg_match("/out/", $first->getName())) {
                return true;
            }
        } else {
            if (preg_match("/git_/", $this->getReturnType())) {
                return true;
            }
        }

        return false;
    }

    public function isStringCreator()
    {
        if (preg_match("/(char)/", $this->getReturnType())) {
            return true;
        }
    }

    public function isLongCreator()
    {
        if (preg_match("/(size_t|int)/", $this->getReturnType())) {
            return true;
        }
    }

    public function isArrayCreator()
    {
        if (preg_match("/git_/", $this->getReturnType())) {
            return true;
        }
    }

    public function isVoidCreator()
    {
        if (preg_match("/void/", $this->getReturnType())) {
            return true;
        }
    }

    public function isSavior()
    {
        if (preg_match('/_free$/', $this->getName())) {
            return true;
        }
    }

    public function getArguments()
    {
        return $this->args;
    }

    public function addArgument(Arg $arg)
    {
        $this->args[] = $arg;
    }

    public function getName()
    {
        return $this->name;
    }

    public function first()
    {
        return $this->args[0];
    }
}

class Arg
{
    protected $type;
    protected $ptr = 0;
    protected $name;
    protected $const;

    public function getDefaultValue()
    {
        if (preg_match("/long/", $this->getZendType())) {
            return "0";
        } else {
            return "NULL";
        }
    }

    public function getName()
    {
        return $this->name;
    }

    public function setName($name)
    {
        return $this->name = $name;
    }


    public function getType()
    {
        return $this->type;
    }

    public function getPtr()
    {
        return str_repeat("*", $this->ptr - 1);
    }

    public function shouldWrite()
    {
        if ($this->ptr == 2) {
            if (preg_match("/^git_/", $this->type)) {
                return true;
            }
        }

        return false;

    }

    public function getZendType()
    {
        if (preg_match("/char/", $this->type)) {
            return "char";
        } else if (preg_match("/(size_t|int)/", $this->type)) {
            return "long";
        } else if (preg_match("/git_oid/", $this->type)) {
            return "char";
        } else if (preg_match("/^git_/", $this->type)) {
            return "zval";
        } else {
            error_log(sprintf("%s (zendtype)", $this->type));
        }
    }

    public function __construct($type, $name)
    {
        $this->type = $type;
        $this->name = $name;

        for ($i = 0; $i < strlen($name); $i++) {
            if ($name[$i] == '*') {
                $this->ptr++;
            }
        }
        $this->name = preg_replace("/\*/", "", $this->name);
        if (preg_match("/^const/", $this->type)) {
            $this->const = 1;
            $this->type = preg_replace("/^const\s+/", "", $this->type);
        }
    }
}

class StringStream
{
    protected $buffer = "";

    public function __construct($string = "")
    {
        $this->buffer = $string;
    }

    public function append($string)
    {
        $this->buffer .= $string;
    }

    public function assign($message)
    {
        $this->buffer = $message;
    }

    public function __toString()
    {
        return $this->buffer;
    }
}

class ZeroCopyOutputStream
{
    protected $stream;

    public function __construct($stream)
    {
        $this->stream = $stream;
    }

    public function write($message)
    {
        $this->stream->append($message);
    }
}

class Printer
{
    protected $replace;
    protected $level = 0;
    protected $indent_char = "\t";
    protected $stream;

    protected $next;

    public function __construct($stream, $replace)
    {
        $this->stream = $stream;
        $this->replace = $replace;
    }

    public function block(Callable $call)
    {
        $this->indent();
        $call($this);
        $this->outdent();
    }

    public function indent()
    {
        $this->level++;
    }

    public function outdent()
    {
        $this->level--;
        if ($this->level < 0) {
            throw new RuntimeException("too low indent level.");
        }
    }

    public function put($message/* $args */)
    {
        $args = func_get_args();
        array_shift($args);

        $key = "";
        $value = "";
        $tmp = array();
        if (count($args)) {
            if (count($args) % 2 != 0) {
                throw new InvalidArgumentException("parameter doesn't match");
            }

            for ($i = 0; $i < count($args); $i++) {
                if ($i % 2 == 0) {
                    $key = $args[$i];
                } else {
                    $value = $args[$i];

                    $tmp[$key] = $value;
                    unset($key);
                    unset($value);
                }
            }
            foreach ($tmp as $key => $value) {
                $message = str_replace(sprintf("%s%s%s", $this->replace, $key, $this->replace), $value, $message);
            }
        }

        if ($this->next) {
            $this->stream->write(str_repeat($this->indent_char, $this->level));
        }

        if (preg_match('/\n$/m', $message)) {
            $this->next = true;
        } else {
            $this->next = false;
        }
        $this->stream->write($message);
    }
}
class Fashion
{
/*
    {{{ proto resource git_revparse_single(repo, spec)
    PHP_FUNCTION(git_revparse_single)
    {
    zval *repo;
    php_git2_t *_repo;
    char *spec = {0};
    int spec_len;

        php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_revparse_single not implemented yet");
        return;

        if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
            "rs", &repo, &spec, &spec_len) == FAILURE) {
        return;
    }
        ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
    }
 */
    public function shouldResource(Arg $arg)
    {
        static $types;
        if (!$types) {
            $types = array(
                "git_repository",
                "git_commit",
                "git_tree",
                "git_tree_entry", // really?
                "git_blob",
                "git_revwalk",
                "git_treebuilder",
                "git_reference",
                "git_config",
                "git_object",
                "git_index",
                "git_odb",
                "git_refdb",
                "git_status_list",
                "git_branch_iterator",
                "git_tag",
                "git_cred",
                "git_transport",
                "git_remote",
                "git_merge_head",
                "git_merge_result",
                "git_pathspec",
                "git_pathspec_match_list",
                "git_diff",
                "git_patch",
                "git_diff_hunk",
                "git_filter_list",
                "git_buf",
                "git_filter_source",
                "git_diff_line",
            );
        }

        if (in_array($arg->getType(), $types)) {
            return true;
        } else {
            return false;
        }
    }

    public function getReturnType(Func $f)
    {
        if ($f->isResourceCreator()) {
            return "resource";
        } else {
            if (preg_match("/(int|size_t)/", $f->getReturnType())) {
                return "long";
            } else if (preg_match("/git_signature/", $f->getReturnType())) {
                return "array";
            } else if (preg_match("/git/", $f->getReturnType())) {
                return "resource";
            } else if (preg_match("/void/", $f->getReturnType())) {
                return "void";
            } else if (preg_match("/char/", $f->getReturnType())) {
                return "string";
            } else {
                error_log(sprintf("%s does not support yet", $f->getReturnType()));
            }
        }
    }

    public function generateProto(Printer $printer, Func $f)
    {
        $printer->put("/* {{{ proto `return_type` `function`",
            "return_type", $this->getReturnType($f),
            "function", $f->getName()
        );
        $printer->put("(");
        $cnt = count($f->getArguments());
        $i = 0;

        foreach ($f->getArguments() as $arg) {
            /** @var Arg $arg */
            if ($i == 0 && $f->isResourceCreator()) {
                $i++;
                continue;
            }
            if ($arg->shouldWrite()) {
                $i++;
                continue;
            }

            if ($this->shouldResource($arg)) {
                $printer->put("resource");
            } else {
                if (preg_match("/char/", $arg->getType())) {
                    $printer->put("string");
                } else if (preg_match("/(int|size_t)/", $arg->getType())) {
                    $printer->put("long");
                } else if (preg_match("/(git_oid)/", $arg->getType())) {
                    $printer->put("string");
                } else if (preg_match("/(git_signature)/", $arg->getType())) {
                    $printer->put("array");
                } else if (preg_match("/(git_strarray)/", $arg->getType())) {
                    $printer->put("array");
                } else {
                    error_log(sprintf("# unknown type (%s)", $arg->getType()));
                }
            }
            $printer->put(" ");

            // variable name
            $printer->put("\$`arg`", "arg", $arg->getName());
            if ($i +1 < $cnt) {
                $printer->put(", ");
            }
            $i++;
        }
        $printer->put(")\n");
        $printer->put(" */\n");
    }

    public function isPtr(Arg $arg)
    {
        if (preg_match("/zval/", $arg->getZendType())) {
            return "*";
        } else {
            if (preg_match("/char/", $arg->getZendType())) {
                return "*";
            } else {
                return "";
            }
        }
    }

    public function generateDeclarations(Printer $printer, Func $f)
    {
        if ($f->isResourceCreator()) {
            $printer->put("php_git2_t *result = NULL;\n");
        } else if ($f->isArrayCreator()) {
            $printer->put("`type` *result = NULL;\n", "type", $f->getReturnType());
            if (preg_match("/git_signature/", $f->getReturnType())) {
                $printer->put("zval *__result = NULL;\n");
            }
        } else if ($f->isLongCreator()) {
            $printer->put("`type` result = 0;\n", "type", $f->getReturnType());
        } else if ($f->isStringCreator()) {
            $printer->put("`type` *result = NULL;\n", "type", $f->getReturnType());
        }

        $i = 0;
        $cnt = count($f->getArguments());
        foreach ($f->getArguments() as $arg) {
            /** @var Arg $arg */
            if ($i == 0  && $f->isResourceCreator()) {
                $printer->put("`type` `ptr``name` = NULL;\n",
                    "type", $arg->getType(),
                    "ptr", $arg->getPtr(),
                    "name", $arg->getName()
                );
                $i++;
                continue;
            }
            if ($arg->shouldWrite()) {
                $printer->put("`type` `ptr``name` = NULL;\n",
                    "type", $arg->getType(),
                    "ptr", $arg->getPtr(),
                    "name", $arg->getName()
                );
            } else {
                /** @var Arg $arg */
                $printer->put("`type` `ptr``name` = `value`;\n",
                    "type", $arg->getZendType(),
                    "ptr", $this->isPtr($arg),
                    "name", $arg->getName(),
                    "value", $arg->getDefaultValue()
                );
                if ($this->shouldResource($arg)) {
                    $printer->put("`type` *_`name` = NULL;\n",
                        "type", "php_git2_t",
                        "name", $arg->getName()
                    );
                }

                if (preg_match("/char/", $arg->getZendType())) {
                    $printer->put("int `name`_len = 0;\n",
                        "name", $arg->getName());
                }
            }

            if ($arg->getType() == "git_oid") {
                $printer->put("git_oid __`name`;\n", "name", $arg->getName());
            }

            $i++;
        }
        if ($f->getReturnType() == "int") {
            $printer->put("`type` error = 0;\n", "type", $f->getReturnType());
        }
        if (preg_match("/git_oid/", $f->getReturnType())) {
            $printer->put("char __result[GIT2_OID_HEXSIZE] = {0};\n");
        }
        if (preg_match("/_owner$/", $f->getName())) {
            $printer->put("php_git2_t *__result = NULL;\n");
        }
    }

    public function generateParse(Printer $printer, Func $f)
    {
        $printer->put("if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,\n");
        $printer->block(function(Printer $printer) use ($f) {
            $i = 0;
            $cnt = count($f->getArguments());
            $printer->put('"');
            foreach ($f->getArguments() as $arg) {
                /** @var Arg $arg */
                if ($i == 0 && $f->isResourceCreator()) {
                    $i++;
                    continue;
                }
                if ($arg->shouldWrite()) {
                    $i++;
                    continue;
                }

                if (preg_match("/char/", $arg->getZendType())) {
                    $printer->put("s");
                } else if (preg_match("/long/", $arg->getZendType())) {
                    $printer->put("l");
                } else if (preg_match("/git_signature/", $arg->getType())) {
                    $printer->put("a");
                } else if ($this->shouldResource($arg)) {
                    $printer->put("r");
                } else {
                    $printer->put("<{$arg->getType()}>");
                }
            }
            $printer->put('", ');

            $i = 0;
            foreach ($f->getArguments() as $arg) {
                /** @var Arg $arg */
                if ($i == 0 && $f->isResourceCreator()) {
                    $i++;
                    continue;
                }
                if ($arg->shouldWrite()) {
                    $i++;
                    continue;
                }

                $printer->put("&`name`", "name", $arg->getName());
                if (preg_match("/char/", $arg->getZendType())) {
                    $printer->put(", ");
                    $printer->put("&`name`_len", "name", $arg->getName());
                }
                if ($i+1 < $cnt) {
                    $printer->put(", ");
                }
                $i++;
            }

            $printer->put(") == FAILURE) {\n");
            $printer->put("return;\n");
        });
        $printer->put("}\n");
    }

    public function generateFetchResourceIfNeeded(Printer $printer, Func $f)
    {
        $i = 0;
        foreach ($f->getArguments() as $arg) {
            if ($f->isResourceCreator() && $i == 0) {
                $i++;
                continue;
            }

            if ($this->shouldResource($arg) && !$arg->shouldWrite()) {
                $printer->put("ZEND_FETCH_RESOURCE(_`container`, php_git2_t*, &`value`, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);\n",
                    "container", $arg->getName(),
                    "value", $arg->getName()
                );
            }
            $i++;
        }
    }

        public function generateOidTranslation(Printer $printer, Func $f)
        {
            foreach ($f->getArguments() as $arg) {
                /** @var Arg $arg */
                if ($arg->getType() == "git_oid") {
                    $printer->put("if (git_oid_fromstrn(&__`name`, `name`, `name`_len)) {\n",
                        "name", $arg->getName()
                    );
                    $printer->block(function(Printer $printer) use($arg) {
                        $printer->put("RETURN_FALSE;\n");
                    });
                    $printer->put("}\n");
                    $arg->setName("__" . $arg->getName());
                }
            }
        }

    public function generateFunctionCall(Printer $printer, Func $f)
    {
        $this->generateOidTranslation($printer, $f);
        if ($f->getReturnType() == "int" && $f->isResourceCreator()) {
            $printer->put("error = `function`",
                "function", $f->getName()
            );
            $printer->put("(");

            $i = 0;
            $cnt = count($f->getArguments());
            foreach ($f->getArguments() as $arg) {
                /** @var Arg $arg */
                if ($i == 0 && $f->isResourceCreator()) {
                    $printer->put("&");
                }

                if ($i != 0) {
                    if ($this->shouldResource($arg) && !$arg->shouldWrite()) {
                        $printer->put("PHP_GIT2_V(_`name`, `type`)",
                            "name", $arg->getName(),
                            "type", $this->getNormarizedTypeName($arg)
                        );
                    } else if ($arg->shouldWrite()) {
                        $printer->put("&`name`", "name", $arg->getName());
                    } else {
                        $printer->put("`name`", "name", $arg->getName());
                    }
                } else {
                    $printer->put("`name`", "name", $arg->getName());
                }

                if ($i + 1 < $cnt) {
                    $printer->put(", ");
                }
                $i++;
            }

            $printer->put(");");
            $printer->put("\n");
        } else if ($f->isResourceCreator()) {
            $printer->put("`retval` = `function`",
                "retval", "result",
                "function", $f->getName()
            );
            $printer->put("(");


            $i = 0;
            $cnt = count($f->getArguments());
            foreach ($f->getArguments() as $arg) {
                /** @var Arg $arg */
                if ($i == 0 && $f->isResourceCreator()) {
                    $printer->put("&");
                }

                if ($i != 0) {
                    if ($this->shouldResource($arg) && !$arg->shouldWrite()) {
                        $printer->put("PHP_GIT2_V(_`name`, `type`)",
                            "name", $arg->getName(),
                            "type", $this->getNormarizedTypeName($arg)
                        );
                    } else if ($arg->shouldWrite()) {
                        $printer->put("&`name`", "name", $arg->getName());
                    } else {
                        $printer->put("`name`", "name", $arg->getName());
                    }
                } else {
                    $printer->put("`name`", "name", $arg->getName());
                }

                if ($i + 1 < $cnt) {
                    $printer->put(", ");
                }
                $i++;
            }
            $printer->put(");\n");
        } else if ($f->isArrayCreator()) {
            $printer->put("result = `function`",
                "function", $f->getName()
            );
            $printer->put("(");

            $i = 0;
            $cnt = count($f->getArguments());
            foreach ($f->getArguments() as $arg) {
                /** @var Arg $arg */

                if ($this->shouldResource($arg) && !$arg->shouldWrite()) {
                    $printer->put("PHP_GIT2_V(_`name`, `type`)",
                        "name", $arg->getName(),
                        "type", $this->getNormarizedTypeName($arg)
                    );
                } else if ($arg->shouldWrite()) {
                    $printer->put("&`name`", "name", $arg->getName());
                } else {
                    $printer->put("`name`", "name", $arg->getName());
                }

                if ($i + 1 < $cnt) {
                    $printer->put(", ");
                }
                $i++;
            }

            $printer->put(");\n");
            if (preg_match("/git_oid/", $f->getReturnType())) {
                $printer->put("git_oid_fmt(__result, `name`);\n", "name", "result");
                $printer->put("RETURN_STRING(__result, 1);\n");
            } else if (preg_match("/_owner$/", $f->getName())) {
                $this->generateMakeResourceIfNeeded($printer, $f, "__result", 1);
            } else if (preg_match("/_type/", $f->getName())) {
                $printer->put("RETURN_LONG(`name`);\n", "name", "result");
            } else if (preg_match("/git_signature/", $f->getReturnType())) {
                $printer->put("php_git2_signature_to_array(result, &__result TSRMLS_CC);\n");
                $printer->put("RETURN_ZVAL(__result, 0, 1);\n");
            } else {
                $printer->put("/* TODO(chobie): implement this */\n");
            }
        } else if ($f->isLongCreator()) {
            $printer->put("result = `function`",
                "function", $f->getName()
            );
            $printer->put("(");
            $i = 0;
            $cnt = count($f->getArguments());
            foreach ($f->getArguments() as $arg) {
                /** @var Arg $arg */

                if ($this->shouldResource($arg) && !$arg->shouldWrite()) {
                    $printer->put("PHP_GIT2_V(_`name`, `type`)",
                        "name", $arg->getName(),
                        "type", $this->getNormarizedTypeName($arg)
                    );
                } else if ($arg->shouldWrite()) {
                    $printer->put("&`name`", "name", $arg->getName());
                } else {
                    $printer->put("`name`", "name", $arg->getName());
                }

                if ($i + 1 < $cnt) {
                    $printer->put(", ");
                }
                $i++;
            }
            $printer->put(");\n");

            if (preg_match("/_is_/", $f->getName())) {
                $printer->put("RETURN_BOOL(`name`);\n", "name", "result");
            } else {
                $printer->put("RETURN_LONG(`name`);\n", "name", "result");
            }
        } else if ($f->isSavior()) {

            $first = $f->first();
            $printer->put("if (_`name`->should_free_v) {\n",
                "name", $first->getName()
            );
            $printer->block(function(Printer $printer) use ($f) {
                $printer->put("`function`",
                    "function", $f->getName()
                );
                $printer->put("(");
                $i = 0;
                $cnt = count($f->getArguments());
                foreach ($f->getArguments() as $arg) {
                    /** @var Arg $arg */

                    if ($this->shouldResource($arg) && !$arg->shouldWrite()) {
                        $printer->put("PHP_GIT2_V(_`name`, `type`)",
                            "name", $arg->getName(),
                            "type", $this->getNormarizedTypeName($arg)
                        );
                    } else if ($arg->shouldWrite()) {
                        $printer->put("&`name`", "name", $arg->getName());
                    } else {
                        $printer->put("`name`", "name", $arg->getName());
                    }

                    if ($i + 1 < $cnt) {
                        $printer->put(", ");
                    }
                    $i++;
                }
                $printer->put(");\n");

            });
            $printer->put("};\n");

            $printer->put("zval_ptr_dtor(&`name`);\n", "name", $first->getName());
        } else if ($f->isStringCreator()) {
            $printer->put("result = `function`",
                "function", $f->getName()
            );
            $printer->put("(");
            $i = 0;
            $cnt = count($f->getArguments());
            foreach ($f->getArguments() as $arg) {
                /** @var Arg $arg */

                if ($this->shouldResource($arg) && !$arg->shouldWrite()) {
                    $printer->put("PHP_GIT2_V(_`name`, `type`)",
                        "name", $arg->getName(),
                        "type", $this->getNormarizedTypeName($arg)
                    );
                } else if ($arg->shouldWrite()) {
                    $printer->put("&`name`", "name", $arg->getName());
                } else {
                    $printer->put("`name`", "name", $arg->getName());
                }

                if ($i + 1 < $cnt) {
                    $printer->put(", ");
                }
                $i++;
            }
            $printer->put(");\n");
            $printer->put("RETURN_STRING(`name`, 1);\n", "name", "result");
        } else if ($f->isVoidCreator()) {
            $printer->put("`function`",
                "function", $f->getName()
            );
            $printer->put("(");
            $i = 0;
            $cnt = count($f->getArguments());
            foreach ($f->getArguments() as $arg) {
                /** @var Arg $arg */

                if ($this->shouldResource($arg) && !$arg->shouldWrite()) {
                    $printer->put("PHP_GIT2_V(_`name`, `type`)",
                        "name", $arg->getName(),
                        "type", $this->getNormarizedTypeName($arg)
                    );
                } else if ($arg->shouldWrite()) {
                    $printer->put("&`name`", "name", $arg->getName());
                } else {
                    $printer->put("`name`", "name", $arg->getName());
                }

                if ($i + 1 < $cnt) {
                    $printer->put(", ");
                }
                $i++;
            }
            $printer->put(");\n");
        } else {
            error_log(sprintf("# %s not supported (call function)", $f->getName()));
        }
    }

    public function generateCheckStatementIfNeeded(Printer $printer, Func $f)
    {
        if ($f->getReturnType() == "int" && $f->isResourceCreator()) {
            $printer->put('if (php_git2_check_error(error, "`func`" TSRMLS_CC)) {',
                "func", $f->getName()
            );
            $printer->put("\n");
            $printer->block(function (Printer $printer) use ($f) {
                $printer->put("RETURN_FALSE;\n");
            });
            $printer->put("}\n");
        }
    }

    public function getNormarizedTypeName(Arg $arg)
    {
        $name = $arg->getType();
        return preg_replace("/^git_/", "", $name);
    }

    public function generateMakeResourceIfNeeded(Printer $printer, Func $f, $name = "result", $force = 0)
    {
        if ($f->isResourceCreator() || $force) {
            $arg = $f->first();
            $printer->put("PHP_GIT2_MAKE_RESOURCE(`name`);\n", "name", $name);
            $printer->put("PHP_GIT2_V(`name`, `type`) = `variable`;\n",
                "name", $name,
                "type", $this->getNormarizedTypeName($arg),
                "variable", $arg->getName()
            );
            $printer->put("`name`->type = PHP_GIT2_TYPE_`type`;\n",
                "name", $name,
                "type", strtoupper($this->getNormarizedTypeName($arg))
            );
            $printer->put("`name`->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);\n", "name", $name);
            $printer->put("`name`->should_free_v = 0;\n", "name", $name);
            $printer->put("ZVAL_RESOURCE(return_value, `name`->resource_id);\n", "name", $name);
        }
    }

    public function out(Func $f)
    {
        $stream = new StringStream();
        $out = new ZeroCopyOutputStream($stream);
        $printer = new Printer($out, "`");

        $this->generateProto($printer, $f);
        $printer->put("PHP_FUNCTION(`function`)\n",
            "function", $f->getName());
        $printer->put("{\n");
        $printer->block(function(Printer $printer) use ($f) {
            $this->generateDeclarations($printer, $f);
            $printer->put("\n");
            $this->generateParse($printer, $f);
            $printer->put("\n");

            $this->generateFetchResourceIfNeeded($printer, $f);
            $this->generateFunctionCall($printer, $f);
            $this->generateCheckStatementIfNeeded($printer, $f);
            $this->generateMakeResourceIfNeeded($printer, $f);
        });
        $printer->put("}\n");
        $printer->put("/* }}} */\n");
        $printer->put("\n");


        return $stream->__toString();
    }
}

$data = file_get_contents($_SERVER['argv'][1]);
$table = array();
if (preg_match_all("/GIT_EXTERN\((.+?)\)\s*([a-zA-Z0-9_-]+)\((.+?)\);/s", $data, $match)) {
    $cnt = count($match[0]);

    for ($i = 0; $i < $cnt; $i++) {
        $func = new Func($match[2][$i], $match[1][$i]);
        $args = explode(",", $match[3][$i]);

        foreach ($args as $arg) {
            $arg = trim($arg);
            $pos = strrpos($arg, " ");
            $key = trim(substr($arg, $pos));
            $type = trim(substr($arg, 0, $pos));
            $func->addArgument(new Arg($type, $key));
        }
        $table[$func->getName()] = $func;
    }
}

$printer = new Fashion();
echo $printer->out($table[$_SERVER['argv'][2]]);

