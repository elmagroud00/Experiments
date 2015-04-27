<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
namespace com\getinstance\util;

require_once 'global.php';

class Lister {
    public static function hellworld() {
        print "hello from " . __NAMESPACE__ . "\n";
    }
}
Lister::hellworld();
\Lister::helloword();