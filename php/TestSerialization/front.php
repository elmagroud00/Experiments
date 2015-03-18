<?php

include_once "Log.php";
session_start();
?>

<html>
    <head>
        <title>Front Page</title>
    </head>
    <body>
        <?php
        $now = strftime("%c");
        //if(!session_is_registered('l')) {
        if(!isset($_SESSION['l'])) {
            $logger = new Log("/tmp/persistent_log");
            //session_register('l');
            $_SESSION['l'] = 'l';
            $logger->write("Create $now");
            
            echo("<p>Create session and persistent log object.</p>");
        }
        
        $logger->write("Viewed first page {$now}");
        echo "<p>The log contains: </p>";
        echo nl2br($logger->read());
        ?>
        
        <a href="next.php">Move to the next page.</a>
    </body>
</html>