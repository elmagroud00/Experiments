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
        <h1>PHP Patterns</h1>
        <?php
            abstract class FileNamingStrategy {
                abstract function createLinkName($filename);
            }
            class ZipFileNamingStrategy extends FileNamingStrategy {
                function createLinkName($filename) {
                    return "http://lnmcc.net/2014/10/24/objectivec-property/a-2/";
                }
            }
            class TarGzFileNamingStrategy extends FileNamingStrategy {
                function createLinkName($filename) {
                    return "http://lnmcc.net/2014/05/20/android-service-framework/f2/";
                }
            }
         
            if(strstr($_SERVER["HTTP_USER_AGENT"], "Win")) {
                $fileNamingObj = new ZipFileNamingStrategy();
            } else {
                $fileNamingObj = new TarGzFileNamingStrategy();
            }
            
            $calc_filename = $fileNamingObj->createLinkName("Calc01");
            $stat_filename = $fileNamingObj->createLinkName("Stat2000");
            
            print <<<EOF
            <h3>The following is a list of greate downloads<</h3>
            <br>
            <a href="$calc_filename">A greate calculator</a><br>
            <a href="$stat_filename">The best statistics application</a><br>
            <br>
EOF;
            
            abstract class User {
                function __construct($name) {
                    $this->name = $name;
                }
                function getName() {
                    return $this->name;
                }
                function hasReadPermission() {
                    return true;
                }
                function hasModifyPermission() {
                    return false;
                }
                function hasDeletePermission() {
                    return false;
                }
                function wantsFlashInterface() {
                    return true;
                }
                protected $name = NULL;
            }
            
            class GuestUser extends User {
                
            }
            
            class CustomerUser extends User {
                function hasModifyPermission() {
                    return true;
                }
            }
            
            class AdminUser extends User {
                function hasModifyPermission() {
                    return true;
                }
                function hasDeletePermission() {
                    return true;
                }
                function wantsFlashInterface() {
                    return false;
                }
            }
            
            class UserFactory {
                private static $users = array("Andi"=>"admin", "Stig"=>"guest", "Derick"=>"customer");
                
                static function Create($name) {
                    if(!isset(self::$users[$name])) {
                        
                    }
                    switch(self::$users[$name]) {
                        case "guest" : return new GuestUser($name);
                        case "customer" : return new CustomerUser($name);
                        case "admin" : return new AdminUser($name);
                        default: break;
                    }
                }
            }
            
            function boolToStr($b) {
                if($b == true) {
                    return "YES\n<br>";
                } else {
                    return "No\n<br>";
                }
            }
            
            function displayPermissions(User $obj) {
                print $obj->getName() . "'s permissions: \n<br>";
                print "Read:" . boolToStr($obj->hasReadPermission());
                print "Modify:" . boolToStr($obj->hasModifyPermission());
                print "Delete:" . boolToStr($obj->hasDeletePermission());
            }
            
            function displayRequirements(User $obj) {
                if($obj->wantsFlashInterface()) {
                    print $obj->getName() . " requires Flash\n<br>";
                }
            }
            
            $logins = array("Andi", "Stig", "Derick");
            
            foreach($logins as $login) {
                displayPermissions(UserFactory::Create($login));
                displayRequirements(UserFactory::Create($login));
            }
            
            ReflectionClass::export("UserFactory");
            print "<br>";
            
            class ClassOne {
                function __construct() {
                    print "ClassOne Construct()\n<br>";
                }
                
                function callClassOne() {
                    print "In Class One\n<br>";
                }
                
                function  __toString() {
                    return "This is ClassOne";
                }
            }
            
            class ClassTwo {
                function __construct() {
                    print "ClassTwo Construct()\n<br>";
                }
                        
                function callClassTwo() {
                    print "In Class Two\n<br>";
                }
                
                function __toString() {
                    return "This is ClassTwo\n<br>";
                }
            }
            
            class ClassOneDelegator {
                private $targets = array();
                
                function __construct() {
                    $this->targets[] = new ClassOne();
                }
                
                function addObject($obj) {
                    $this->targets[] = $obj;
                }
                
                function showAll() {
                    foreach($this->targets as $obj) {
                        echo $obj;
                    }
                }
                
                function __call($name, $args) {
                    foreach($this->targets as $obj) {
                        $r = new ReflectionClass($obj);
                        
                        if($method = $r->getMethod($name)) {
                            if($method->isPublic() && !$method->isAbstract()) {
                                return $method->invoke($obj, $args);
                            }
                        }
                    }
                }
            }
            
            $obj = new ClassOneDelegator();
            $obj->addObject(new ClassTwo());
            $obj->showAll();
            $obj->callClassOne();
            $obj->callClassTwo();
        ?>
    </body>
</html>
