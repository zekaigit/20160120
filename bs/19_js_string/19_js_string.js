
function deal_string(deal_num)
{
	var src = document.getElementById("src").value;//
	var way = document.getElementById("way").value;
	var dest;//�洢������
	switch(deal_num)
	{
		case 1:
			dest = src.charAt(Number(way));//������ָ��λ�õ��ַ���
			break;

		case 2:
			dest = src.indexOf(way);//lastIndexOf();�Ӻ���ǰ�����ַ�����
			break;

		case 3:
			/****src.substr(start,length)****/
			var start = way.substr(0,1);
			var length = way.substr(2,1);
			dest = src.substr(Number(start),Number(length));//�ַ����г�ȡ�ӵ�һ�������±꿪ʼ��ָ����Ŀ���ڶ������������ַ���
			break;

		case 4:
			/****src.substring(start,stop)***/
			var start = way.substring(0,1);
			var stop = way.substring(2);
			dest = src.substring(Number(start),Number(stop));//��ȡ�ַ����н�������ָ���±�֮����ַ���
			//dest = src.substring(2);//��ȡ�ַ�����2��ʼ�Ժ���ַ�
			break;			
		
	}

	document.getElementById("dest").value = dest;//��ʾ���
}