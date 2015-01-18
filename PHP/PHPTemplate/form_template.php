<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
$bindings['DESTINATION'] = $_SERVER['PHP_SELF'];

$name = $_GET['name'];

if (!empty($name)) {
    //do something with the supplied values
    $template = "thankyou.template";
    $bindings['NAME'] = $name;
} else {
    $template = "input.template";
}

echo fillTemplate($template, $bindings);

function fillTemplate($name, $value = array(), $unhandled = "delete") {
    $templateFile = $_SERVER['DOCUMENT_ROOT'] . '/templates/' . $name;

    if ($file = fopen($templateFile, 'r')) {

        $template = fread($file, filesize($template));
        fclose($file);
    }

    $keys = array_keys($values);
    foreach ($keys as $key) {
        // look for and replace the key everywhere it occurs in the template
        $template = str_replace("{{$key}}", $values[$key], $template);
    }

    if ($unhandled == 'delete') {
        // remove remaining keys
        $template = preg_replace('/{[^ }]*}/i', '', $template);
    } else if ($unhandled == 'comment') {
        // comment remaing keys
        $template = preg_replace('/{([^ }]*)}/i', '<!-- \\1 undefined-->', $template);
    }
    
    return $template;
}
