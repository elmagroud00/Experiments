#!/usr/bin/php

<?php
$str = '0.87395100 1078006447';
$time = preg_replace('@^(.*)\s+(.*)$@e', '\\2 + \\1', $str);
echo "\n" . 'time=' . $time . "\n";
?>
