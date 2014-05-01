#!/bin/bash

var="a.so"
echo $var
echo $0

echo `pidof $0`

f="/tmp/test`date +%Y%m%d%H%M%S`"
echo $f
