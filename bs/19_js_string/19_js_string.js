
function deal_string(deal_num)
{
	var src = document.getElementById("src").value;//
	var way = document.getElementById("way").value;
	var dest;//存储处理结果
	switch(deal_num)
	{
		case 1:
			dest = src.charAt(Number(way));//返回在指定位置的字符。
			break;

		case 2:
			dest = src.indexOf(way);//lastIndexOf();从后向前搜索字符串。
			break;

		case 3:
			/****src.substr(start,length)****/
			var start = way.substr(0,1);
			var length = way.substr(2,1);
			dest = src.substr(Number(start),Number(length));//字符串中抽取从第一个参数下标开始的指定数目（第二个参数）的字符。
			break;

		case 4:
			/****src.substring(start,stop)***/
			var start = way.substring(0,1);
			var stop = way.substring(2);
			dest = src.substring(Number(start),Number(stop));//提取字符串中介于两个指定下标之间的字符。
			//dest = src.substring(2);//提取字符串从2开始以后的字符
			break;			
		
	}

	document.getElementById("dest").value = dest;//显示结果
}