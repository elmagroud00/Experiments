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
        if(getenv('REQUEST_METHOD') == 'POST') {
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
        if($url) {
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
                
                foreach($matches[0] as $u) {
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
        function printRow($value, $key) {
            print("<tr><td>{$value}</td><td>{$key}</td></tr>\n");
        };
        $person = array('name'=>"Fred", 'age'=>35, 'wife'=>"Wilma");
        array_walk($person, printRow);
        ?>
        
    </body>
</html>
