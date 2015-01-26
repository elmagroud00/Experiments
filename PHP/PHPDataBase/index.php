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
        if(mysqli_connect_errno()) {
            die("mysqli_connect failed: " . mysqli_connect_error());
        }
        print "connect to " . $db->host_info . "<br />";
        
        $db->query("CREATE TABLE alfas ".
                "(year INTEGER, model VARCHAR(50), accel REAL)");
        $stmt = $db->prepare("INSERT INTO alfas VALUES(?, ?, ?)");
        $stmt->bind_param("isd", $year, $model, $accel);
        
        $year = 2001;
        $model = '156 2.0 Selected';
        $accel = 8.6;
        $stmt->execute();
        
        $year = 2003;
        $model = "147 2.0 Selected";
        $accel = 9.3;
        $stmt->execute();
        
        /*
        $query = "SELECT Name FROM City";
        $query .= "SELECT Name FROM Country";
        
        if($db->multi_query($query)) {
            do {
                if($result = $db->store_result()) {
                    while($row = $result->fetch_row()) {
                        printf("Col: %s\n", $row[0]);
                    }
                    $result->close();
                }
            } while($db->next_result());
        }
        */
       $result = $db->query("SELECT * FROM alfas");
        while($row = $result->fetch_row()) {
            print $row[0] . $row[1] . $row[2] . "<br>\n";
        }
        $result->free();
        
        $db->close();
        ?>
        
    </body>
</html>
