<?php

$extName = "Git";


$extension = new ReflectionExtension($extName);
$classes = $extension->getClassNames();

foreach($classes as $class){
    $ref = new ReflectionClass($class);
    
    $methods = $ref->getMethods();
    $namespace = array();

    if(strpos($ref->getName(),"\\") !== false) {
        $tmp = explode("\\",$ref->getName());
        $className = array_pop($tmp);
        $name      = strtolower($className);
        $namespace = $tmp;
        $nameSpace = join("\\\\",$namespace) . "\\\\";
        $nameSpace2 = join("\\",$namespace) . "\\";
    } else {
      $className = $ref->getName();
      $name      = strtolower($className);
    }

    //if(!is_dir("class/" . $name)){
        @mkdir("class/" . $name,0766);
        file_put_contents("class/" . $name . "/" . "index.rst",(<<<EOS
{$nameSpace}{$className}
===========================


.. toctree::
   :maxdepth: 1
   :glob:

   *

EOS
        ));
    //}
    
    foreach($methods as $method){
        $methodName = $method->getName();
        $method_name = strtolower(preg_replace('/([a-z])([A-Z])/', "$1_$2", $methodName));
        
        $filename = "class/" .$name . "/" . $method_name . ".rst";
        //if(!is_file($filename)){
        $definition = genMethodDefinition($className, $method, $nameSpace);
        $parameters = genParameterDocs($method);
            file_put_contents($filename,(<<<EOS
.. index::
   single: {$methodName} ({$nameSpace2}{$className} method)


{$nameSpace}{$className}::{$methodName}
===========================================================

Description
***********************************************************

{$definition}

Parameters
***********************************************************

{$parameters}

Return Values
***********************************************************

Examples
***********************************************************

See Also
***********************************************************
EOS
            ));
       // }
    }

}

function genMethodDefinition($className, $ref, $namespace)
{
    $result = "";
    if($ref->isPublic()){
        $result .= "public ";
    }else if($ref->isProtected()){
        $result .= "protected ";
    }
    if($ref->isStatic()){
        $result .= "static ";
    }
    $result .= "**" . $namespace . $className;
    $result .= "::";
    $result .= $ref->getName() . "**";
    $result .= " (";
    
    $params = $ref->getParameters();
    $p = array();
    foreach($params as $param){
        $tmp = "";
        if($param->isOptional()){
            $tmp .= " [";
        }
        
        if($param->isArray()) {
            $tmp .= " array ";
        }
        
        $tmp .= "*\$" . $param->getName() . "*";

        if($param->isOptional()){
            $tmp .= "]";
        }
        $p[] = $tmp;
    }
    $result .= join(", ", $p);
    $result .= ")";

    return $result . PHP_EOL;
}

function genParameterDocs($ref)
{
    $params = $ref->getParameters();
    $result = array();
    foreach($params as $param){
        $name = $param->getName();
        
        $result[] = sprintf("*%s*\n  fill them out later\n",$name);
    }
    
    return join("\n",$result);
    
}