--TEST--
replaceJpegData test;
--FILE--
<?php

$swf_filename = 'tests/saitama.swf';
$gif_filename = 'tests/5.jpg';

$swfdata = file_get_contents($swf_filename);
$obj = new SWFEditor();

$obj->setShapeAdjustMode(SWFEditor::SHAPE_BITMAP_RECT_RESIZE);
// $obj->setShapeAdjustMode(SWFEditor::SHAPE_BITMAP_MATRIX_RESCALE);
// $obj->setShapeAdjustMode(SWFEditor::SHAPE_BITMAP_TYPE_TILLED);

$obj->input($swfdata);
$image_id = 1;
$gifdata = file_get_contents($gif_filename);
$obj->replaceJpegData($image_id, $gifdata);
echo md5($obj->output())."\n";
?>
===DONE===
--EXPECTF--
51e77504526506cb5ea22ce187d55c30
===DONE===
