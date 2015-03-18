<?php
/*
    $dom = new DomDocument();
    $dom->load('test2.xml');
    $root = $dom->documentElement;

    process_children($root);

    function process_children($node) {
        $children = $node->childNodes;

        foreach($children as $elem) {
            if($elem->nodeType == XML_TEXT_NODE) {
                if(strlen($elem->nodeValue)) {
                    echo trim($elem->nodeValue) . "<br />";            
                }
            } else if($elem->nodeType == XML_ELEMENT_NODE) {
                process_children($elem);
            }  
        }
    }
 */
?>
<html>
    <head><title>Test PHP DOM</title></head>

    <body>
        <h1>Test DOM</h1>
        <?php
        $dom = new DomDocument();
        $dom->load('test2.xml');
        $root = $dom->documentElement;

        process_children($root);

        function process_children($node) {
            $children = $node->childNodes;
            foreach($children as $elem) {
                if($elem->nodeType == XML_ELEMENT_NODE) {
                    if($elem->nodeName == 'name') {
                        echo $elem->getAttributeNode('id')->value . "<br />";
                    }
                }
            } 
        }
        ?>
        <h1>Test XPATH</h1>
        <?php
            $xpath = new DomXPath($dom);
            $nodes = $xpath->query("*[local-name()='name']", $dom->documentElement);
            echo $nodes->item(0)->getAttributeNode('id')->value . "<br />";

        ?>

        <h1>Create DOM</h1>
        <?php
            $dom = new DomDocument();
            $html = $dom->createElement('html');
            $html->setAttribute("xmlns", "http://www.w3.org/1999/xhtml");
            $html->setAttribute("xml:lang", "en");
            $html->setAttribute("lang", "en");
            $dom->appendChild($html);

            $head = $dom->createElement('head');
            $html->appendChild($head);

            $title = $dom->createElement('title');
            $title->appendChild($dom->createTextNode("XML Example"));

            $head->appendChild($title);
            $body = $dom->createElement('body');
            $body->setAttribute("background", "bg.png");
            $html->appendChild($body);

            $p = $dom->createElement('p');
            $body->appendChild($p);
            $text = $dom->createTextNode("Move to ");
            $p->appendChild($text);

            $a = $dom->createElement('a');
            $a->setAttribute("href", "http://lnmcc.net");
            $a->appendChild($dom->createTextNode("lnmcc.net"));
            $p->appendChild($a);

            $text = $dom->createTextNode(".");
            $p->appendChild($text);
            $br = $dom->createElement('br');
            $p->appendChild($br);
            $text = $dom->createTextNode("foo & bar");
            $p->appendChild($text);

            echo $dom->saveXML();
        ?>
        <h1>TEST SimpleXML</h1>
        <?php
            $sxl = simplexml_load_file('test2.xml');
            $string = <<<XML
<?xml version='1.0'?>
<html xmlns="http://www.w3c.org/1999/xhtml" xml:lang="en" lang="en">
    <head><title>XML Example</title></head>
    <body background="bg.png">
        <p>
            Move to <a href="http://lnmcc.net">lnmcc.net</a>.
        </p>
        <pre>
            foo
        </pre>
        <p>
            Move to <a href="http://lnmcc.net">lnmee.net</a>.
        </p>
    </body>
</html>
XML;
                $sx2 = simplexml_load_string($string);
               // $sx3 = simplexml_load_dom(new DomDocument());
        ?>
    </body>

</html>
