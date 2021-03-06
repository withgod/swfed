<?php

$compress = true;

switch($argc) {
  case 2:
    $swf_filename = $argv[1];
    break;
  case 3:
    if ($argv[1] == '-u') {
       $compress = false;
       $swf_filename = $argv[2];
       break;
    }
  default:
    fprintf(STDERR, "Usage: php swfcompress.phps [-u] <swf_file>\n");
    exit(1);
}

$swf_data = file_get_contents($swf_filename);

$swf = new SWFEditor();
if ($swf->input($swf_data) == false) {
    fprintf(STDERR, "input failed\n");
    exit(1);
}

$info = $swf->getHeaderInfo();

$info['compress'] =  $compress;
if ($info['compress'] && $info['version'] < 6) {
	$info['version'] = 6;
}

$swf->setHeaderInfo($info);

echo $swf->output();
