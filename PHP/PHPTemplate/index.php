<!DOCTYPE html>
<!--
To change this license header, choose License Headers in Project Properties.
To change this template file, choose Tools | Templates
and open the template in the editor.
-->
<html>
    <head>
        <meta charset="UTF-8">
        <title>PHP Template: User Information</title>
    </head>
    <body>
        <?php
        if (!empty($_GET['name'])) {
            // do something with the supplied values 
            ?>

            <p><font face="helvetical,arial">Thank you for filling out the form,
                <?php echo $_GET['name'] ?>.</font></p>
        <?php } else {
            ?>
            <p><font face="helvetica,arial">Please enter the
                following information:</font></p>

            <form action="<?php echo $_SERVER['PHP_SELF']; ?>">
                <table>
                    <tr>
                        <td>Name:</td>
                        <td>
                            <input type="text" name="name"/>
                            <input type="submit"/>
                        </td>
                    </tr>
                </table>
            </form>
        <?php } ?>
    </body>
</html>
