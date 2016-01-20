var stop_flag = 0;

function time()
{
	var time = new Date();
	var h = time.getHours();
	var m = time.getMinutes();
	var s = time.getSeconds();
	
	document.getElementById("time").value = h+":"+m+":"+s;
}


function start_onload()
{
	stop_flag = setInterval("time()",1000);//在指定的毫秒数后调用函数time()函数
}

function stop_1()
{
	clearInterval(stop_flag); //通过setInterval()返回值，停止调用
}