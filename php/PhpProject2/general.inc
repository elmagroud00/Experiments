<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

function __autoload($class_name) {
    require_once($__SERVER["DOCUMENT_ROOT"] . "/classes/"$class_name);
}