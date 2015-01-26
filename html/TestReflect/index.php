<!DOCTYPE html>
<!--
To change this license header, choose License Headers in Project Properties.
To change this template file, choose Tools | Templates
and open the template in the editor.
-->
<html>
    <head>
        <meta charset="UTF-8">
        <title>Test Reflect</title>
    </head>
    <body>
        <?php

        //error_reporting(null);

        class ClassOne {

            function callClassOne() {
                print "In Class One\n";
            }

        }

        class ClassTwo {

            function callClassTwo() {
                print "In Class Two\n";
            }

        }

        class ClassOneDelegator {

            private $targets;

            function __construct() {
                $this->targets[] = new ClassOne();
            }

            function addObject($obj) {
                $this->targets[] = $obj;
            }

            function __call($name, $arguments) {
                foreach ($this->targets as $obj) {
                    $r = new ReflectionClass($obj);
                    try {
                        $method = $r->getMethod($name);
                    } catch (ReflectionException $e) {
                        continue;
                    }

                    if ($method->isPublic() && !$method->isAbstract()) {
                        return $method->invoke($obj, $arguments);
                    }
                }
            }

        }

        $obj = new ClassOneDelegator();
        $obj->addObject(new ClassTwo());
        //$obj->callClassOne();
        $obj->callClassTwo();
        ?>

    </body>
</html>
