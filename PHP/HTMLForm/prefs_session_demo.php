<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

session_start();
$backgroundName = $_SESSION['background'];
$foregroundName = $_SESSION['foreground'];
?>

<html>
    <head><title>Front Foor</title></head>
    <?php
    echo $backgroundName;
    echo "<br />";
    echo $foregroundName;
    ?>
    <body bgcolor=<?= $backgroundName; ?> text="<?= $foregroundName; ?>" >
        <h1>Welcome to the Store</h1>
        <p>Would you like to <a href="colors.php">change your preferences?</a></p>
    </body>
</html>