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
        
        class NumberSquared implements Iterator {
            public function __construct($start, $end) {
                $this->start = $start;
                $this->end = $end;
            }
            
            public function rewind() {
                $this->cur = $this->start;
            }
            
            public function key() {
                return $this->cur;
            }
            
            public function current() {
                return pow($this->cur, 2);
            }
            
            public function next() {
                $this->cur++;
            }
            
            public function valid() {
                return $this->cur <= $this->end;
            }
            
            private $start, $end;
            private $cur;
        }
        
  
        
        ?>
        <h1>Test Class NumberSquared</h1>
        <?php
        $obj = new NumberSquared(3, 7);
        
        foreach($obj as $key=>$value) {
            print "\nThe square of $key is $value\n";
        }
        ?>
        
        <?php
        class NumberSquared2 implements IteratorAggregate {
            public function __construct($start, $end) {
                $this->start = $start;
                $this->end = $end;
            }
            public function getIterator() {
                return new NumberSquared2Iterator($this);
            }
            public function getStart() {
                return $this->start;
            }
            public function getEnd() {
                return $this->end;
            }
            private $start, $end;
        }
        
        class NumberSquared2Iterator implements Iterator {
            public function __construct($obj) {
                $this->obj = $obj;
            }
            public function rewind() {
                $this->cur = $this->obj->getStart();
            }
            public function key() {
                return $this->cur;
            }
            public function current() {
                return pow($this->cur, 2);
            }
            public function next() {
                $this->cur++;
            }
            public function valid() {
                return $this->cur <= $this->obj->getEnd();
            }
            private $cur;
            private $obj;
        }
        ?>
        <h1>NumberSquared2</h1>
        <?php
        $obj = new NumberSquared2(3, 7);
        foreach($obj as $key=>$value) {
            print "The square of $key is $value\n";
        }
        ?>
    </body>
</html>
