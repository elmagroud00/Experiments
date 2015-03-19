<table border="1" cellpadding="20" cellspacing="1" bordercolor="#FFFFFF" bgcolor="#999999">
   <tr align="center" bgcolor="#666666">
        <td width="50">Id</td>
        <td width="221">Name</td>
        <td width="329">Age</td>
   </tr>

<?php 
    $conn = mysql_connect("localhost", "root", "") or die(mysql_error());
    mysql_select_db("testDB", $conn) or die(mysql_error());

    $page_num = isset($_GET['page_num']) ? intval($_GET['page_num']) : 1; 

    $page_size = 5;   // show 5 records per page

    $query = "select count(*) as total from persons order by id";
    $result = mysql_query($query);
    $total_records = mysql_result($result, 0, "total");

    $page_count = ceil($total_records / $page_size);
    $offset = ($page_num - 1) * $page_size;

    $query = "select * from persons order by id limit $offset, $page_size";
    $result = mysql_query($query);
    
    while($row = mysql_fetch_object($result)) {
?>
    <tr bgcolor="#FFFFFF">
        <td><?php echo $row->id?></td>
        <td><?php echo $row->name?></td>
        <td><?php echo $row->age?></td>
    </tr>

<?php
    }
?>
</table>

<table border="0" cellpadding="5">
    <tr>
        <td width="100" align="center">
        Current: <?php echo $page_num;?>
        </td>

        <td width="50" align="center">
<?php
    if($page_num != 1) {
        echo "<a href=splitpages.php?page_num=1>First</a>";
?>
        </td>
        <td width="50" align="center">
<?php
        echo "<a href=splitpages.php?page_num=" . ($page_num - 1) . ">Prev</a>";
    }
?>

        </td>
        <td width="50" align="center">
<?php
    if($page_num < $page_count) {
        echo "<a href=splitpages.php?page_num=" . ($page_num + 1) . ">Next</a>";
?>
        </td>
        <td width="50" align="center">
<?php
        echo "<a href=splitpages.php?page_num=" . $page_count . ">Last</a>";
    }
?>
        </td>
    <tr>
</table>
