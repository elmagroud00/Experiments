<?php
    require('XML/RPC.php');
    require_once 'PEAR.php';

    $client = new XML_RPC_Client('/php-source/TestXMLRPC/server.php', 'localhost');
    $client->setDeug(1);
    $vals = array(new XML_RPC_Value('Derick', 'string'));
    $msg = new XML_RPC_Message('hello', $vals);
    $res = call_method($client, $msg);

    if($res !== NULL) {
        echo XML_RPC_decode($res) . "<br />";
    }

    function call_method($client, $msg) {
        /*send request*/
        $p = $client->send($msg);

        if(PEAR::isError($p)) {
            echo $p->getMessage();
        } else {
            if($p->faultCode())  {
                print $p->faultString();
                return NULL;
            } else {
                $res = $p->value();
                return $res;
            }
        }
    }
