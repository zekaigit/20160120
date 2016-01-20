var led1_flag=0;
function led(led_num)
{
	if(led_num==1)
	{
	// alert("测试");
	// alert(led_num);
	if(0==led1_flag)
	{
		document.getElementById("led1").src="./image/on.bmp";
		led1_flag=1;
	}
	else if(1==led1_flag)
	{
		document.getElementById("led1").src="./image/off.bmp";
		led1_flag=0;
	}
	}
	else if(led_num==2)
	{
	// alert("测试");
	// alert(led_num);
	if(0==led1_flag)
	{
		document.getElementById("led2").src="./image/on.bmp";
		led1_flag=1;
	}
	else if(1==led1_flag)
	{
		document.getElementById("led2").src="./image/off.bmp";
		led1_flag=0;
	}
	}
	else if(led_num==3)
	{
	// alert("测试");
	// alert(led_num);
	if(0==led1_flag)
	{
		document.getElementById("led3").src="./image/on.bmp";
		led1_flag=1;
	}
	else if(1==led1_flag)
	{
		document.getElementById("led3").src="./image/off.bmp";
		led1_flag=0;
	}
	}
}