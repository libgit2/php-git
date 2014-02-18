<?php
$target = $_SERVER['argv'][1];

// clang warning based unused variables fixer.
//
// make 2> error.log
// grep "unused variables" error.log > error2.log
// php fixer.php <path.c>
$data = file_get_contents("error2.log");
$result = array();
foreach (explode("\n", $data) as $line) {
    if (preg_match("!(.+?):(\d+):(\d+): warning: unused variable '(.+?)'!", $line, $match)) {
        $filename = basename($match[1]);
        $line = $match[2];
        $columns = $match[3];
        $name = $match[4];

        if ($filename == $target) {
            $result[$filename][] = array(
                "line" => $line,
                "columns" => $columns,
                "name" => $name,
            );
        }
    }
}

//var_dump($result);
$file = file_get_contents($target);
$lines = explode("\n", $file);
if (!isset($result[$target])) {
    echo "nothing";
    exit;
}
foreach ($result[$target] as $value) {
    //echo $lines[$value['line']-1] . PHP_EOL;

    $line = $lines[$value['line']-1];
    $l = parseLine($line);
    $l->remove($value['name']);
    $hhh = $l->toLine();
    $lines[$value['line']-1] = $hhh;
}
$buffer = "";
for ($i = 0; $i < count($lines); $i++) {
    $line = $lines[$i];
    if ($line == "==========REMOVED==========") {
        continue;
    }
    $buffer .= $line;
    if ($i + 1 < count($lines)) {
        $buffer .= "\n";
    }
}
//echo $buffer;exit;
file_put_contents($target, $buffer);

function parseLine($line)
{
    for ($i = 0; $i < strlen($line); $i++) {
        if ($line[$i] == "\t") {
            continue;
        } else {
            break;
        }
    }

    $l = new Line($i);
    $arg = substr($line, $i);
    $type = null;
    $args = array();
    $tmp = null;
    $base = null;
    foreach (explode(",", $arg) as $arg2) {
        $tokens = preg_split("/(\s+|;)/", $arg2);

        $cnt = count($tokens);
        $state = 0;
        for ($i = 0; $i < $cnt; $i++) {
            if ($state == 0) {
                if (empty($tokens[$i])) {
                    continue;
                }
                if (!$type) {
                    if ($tokens[$i] != "const") {
                        $type = $tokens[$i];
                        $state = 1;
                        if (!$tmp) {
                            $tmp = new Variable();
                            $tmp->setType($tokens[$i]);
                            $base = clone $tmp;
                        }
                    } else {
                        $tmp = new Variable();
                        $tmp->is_const = 1;
                        $tmp->setType($tokens[$i+1]);
                        $i++;
                        $state = 1;
                        $base = clone $tmp;
                    }
                } else {
                    $state = 1;
                    $tmp = clone $base;
                    $tmp->setName($tokens[$i]);
                }
            } else if ($state == 1) {
                if ($tokens[$i] == "=") {
                    $state = 2;
                } else {
                    $tmp->setName($tokens[$i]);
                }
            } else if ($state == 2) {
                $tmp->setDefault($tokens[$i]);
                $l->add($tmp);
                unset($tmp);
                $state = 0;
            }
        }
        if (isset($tmp)) {
            $l->add($tmp);
        }
    }

    return $l;
}

class Line
{
    public $indent;
    public $variables = array();

    public function __construct($indent)
    {
        $this->indent = $indent;
    }

    public function add(Variable $var)
    {
        $this->variables[] = $var;
    }

    public function remove($name)
    {
        foreach ($this->variables as $o => $var) {
            if ($var->name == $name) {
                unset($this->variables[$o]);
            }
        }
    }

    public function isEmpty()
    {
        if (count($this->variables)) {
            return false;
        } else {
            return true;
        }
    }

    public function toLine()
    {
        $type = null;
        $buffer = str_repeat("\t", $this->indent);
        $values = array();
        foreach ($this->variables as $var) {
            if (!$type) {
                if ($var->getNameWithPtr() === "") {
                    continue;
                }

                $type = $var->type;
                if ($var->is_const) {
                    $buffer .= "const ";
                }
                $buffer .= sprintf("%s ", $var->type);

                if ($var->default !== NULL) {
                    $values[] = sprintf("%s = %s", $var->getNameWithPtr(), $var->default);
                } else {
                    $values[] = $var->getNameWithPtr();
                }
            } else {
                if ($var->getNameWithPtr() === "") {
                    continue;
                }


                if ($var->default !== NULL) {
                    $values[] = sprintf("%s = %s", $var->getNameWithPtr(), $var->default);
                } else {
                    $values[] = $var->getNameWithPtr();
                }
            }
        }

        if (count($values)) {
            $buffer .= join(", ", $values);
        } else {
            return "==========REMOVED==========";
        }
        if (strlen($buffer) > $this->indent) {
            $buffer .= ";";
        }

        $check = trim($buffer, " \t");
        if (!$check) {
            return "==========REMOVED==========";
        }

        return $buffer;
    }
}

class Variable
{
    public $name;
    public $type;
    public $default;
    public $is_static;
    public $is_const;
    public $ptr = 0;

    public function __construct()
    {
    }

    public function setType($type)
    {
        $this->type = $type;
    }

    public function setName($name)
    {
        $ptr = 0;
        for ($i =0; $i < strlen($name); $i++) {
            if ($name[$i] == '*') {
                $ptr++;
            }
        }

        $this->name = substr($name, $ptr);
        if ($ptr) {
            $this->ptr = $ptr;
        }
    }

    public function setPtr($ptr)
    {
        $this->ptr = $ptr;
    }

    public function setDefault($default)
    {
        $this->default = $default;
    }

    public function getNameWithPtr()
    {
        if ($this->name) {
            return str_repeat("*", $this->ptr) . $this->name;
        } else {
            return "";
        }
    }
}
