<?php
echo "hello,world !\n"; 
echo "导航到西乡站";
$sub=substr("导航到西乡站",1,6);
echo $sub;

echo 15;


?>
<canvas id="demoCanvas" width="500" height="600"></canvas>
	<script type="text/javascript">
		//通过id获得当前的Canvas对象
		var canvasDom = document.getElementById("demoCanvas");
		//通过Canvas Dom对象获取Context的对象
		var context = canvasDom.getContext("2d");
		context.beginPath();//开始绘制路径
		//绘制以 （60,60）为圆心，50为半径长度，从0度到360度（PI是180度），最后一个参数代表顺时针旋转。
		context.arc(60, 60, 50, 0, Math.PI * 2, true);
		context.lineWidth = 2.0;//线的宽度
		context.strokeStyle = "#000";//线的样式
		context.stroke();//绘制空心的，当然如果使用fill那就是填充了。
	</script>