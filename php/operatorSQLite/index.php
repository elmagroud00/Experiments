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
                require_once "OS/Guess.php";
                $os = new OS_Guess;
                print "OS signature: " . $os->getSignature() . "\n";
                if($os->matchSignature("linux-*-i386")) {
                    print "Linux";
                }
                
                require_once 'PEAR.php';
                
                if(PEAR::isError($e = lucky())) {
                    die($e->getMessage() . "\n");
                }
                
                print "You were lucky, this time\n";
                
                function lucky() {
                    if(rand(0, 1) == 0) {
                        return PEAR::throwError('tough luck!');
                    }
                }
                
                class Luck extends PEAR {
                    function testLuck() {
                        if(rand(0, 1) == 0) {
                            return $this->throwError('tough luck!');
                        }
                        return "Lucky!";
                    }
                }
                print "<br/>";
                $luck = new Luck;
                $test = $luck->testLuck();
                if(PEAR::isError($test)) {
                    die($test->getMessage() . "\n");
                }
                print "$test \n";
        ?>
    </body>
</html>
