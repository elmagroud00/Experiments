<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

session_start();
$folder = $_SESSION['folder'];
$filename = $folder . "/question1.txt";
$file_handler = fopen($filename, "a+");
//open file for reading then clean it out 
//pick up any text in the file that may already be there
$comments = fread($file_handler, filesize($filename));
fclose($file_handler);//close this handler;

if(!empty($_POST['posted'])) {
    //create file if first time and then
    //save text that is in $_POST['question1'];
    $question1 = $_POST['question1'];
    $file_handler = fopen($filename, "w+");
    //open file for total overwrite
    if(flock($file_handler, LOCK_EX)) {
        //do exclusive lock
        if(fwrite($file_handler, $question1) == FALSE) {
            echo "Cannot write to file ($filename)";
        }
        flock($file_handler, LOCK_UN);
        //release the lock
    }
    //close the file handler and redirect to next page?
    fclose($file_handler);
    header("Location:page2.php");
} else { ?>
<html>
    <head><title>Files & Folder - On-line Survery</title></head>
    <body>
        <table boder="0">
            <tr><td>Please enter you response to the following survery questions:</td></tr>
            <tr bgcolor="lightblue"><td>What is your option on the statte of the world economy?<br />
                Can yout help us fix it ?</td></tr>
            <tr><td>
                    <form action="<?php echo $_SERVER['PHP_SELF'];?>" method="POST">
                        <input type="hidden" name="posted" value="1"/><br />
                        <textarea name="question1" rows=12 cols=35><?php echo $comments; ?></textarea>
                    </td></tr>
                    <tr><td>
                            <input type="submit" name="submit" value="Submit">
                    </form>
                </td></tr>
        </table>
    </body>
</html>
<?php } ?>
