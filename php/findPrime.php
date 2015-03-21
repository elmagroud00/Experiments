#!/usr/bin/php

<?php
$ss = 2;
$max = 1000;
$arr = array();
echo $max . " all primes: ";

while($ss < $max) {
    $boo = false;
    foreach($arr as $value) {
        if($ss % $value == 0) {
            $boo = true;
            break;
        }
    }
    if(!$boo) {
        echo $ss . " ";
        $arr[count($arr)] = $ss;
    }
    $ss++;
}

?>
