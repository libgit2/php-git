<?php

$ex = new ReflectionExtension("git2");
$result = array();
foreach ($ex->getFunctions() as $func) {
    /** @var ReflectionFunction $func */

    $name = $func->getName();
    $result[$name] = array();
    foreach ($func->getParameters() as $param) {
        /** @var ReflectionParameter $param */
        $result[$name][] = '$' . $param->getName();
    }
}

echo "<?php\n";
foreach ($result as $func => $params) {
    printf("function %s(%s){}\n", $func, join(", ", $params));
}
