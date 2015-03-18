<!DOCTYPE html>
<!--
To change this license header, choose License Headers in Project Properties.
To change this template file, choose Tools | Templates
and open the template in the editor.
-->
<html>
    <head>
        <meta charset="UTF-8">
        <title>Handing Output</title>
    </head>
    <body>
        <?php
        ob_start();
        phpinfo();
        $phpinfo = ob_get_contents();
        ob_end_clean();
        
        if(strpos($phpinfo, "module_gd") == false) {
            echo "You do not hava GD Graphics support in your PHP, sorry.";
        } else {
            echo "Congratulations, you hava GD Graphics support!";
        }
        ?>
    </body>
</html>
