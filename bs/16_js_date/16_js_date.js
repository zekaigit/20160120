
var d = new Date();
var hour = d.getHours();
document.write("<br>");
document.write("现在的时间是：");
document.write(d.getFullYear());
document.write("年");
document.write(d.getMonth()+1);
document.write("月");
document.write(d.getDate());
document.write("日");
document.write(" 星期");
document.write(d.getDay()+" ");
document.write(d.getHours());
document.write("点");
document.write(d.getMinutes());
document.write("分");
document.write(d.getSeconds());
document.write("秒");
document.write("<br>");
document.write("<br>");
if (hour < 12)
{
	document.write("Good morning");
}
else if (hour < 18)
{
	document.write("Good afternoon");
}
else if(hour < 24)
{
	document.write("Good night");
}
