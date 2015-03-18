<table width="550" border="1" cellpadding="1" cellspacing="1" bordercolor="#FFFFFF" bgcolor="#999999">
   <tr align="center" bgcolor="#f0f0f0">
        <td width="221">Name</td>
        <td width="329">Age</td>
   </tr>

<?php 
    $conn = mysql_connect("localhost", "root", "") or die(mysql_error());
    mysql_select_db("testDB", $conn) or die(mysql_error());

    if(!$page_num)
        $page_num = 1;

    $page_size = 50;   // show 50 records per page

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
