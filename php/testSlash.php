#!/usr/bin/php

<?php
$str = "select * from tb_book where bookname='PHP Book'";
echo $str . "\n";
$a = addslashes($str);
echo $a . "\n";
$b = stripslashes($a);
echo $b . "\n";
?>
