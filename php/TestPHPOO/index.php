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
        error_reporting(null);

        class HelloWorld {

            function display($count) {
                for ($i = 0; $i < $count; $i++) {
                    print "Hello, World\n";
                }
                return $count;
            }

        }

        class HelloWorldDelegator {

            private $obj;

            function __construct() {
                $this->obj = new HelloWorld();
            }

            function __call($name, $arguments) {
                return call_user_func_array(array($this->obj, $name), $arguments);
            }

        }

        $obj = new HelloWorldDelegator();
        print $obj->display(3);
        ?>
        <h1>DataBase</h1>
        <?php
        $mysqli = new mysqli("localhost", "root", "", "test");
        if (mysqli_connect_errno()) {
            printf("Connect failed: %s\n", mysqli_connect_error());
            exit();
        }
        $sql = "CREATE TABLE files(id INTEGER PRIMARY KEY AUTO_INCREMENT, data BLOB)";
        $mysqli->query($sql);

        $stmt = $mysqli->prepare("INSERT INTO files VALUES(NULL, ?)");
        $stmt->bind_param('s', $data);
        $file = "1.png";
        $fp = fopen($file, "r");
        $size = 0;
        while ($data = fread($fp, 102)) {
            $size += strlen($data);
            $stmt->send_long_data(0, $data);
        }
        if ($stmt->execute()) {
            print "$file ($size bytes) was added to the file table\n";
        } else {
            die($conn->error);
        }
        $mysqli->close();
        ?>
        <?php
        $id = 3;
        $conn = mysqli_connect("localhost", "root", "", "test");

        $result = $conn->query("SELECT id, length(data) FROM files LIMIT 20");
        if ($result->num_rows == 0) {
            print "No images!\n";
            print "<a href=\"lnmcc.net\">Click here to add one</a>\n";
            exit();
        }
        while ($row = $result->fetch_row()) {
            print "<a href=\"$_SERVER[PHP_SELF]id=$row[0]\">";
            print "image $row[0] ($row[1] bytes])</a><br />\n";
        }

        $stmt = $conn->prepare("SELECT data FROM files WHERE id = ?");
        $stmt->bind_param("i", $id);
        $stmt->execute();
        $data = null;
        $stmt->bind_result($data);
        if (!$stmt->fetch()) {
            die("No such image!");
        }
        // header("Content-type: image/png");
        print $data;
        ?>
        <?php
        $arr = array("a", "b", "c");

        print_r($arr);
        echo "<br />";
        $arr2 = array_splice($arr, 1);

        print_r($arr2);
        ?>
        <h1>Test Error Handler</h1>
        <?php

        //error_reporting(1);

        function my_error_handler($num, $str, $file, $line) {
            /* if (error_reporting() === 0) {
              print "(Silenced)";
              return;
              } */
            switch ($num) {
                case E_WARNING:
                case E_USER_WARNING:
                    $type = "Warning";
                    break;
                case E_NOTICE:
                case E_USER_NOTICE:
                    $type = "Notice";
                    break;
                default:
                    $type = "Error";
                    break;
            }
            $file = basename($file);
            print "$type: $file: $line: $str\n";
        }

        set_error_handler("my_error_handler");

        trigger_error("not silenced error", E_USER_NOTICE);
        @trigger_error("silenced error", E_USER_NOTICE);
        ?>

        <h1>USE SAX</h1>
        <?php
        $level = 0;
        $char_data = '';

        $xml = xml_parser_create('UTF-8');
        xml_set_element_handler($xml, 'start_handler', 'end_handler');
        xml_set_character_data_handler($xml, 'character_handler');
        xml_parser_set_option($xml, XML_OPTION_CASE_FOLDING, false);
        xml_parse($xml, file_get_contents('test1.xhtml'));
        
        function flush_data() {
            global $level, $char_data;
            
            $char_data  = trim($char_data);
            if(strlen($char_data) > 0) {
                echo "\n";
                $data = preg_split("/\n/", wordwrap($char_data, 76 - ($level * 2)));
                foreach($data as $line) {
                    echo str_repeat(' ', ($level + 1)) . "[" . $line . "]\n";
                }
            }
            $char_data = '';
        }
        
        function start_handler($xml, $tag, $attrobutes) {
            global $level;
            
            flush_data();
            echo "\n" . str_repeat(' ', $level) . "$tag";
            foreach($attrobutes as $key => $value) {
                echo " $key = '$value'";
            }
            $level++;
        }
        
        function end_handler($xml, $tag) {
            global $level;
            
            flush_data();
            $level--;
            echo "\n" . str_repeat(' ', $level) . "/$tag";
        }
        
        function character_handler($xml, $data) {
            global $level, $char_data;
            
            $char_data .= ' ' . $data;
        }

        /*
          function start_handler($xml, $tag, $attributes) {
          global $level;

          echo "\n" . str_repeat(' ', $level) . ">>>$tag" . "<br />";
          foreach ($attributes as $key => $value) {
          echo " $key $value";
          }
          $level++;
          }

          function end_handler($xml, $tag) {
          global $level;

          $level--;
          echo str_repeat(' ', $level) . "<<<$tag" . "<br />";
          }

          function character_handler($xml, $data) {
          global $level;

          $data = preg_split("/\n/", wordwrap($data, 76 - ($level * 2)));
          foreach ($data as $line) {
          echo str_repeat(' ', $level) . $line . "<br />";
          }
          }
         */
        ?>
    </body>
</html>
