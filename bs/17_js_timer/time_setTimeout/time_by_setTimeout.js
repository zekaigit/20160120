var stop_flag = 0;

function timeout()
{
	var time = new Date();
	var h = time.getHours();
	var m = time.getMinutes();
	var s = time.getSeconds();
	
	document.getElementById("time").value = h+":"+m+":"+s;
	
	stop_flag = setTimeout("timeout()",1000); //ָ���ĺ���������ú���timeout
}

function start_onload()
{
	timeout();
}

function stop()
{
	clearTimeout(stop_flag); //ͨ��setTimeout����ֵ��ֹͣ��ʱ
}

function start()
{
	timeout();
}