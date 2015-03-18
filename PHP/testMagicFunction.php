<?php

error_reporting(0);

class SportObject {
    private $type = 'DIY';

    public function getType() {
        return $this->type;
    }

    public function __sleep() {
        echo "use serialize() function to save this object.\n";
        return $this;
    }

    public function __wakeup() {
        echo "use unserialize() function to restore this object.\n";
    }
}

$myClass = new SportObject();
$i = serialize($myClass);
echo 'after serialize:     ' . $i . "\n";

$reMyClass = unserialize($i);
echo 'after restore:       ' . $reMyClass->getType() . "\n";

?>
