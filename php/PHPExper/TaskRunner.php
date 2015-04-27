<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
include_once "ReflectUtil.php";

$classname = "Task";

$path = "tasks/{$classname}.php";
try {
    if (!file_exists($path)) {
        throw new Exception("No such file as {$path}");
    }

    require_once $path;
    $qclassname = "tasks\\$classname";
    if (!class_exists($qclassname)) {
        throw new Exception("No such class as $qclassname");
    }
} catch (Exception $e) {
    print_r($e);
}

$myObj = new $qclassname();
$myObj->doSpeak();

//print_r(get_declared_classes());

function classData(ReflectionClass $class) {
    $name = $class->getName();
    print_r("Class name: " . $name);
}

$prod_class = new ReflectionClass("$qclassname");
classData($prod_class);

print ReflectionUtil::getClassSource(new ReflectionClass("$qclassname"));

