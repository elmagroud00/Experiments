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
        if (mysqli_connect_errno()) {
            die("mysqli_connect failed: " . mysqli_connect_error());
        }
        print "connect to " . $db->host_info . "<br />";

        $db->query("CREATE TABLE alfas " .
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
        while ($row = $result->fetch_row()) {
            print $row[0] . $row[1] . $row[2] . "<br>\n";
        }
        $result->free();

        $db->close();
        ?>
        <h1>Test SQLite</h1>
        <?php
        /* $db = new SQLiteDatabase("./crm.db", 0666, $error)
          or die("Failed: $error");

          unset($db);
         */
        ?>
        <h1>Test PEAR DB</h1>
        <?php
        require_once 'DB.php';

        PEAR::setErrorHandling(PEAR_ERROR_DIE, "%s<br />\n");
        $dbh = DB::connect("mysql://root@localhost/world");
        if (DB::isError($dbh)) {
            print "Connect failed!\n";
            print "Error message: " . $dbh->getMessage() . "\n";
            print "Error details: " . $dbh->getUserInfo() . "\n";
            exit(1);
        }
        print "Connect OK!\n";
        print "<br />";

        $result = $dbh->query("SELECT Name FROM City WHERE " .
                "CountryCode='NOR'");
        while ($result->fetchInto($row)) {
            //print "$row[0]<br />\n";
            print_r($row);
            print "<br />";
        }

        $code = 'NOR';
        $result = $dbh->query("SELECT Name FROM City WHERE CountryCode = ?", $code);
        while ($result->fetchInto($row)) {
            print "$row[0]<br />\n";
        }
        ?>
        <?php
        require_once 'DB.php';

        $changes = array(
            array(154351, "Trondheim", "NOR"),
            array(521886, "Oslo", "NOR"),
        );

        PEAR::setErrorHandling(PEAR_ERROR_DIE, "%s<br />\n");
        $dbh = DB::connect("mysql://root@localhost/world");
        $sth = $dbh->prepare("UPDATE City SET Population=? " .
                "WHERE Name=? AND CountryCode=?");
        foreach ($changes as $data) {
            $dbh->execute($sth, $data);
            printf("%s: %d row(s) changed<br />\n", $data[1], $dbh->affectedRows());
        }
        ?>
        <h1>DB_FETCHMODE_OBJECT</h1>
        <?php
        require_once 'DB.php';

        class MyResultClass {

            public $row_data;

            function __construct($data) {
                $this->row_data = $data;
            }

            function __get($variable) {
                return $this->row_data[$variable];
            }

        }

        PEAR::setErrorHandling(PEAR_ERROR_DIE, "%s<br />\n");
        $dbh = DB::connect("mysql://root@localhost/world");
        $dbh->setFetchMode(DB_FETCHMODE_OBJECT, "MyResultClass");
        $Code = 'NOR';
        $result = $dbh->query("SELECT Name, Population FROM City WHERE CountryCode = ?", $code);
        while ($row = $result->fetchRow()) {
            print_r($row);
            print  "<br />\n";
        }
        require('XML/RPC.jjjphp');
        require("XML/RPC/Server.php");
        
        new XML_RPC_Response()
        ?>

    </body>
</html>
