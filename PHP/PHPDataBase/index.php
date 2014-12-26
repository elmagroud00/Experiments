<!DOCTYPE html>
<!--
To change this license header, choose License Headers in Project Properties.
To change this template file, choose Tools | Templates
and open the template in the editor.
-->
<html>
    <head>
        <meta charset="UTF-8">
        <title>PHP DataBase</title>
    </head>
    <body>
        <H1>Test1</H1>
        <?php
        $db = new mysqli("localhost", "root", "", "world");
        $sql = "SELECT * FROM City";
        $result = $db->query($sql);
        
        while($row = $result->fetch_assoc()) {
            echo "{$row['Name']} <br />";
        }
        
        $result->close();
        $db->close();
        ?>
    </body>
</html>
