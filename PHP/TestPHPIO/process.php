<html>
    <title>Process</title>
    <body>
    <h1>Dumping $_POST</h1>      
    <?php 
       var_dump($_POST); 
    ?>
    <h1>Dumping php://input</h1>
    <?php
       $sin = fopen("php://input", "rb");
       while(!feof($sin)) {
           echo fread($sin, 128);
       }
    ?>
    </body>
</html>
