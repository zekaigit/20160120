
var d = new Date();
var hour = d.getHours();
document.write("<br>");
document.write("���ڵ�ʱ���ǣ�");
document.write(d.getFullYear());
document.write("��");
document.write(d.getMonth()+1);
document.write("��");
document.write(d.getDate());
document.write("��");
document.write(" ����");
document.write(d.getDay()+" ");
document.write(d.getHours());
document.write("��");
document.write(d.getMinutes());
document.write("��");
document.write(d.getSeconds());
document.write("��");
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
