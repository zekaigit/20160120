<html>
<body>
<canvas id = "myCanvas" width="200" height="100" style="border:1px solid #c3c3c3;">
Your browser does not support the canvas element.
</canvas>

<script type="text/javascript">
var c=document.getElementByID("myCanvas");
var cxt=c.getContext("2d");
cxt.fillStype="#FF0000";
cxt.beginPath();
cxt.arc(70,18,15,0,Math.PI*2,true);
cxt.closePath();
cxt.fill();
</script>

</body>
</html>