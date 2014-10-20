<!DOCTYPE html>
<!--
To change this license header, choose License Headers in Project Properties.
To change this template file, choose Tools | Templates
and open the template in the editor.
-->
<html>
    <head>
        <meta charset="UTF-8">
        <title>A Php Test</title>
    </head>
    <body>
        <?php
        interface Loggable {
            function logString();
        }
        
        class Person implements Loggable {
            private $name, $address, $idName, $age;
            
            function __Construct($name) {
                $this->name = $name;
            }
            
            function __toString() {
                return $this->name;
            }
            
            function logString() {
                return "class Person: name = $this->name, ID = $this->idName\n";
            }
        }
        
        class Product implements Loggable {
            private $name, $price, $expiryDate;
            
            function logString() {
                return "class Product: name = $this->name, price = $this->price\n";
            }
        }
        
        function MyLog($obj) {
            if($obj instanceof Loggable) {
                print $obj->logString();
            } else {
                print "Error: Object doesn't support Loggable interface\n";
            }
        }
        
        $person = new Person();
        $product = new Product();
        
        MyLog($person);
        MyLog($product);
        
        $person = new Person("Andi Gutmas");
        print $person;
        ?>
    </body>
</html>
