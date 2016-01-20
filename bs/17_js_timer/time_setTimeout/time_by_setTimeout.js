var stop_flag = 0;

function timeout()
{
	var time = new Date();
	var h = time.getHours();
	var m = time.getMinutes();
	var s = time.getSeconds();
	
	document.getElementById("time").value = h+":"+m+":"+s;
	
	stop_flag = setTimeout("timeout()",1000); //指定的毫秒数后调用函数timeout
}

function start_onload()
{
	timeout();
}

function stop()
{
	clearTimeout(stop_flag); //通过setTimeout返回值，停止定时
}

function start()
{
	timeout();
}