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
        <h1>Test 1</h1>
        <?php
        error_reporting(E_ALL);
        /*
          $image = imagecreatetruecolor(150, 150);
          imagealphablending($image, false);

          $white = imagecolorallocate($image, 255, 255, 255);
          imagefilledrectangle($image, 0, 0, 150, 150, $white);

          $red = imagecolorallocatealpha($image, 255, 0, 0, 63);
          imagefilledellipse($image, 75, 75, 80, 50, $red);

          imagealphablending($image, false);
          $gray = imagecolorallocatealpha($image, 70, 70, 70, 63);
          imagefilledrectangle($image, 60, 60, 120, 120, $gray);
         */
        $image = imagecreatetruecolor(256, 60);
        
        for($x = 0; $x < 256; $x++) {
            imageline($image, $x, 0, $x, 19, $x);
            //imageline
        }
        
        header("Content-Type: image/png");
        imagepng($image);
        ?>

    </body>
</html>
