--TEST--
replaceGIFData test;
--FILE--
<?php

$swf_filename = 'tests/saitama.swf';
$gif_filename = 'tests/inasahama.gif';

$swfdata = file_get_contents($swf_filename);
$obj = new SWFEditor();

// $obj->setShapeAdjustMode(SWFEditor::SHAPE_BITMAP_RECT_RESIZE);
// $obj->setShapeAdjustMode(SWFEditor::SHAPE_BITMAP_MATRIX_RESCALE);
$obj->setShapeAdjustMode(SWFEditor::SHAPE_BITMAP_TYPE_TILLED);

$obj->input($swfdata);
$image_id = 1;
$gifdata = file_get_contents($gif_filename);
$obj->replaceGIFData($image_id, $gifdata);
echo md5($obj->output())."\n";
?>
===DONE===
--EXPECTF--
16f3bec42aa6d6249179092fd79fc46d
===DONE===
