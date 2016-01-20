<?php

file_put_contents("D:\\wamp\\www\\wei\\tmp.txt", "start\n",FILE_APPEND);
	
$animal=array(
'hello',
'cat'=>array('hello','world'),
'dog'=>1,
'sheep'
);

//var_dump($animal);
$ret=var_export($animal,true);
echo "var_export result: ".$ret;

$string="qrscene_123123";

$rest = substr($string, 8, strlen($string)-8);//123123
echo $rest;

//$string2="导航到西乡站";
echo '导航到西乡站';

$ret=mb_substr( $string2, 0, 3,'utf-8' );
echo $ret;

file_put_contents("D:\\wamp\\www\\wei\\tmp.txt", "var_export result: ".$ret."\n",FILE_APPEND);
file_put_contents("D:\\wamp\\www\\wei\\tmp.txt", "end\n",FILE_APPEND);


/*
file_put_contents("D:\\wamp\\www\\wei\\tmp.txt",var_export($_GET,true),FILE_APPEND);
file_put_contents("D:\\wamp\\www\\wei\\tmp.txt","\n",FILE_APPEND);
file_put_contents("D:\\wamp\\www\\wei\\tmp.txt",var_export($HTTP_RAW_POST_DATA,true),FILE_APPEND);
*/
?>