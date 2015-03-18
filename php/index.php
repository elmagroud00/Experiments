<?php
class Animal {
    function makeSound() {
        print "Error";
    }
}

class Cat extends Animal {
    function makeSound() {
        print "miau";
    }
}

function printTheRightSound($obj) {
    if($obj instanceof Animal) {
        $obj->makeSound();
    } else {
        print "Error";
    }
}
php?>

<html>
<head>
<title>Hello, PHP</title>
</head>

<body>

    <H1>This is my first PHP project</H1>
    <?php
        printTheRightSound(new Cat());
    php?>
    
</body>
</html>