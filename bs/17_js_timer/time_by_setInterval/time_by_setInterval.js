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
	stop_flag = setInterval("time()",1000);//��ָ���ĺ���������ú���time()����
}

function stop_1()
{
	clearInterval(stop_flag); //ͨ��setInterval()����ֵ��ֹͣ����
}