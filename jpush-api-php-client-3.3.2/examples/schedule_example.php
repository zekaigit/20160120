<?php

require_once("../src/JPush/JPush.php");

$br = '<br/>';
$app_key = 'dd1066407b044738b6479275';
$master_secret = 'e8cc9a76d5b7a580859bcfa7';

// 初始化
$client = new JPush($app_key, $master_secret);

$payload = $client->push()
    ->setPlatform("all")
    ->addAllAudience()
    ->setNotificationAlert("Hi, 这是一条定时发送的消息")
    ->build();

// 创建一个2016-12-22 13:45:00触发的定时任务
$response = $client->schedule()->createSingleSchedule("每天14点发送的定时任务", $payload, array("time"=>"2016-12-22 13:45:00"));
echo 'Result=' . json_encode($response) . $br;

// 创建一个每天14点发送的定时任务
$response = $client->schedule()->createPeriodicalSchedule("每天14点发送的定时任务", $payload,
        array(
            "start"=>"2016-12-22 13:45:00",
            "end"=>"2016-12-25 13:45:00",
            "time"=>"14:00:00",
            "time_unit"=>"DAY",
            "frequency"=>1
        ));
echo 'Result=' . json_encode($response) . $br;

// 更新指定的定时任务
$response = $client->schedule()->updatePeriodicalSchedule('89c984f4-a880-11e5-b41a-0021f652c102', null, true);
echo "Result=" . json_encode($response) . "\r\n";

// 获取定时任务列表
$response = $client->schedule()->getSchedules();
echo "Result=" . json_encode($response) . "\r\n";

