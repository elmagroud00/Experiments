<!DOCTYPE html>
<!--
To change this license header, choose License Headers in Project Properties.
To change this template file, choose Tools | Templates
and open the template in the editor.
-->
<html>
    <head>
        <meta charset="UTF-8">
        <title>Test PHP Reg</title>
    </head>
    <body>
        <h2>Test 1</h2>
        <?php
        $patterm = "/^([0-9a-f]{2}:){5}[0-9a-f]{2}$/";
        preg_match($patterm, '00:04:23:7c:5d:01', $matches);
        print_r($matches);
        ?>

        <h2>Test 2</h2>
        <?php
        $raw_document = file_get_contents('http://www.w3.org/TR/CSS21');
        $doc = html_entity_decode($raw_document);
        $count = preg_match_all(
                '/<(?P<email>([a-z]+).?@[a-z0-9]+\.[a-z]{1,6})>/Ui', $doc, $matches2
        );
        var_dump($matches2);
        ?>

        <h2>Test 3</h2>
        <?php
        echo strftime("%c\n");
        echo "<br />";
        echo "\nEST in en_US:\n";
        setLocale(LC_ALL, "en_US");
        putenv("TZ=EST");
        echo strftime("%c\n");
        echo "<br />";
        echo "\nMET in nl_NL:\n";
        setLocale(LC_ALL, "nl_NL");
        putenv("TZ=MET");
        echo strftime("%c\n");
        ?>

        <h2>Test 4</h2>
        <?php
        $input = <<< END
        <p>"this is test" </p> 
END;
        $str = htmlentities($input, ENT_QUOTES);
        $table = get_html_translation_table(HTML_ENTITIES);
        echo $str;
        //var_dump($table);      
        ?>
        <h2>Test 5</h2>
        <?php
        $mailbox = "xxx From: lnmcc@hotmail.com";
        $message = preg_split('/(?=^From)/m', $mailbox);
        print_r($message);
        ?>
        <h2>Test 6</h2>
        <?php
        $input = <<< END
        name = 'Tim O\'Reilly';
END;
        $pattern = <<< END
                '           #opening quote
                (           #begin capturing
                .*?         #the string
                (?<! \\\\)  #skip escaped quotes
                )           #end capturing
                '           #closing quote
END;
        preg_match("($pattern)x", $input, $match);
        echo $match[1];
        ?>

        <h2>Test 7</h2>
        <?php
        $string = <<< END
                13 dogs
                12 rabbits
                8 cows
                1 goat
END;
        preg_match_all('/(\d+) (\S+)/', $string, $m1, PREG_PATTERN_ORDER);
        preg_match_all('/(\d+) (\S+)/', $string, $m2, PREG_SET_ORDER);
        print_r($m1);
        echo "<br />";
        print_r($m2);
        ?>
        <h2>Test 8</h2>
        <?php
        if (getenv('REQUEST_METHOD') == 'POST') {
            $url = $_POST['url'];
        } else {
            $url = $_GET['url'];
        }
        ?>

        <form action="<?php echo $SERVER['PHP_SELF']; ?>" method="POST">
            <p>URL: <input type="text" name="url" value="<?php echo $url ?>" /><br />
                <input type="submit">
        </form>

        <?php
        if ($url) {
            $remote = fopen($url, 'r'); {
                $html = fread($remote, 1048576);
            }
            fclose($remote);

            $urls = '(http|telnet|gopher|file|wais|ftp)';
            $ltrs = '\w';
            $gunk = '/#~:.?+=&%@!\-';
            $punc = '.:?\-';
            $any = "{$ltrs}{$gunk}{$punc}";

            preg_match_all("{
                \b                  #start at word boundary
                {$urls}:            #need resource and a colon
                [{$any}]+?          #followed by one or more of any vaild characters but be conservative 
                (?=                 #and take only what you need the match ends at
                [{$punc}]*          #punctuation
                [^{any}]            #followed by a non-URL charchter
                |                   #or
                \$                  #the end of the string
                )
                }x", $html, $matches);

            printf("I found %d URLs<p>\n", sizeof($matches[0]));

            foreach ($matches[0] as $u) {
                $link = $_SERVER['PHP_SELF'] . '?url=' . urlencode($u);
                echo "<a href=\"{$link}\">{$u}</a><br />\n";
            }
        }
        ?>
        <h2>Test 9</h2>
        <?php
        $name = "wangsijie";
        $person = array('name' => "lnmcc", 'age' => 100);
        extract($person, EXTR_PREFIX_ALL, "person");
        echo "name: {$name}, Person Name: {$person_name}, Person Age: {$person_age}";
        ?>

        <h2>Test 10</h2>
        <?php

        function printRow2($value, $key) {
            print("<tr><td>{$value}</td><td>{$key}</td></tr>\n");
        }

        ;
        $person = array('name' => "Fred", 'age' => 35, 'wife' => "Wilma");
        array_walk($person, printRow2);
        ?>

        <h2>Test11</h2>
        <?php

        function printRow($value, $key, $color) {
            echo "<tr>\n<td bgcolor=\"{$color}\">{$value}</td>";
            echo "<td bgcolor=\"{$color}\">{$key}</td>\n</tr>\n";
        }

        $person = array('name' => "Fred", 'age' => 35, 'wifi' => "Wilma");
        echo "<table border=\"1\">";
        array_walk($person, "printRow", "lightblue");
        echo "</table>";
        ?>

        <h2>Test 12</h2>
        <?php

        function hasRequired($array, $requiredFields) {
            $keys = array_keys($array);
            foreach ($requiredFields as $fieldName) {
                if (!in_array($fieldName, $keys)) {
                    return false;
                }
            }
            return true;
        }

        if ($_POST['submitted']) {
            echo "<p>You";
            echo hasRequired($_POST, array('name', 'email')) ? "did" : "did not";
            echo " hava all the required fields.</p>";
        }
        ?>
        <form action="<?php echo $_SERVER['PHP_SELF']; ?>" method="POST">
            <p>Name: <input type="text" name="name" /> <br />
                Email: <input type="text" name="email" /> <br />
                Age(Optional): <input type="text" name="age" /> </p>

            <p align="left"><input type="submit" value="submit" name="submitted" /></p>
        </form>

        <h2>Test 13</h2>
        <?php

        function isOdd($element) {
            return $element % 2;
        }

        $callback = 'isOdd';
        $numbers = array(9, 23, 24, 27);
        $odd = array_filter($numbers, $callback);
        print_r($odd);
        ?>
        <h2>Test 14</h2>
        <?php
        $callTrace = array();

        function enterFunction($name) {
            global $callTrace;
            $callTrace[] = $name;
            echo "Entering {$name} (stack is now: " . join('->', $callTrace) . ")<br />";
        }

        function exitFunction() {
            echo "Exiting <br />";
            global $callTrace;
            array_pop($callTrace);
        }

        function first() {
            enterFunction("first");
            exitFunction();
        }

        function second() {
            enterFunction("second");
            first();
            exitFunction();
        }

        function third() {
            enterFunction("third");
            second();
            first();
            exitFunction();
        }

        first();
        third();
        ?>
        <h2>Test 15</h2>
        <?php

        trait Logger {

            public function log($logString) {
                $className = __CLASS__;
                echo date("Y-m-d:h:i:s", time()) . ": [{$className}] {$logString} <br />";
            }

        }

        class User {

            use Logger;

            function __construct($name = '') {
                $this->name = $name;
                $this->log("Create user '{$this->name}'");
            }

            function __toString() {
                return $this->name;
            }

        }

        Class UserGroup {

            use Logger;

            private $users = array();

            public function addUser(User $user) {
                if(!$this->includesUser($user)) {
                    $this->users[] = $user;
                    $this->log("Added user '{$user}' to group");
                }
            }

            private function includesUser(User $user) {
                return array_search($user, $this->users, true);
            }
            
            public function showAll() {
                foreach($this->users as $name) {
                    echo "{$name} <br />";
                }
            }
        }
        
        $group = new UserGroup;
        $group->addUser(new User("lnmcc"));
        $group->addUser(new User("wangsijie"));
        $group->showAll();
        ?>
        
        <h2>Test 16</h2>
        <?php
        trait Command1 {
            function run() {
                echo "executing command1 ... <br />";
            }
        }
        
        trait Command2 {
            function run() {
                echo "executing command2 ... <br />";
            }
        }
        
        class TestCommand {
            use Command1, Command2 {
                Command1::run as Command1Run;
                Command2::run insteadof Command1;
            }
        }
        
        $test = new TestCommand();
        $test->run();
        $test->Command1Run();
        ?>
    </body>
</html>
