<!DOCTYPE html>
<!--
To change this license header, choose License Headers in Project Properties.
To change this template file, choose Tools | Templates
and open the template in the editor.
-->
<html>
    <head>
        <meta charset="UTF-8">
        <title>Register</title>
    </head>
    <body>
        <?php
            if(!isset($POST['register']) || ($_POST['register'] != 'Register')) {
        ?>
        <h1>Registation</h1>
        <form method="get" action="register.php">
            <table>
                <tr><td>E-Mail address:</td>
                    <td><input type="text" name="email"/></td></tr>
                <tr><td>First name:</td>
                    <td><input type="text" name="first_name"/></td></tr>
                <tr><td>Last name:</td>
                    <td><input type="text" name="second_name"/></td></tr>
                <tr><td>Password:</td>
                    <td><input type="password" name='password'/></td></tr>
                <tr><td colspan="2">
                        <input type='submit' name='register' value='Register'/>
                    </td>
                </tr>
            </table>
        </form>
        <?php
            } else {
        ?>
        E-Mail: <?php echo $_POST['email']; ?><br/>
        Name: <?php echo $_POST['first_name'] . ' ' . $_POST['last_name']; ?><br/>
        Password: <?php echo $_POST['password']; ?><br/>
        <?php
            }
            ?>
    </body>
</html>
