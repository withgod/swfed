--TEST--
replaceActionString() : ActionPush longer parameter
--FILE--
<?php

$swfdata = file_get_contents('tests/textvar.swf');
$obj = new SWFEditor();
$obj->input($swfdata);
$params = array('dummy' => 'dummydummy', 'inputvar' => 'replacedvar');
$obj->replaceActionStrings($params);
echo md5($obj->output())."\n";
?>
===DONE===
--EXPECTF--
1a3f85b044e039b4977c38938d21ab4b
===DONE===
