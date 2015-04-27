<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
class Preferences {
    private $props = array();
    private static $instance;
    
    public static function getInstance() {
        if(empty(self::$instance)) {
            self::$instance = new Preferences();
        }
        return self::$instance;
    }
    
    private function __construct() {
        
    }
    
    public function setProperty($key, $val) {
        $this->props[$key] = $val;
    }
    
    public function getProperty($key) {
        return $this->props[$key];
    }
}

$pref = Preferences::getInstance();
$pref->setProperty("name", "matt");

unset($pref);

$pref2 = Preferences::getInstance();
print $pref2->getProperty("name") . "\n";
