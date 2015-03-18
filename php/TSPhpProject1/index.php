<!DOCTYPE html>
<!--
To change this license header, choose License Headers in Project Properties.
To change this template file, choose Tools | Templates
and open the template in the editor.
-->
<html>
    <head>
        <meta charset="UTF-8">
        <title></title>
    </head>
    <body>
        <?php
        class StrictCoordinateClass {
            private $arr = array('x' => NULL, 'Y' => NULL);
            
            function __get($property) {
                if(array_key_exists($property, $this->arr)) {
                    return $this->arr[$property];
                } else {
                    print "Error: cannot read a property other than x & y\n";
                }
            }
            
            function __set($property, $value) {
                if(array_key_exists($property, $this->arr)) {
                    $this->arr[$property] = $value;
                } else {
                    print "Error: cannot write a property other than x & y\n";
                }
            }
        }
        
        $obj = new StrictCoordinateClass();
        $obj->x = 1;
        print $obj->x;
        print "\n";
        
        $obj->n = 2;
        print $obj->n;
        ?>
    </body>
</html>
