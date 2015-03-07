<?php
require_once 'Auth.php';

$auth = new Auth("File", ".htpasswd", "login_function");
$auth->start();
if(!$auth->getAuth()) {
    exit;
}

if(!empty($_REQUEST['logout'])) {
    $auth->logout();
    print "<h1>Logged out</h>\n";
    print "<a href=\"$_SERVER[PHP_SELF]\">Log in again</a>\n";
    exit;
}

print "<h1>Logged in!</h1>\n";

if(!empty($_REQUEST['dump'])) {
    print "<pre>SESSION=";
    var_dump($_SESSION);
    print "</pre>\n";
} else {
    print "<a href=\"$_SERVER[PHP_SELF]?dump=1\">Dump session</a><br>\n";
}

print "<a href=\"$_SERVER[PHP_SELF]?logout=1\">Log Out</a>\n";

function login_function() {
    print "<h1>Please Log In</h1>\n";
    print "<form action=\"$_SERVER[PHP_SELF]\" method=\"POST\">\n";
    print "User name: <input name=\"username\">\n";
    print "Password: <input name=\"password\">\n";
    print "<input type=\"submit\" value=\"Log In\">\n";
    print "</form>\n";
    exit;
}
?>
