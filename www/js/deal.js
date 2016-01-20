var xhr = null;


/*====================�����Ǻ�ajax�йصĲ���==================*/
/*
	��������createXHR
	������	���ݲ�ͬ�İ汾���������ajax	
	������	��
	����ֵ�������õ�ajax
	��ע��	��
*/
function createXHR()
{
	var xmlhttp = null;
	
	//����Firefox��chrome��opera��
	if(window.XMLHttpRequest)
		xmlhttp = new XMLHttpRequest();
	//���ݸ߰汾IE
	else if(window.ActiveXObject)
		xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
	//���ݵͰ汾IE
	else
		xmlhttp = new ActiveXObject('Msxml2.XMLHTTP');
	
	//��������ɹ����ط�null�������������֧�ִ���ʧ��
	if(xmlhttp)
	{
		;//alert('create xmlhttp success!');
	}
	else
	{
		alert('�������֧��!');//alert������ҳ���浯����ʾ��Ϣ�򣬴����ַ������߱�����������Ϣ������ʾ�û��������ڵ���
	}
	
	return xmlhttp;
}

/*
	��������comm_with_cgi
	������	��cgi����ͨ�ţ���send_data���ݷ��͸�cgi_name����ͨ��callback�ص����������غ������
	������	cgi_name:���ĸ�cgi����ͨ�ţ�
			send_data:Ҫ���͸�cgi_name�����ݣ�
			method:"GET"�����͡�POST��������GET�������ݳ������޲��ҷ��͵������Ǻ�URL?�����һ��ģ����ķ�ʽ��POST�������Ȳ������ƣ�������ͨ��send�������ͳ�ȥ�ģ����ķ���
			async:true:�첽��false:ͬ�����첽�ķ�ʽ�������ȴ��������ķ��أ�ͨ���������úõĻص���������������ķ��أ�ͬ����ʽ�������ȴ���ֱ���������з���
			callback������cgi�������ݵĻص�����
	����ֵ����
	��ע��	�������̲��õ��첽ͨ�ŷ�ʽ
*/
function comm_with_cgi(cgi_name, send_data1, method, async, callback)
{
	//��ҳ���������������Ҫ��ת��Ȼ�������ȷ����
	alert(send_data1);
	var send_data = encodeURI(send_data1);


	//ָ���ĸ�cgi��������ҳ����
	var URL = cgi_name;
	if("GET" == method)
	{
		URL+="?";
		URL+=send_data;
	}	
	
	// alert(URL);
	//����ajax��ʵ����ҳ��cgi����ͨ��
	xhr = createXHR();
	
	//����ajax�ɹ����ط�null
	if(xhr)
	{
		// callback();
		//�첽ͨ��ʱ������������з����ˣ�ͨ���˴����õĻص�����������������ص���Ϣ
		if(true == async)
			xhr.onreadystatechange = callback;
				
		/*
			����http���󣺲���GET������ָ����URL�������󣬲����첽��ʽ
			false:ͬ��;true:�첽��ͬ���������ȴ����������أ��첽�����������ȷ��������غ��ɻص����������������Ӧ����Ϣ
		*/
		xhr.open(method,URL,async);
		
		//���������������ʷ��¼���ݣ���֤ÿ����������ݶ������µģ���������ʷ��¼
		xhr.setRequestHeader("If-Modified-Since", "0");
		
		//�������ݣ��������ʱGET���������ģ����ݻḽ��URL?���棻POST�������͵ģ����ݻ�ͨ��send�Ĳ������ͳ�ȥ
		if("POST" == method)
			xhr.send(send_data);
		else if("GET" == method)
			xhr.send();
		
		//�����ͬ����ʽ���͵����ݣ��������ݺ���Ҫͨ�����������������������ص�����
		if(false == async)
			callback();
		
	}
}


/*
	��������get_cgi_data
	������	��ȡ������(cgi)���ظ���ҳ������
	������	xmlhttp Ϊajax����
			typeΪ�������ݵ����ͣ�0��text;1Ϊxml
	����ֵ��������(cgi)���ظ���ҳ�����ݣ�������(cgi)û������ɻ��߳�����null
	��ע��	��
*/
function get_cgi_data(xmlhttp, type)
{
	/*
		readyState:�����״̬��0 = δ��ʼ����1 = ���ڼ��أ�2 = �Ѽ��أ�	3 = �����У�4 = ���
		status:��������HTTP״̬�루200��ӦOK��404��ӦNot Found��δ�ҵ�����
	*/
	if(4 == xmlhttp.readyState && 200 == xmlhttp.status)
	{
		//�ڵ��Թ����в鿴���������ص����ݣ���ȷ���ٽ��н���������û����ν���ע�͵�
		// alert("cgi:"+xmlhttp.responseText);
		if(0 == type)
			return xmlhttp.responseText;
		else if(1 == type)
			return xmlhttp.responseXML;
	}
	else
		return null;

	
}




/*
	��������callback
	������	������(cgi����)������Ϣ��Ľ����������
	������	��
	����ֵ����
	��ע��	��
*/
function callback()
{
	//������(cgi����)���ص����ݸ�ʽ��led:0(0-15)
	var recv_data = get_cgi_data(xhr, 0);
	
	//�ж��·������Ƿ��Ѿ�������ɲ���������
	if(null != recv_data)
	{
		//alert���Դ�ӡ���������ص�����
		alert(recv_data);
		//����Э������ͬ�Ĵ���:server:n:OK/NOTOK
		//���ҵ�server:�ַ���λ��
		var index = recv_data.indexOf(":")+1;
		//��server:�и��
		var tmp = recv_data.substring(index, recv_data.length);
		//�ҵ�n����ķֺã��Ա����и��n
		index = tmp.indexOf(":");
		var n = tmp.substring(0,index);

		switch(n)
		{
			//��½����
			case '1':
			{
			}
			break;
			//ע�ᴦ��
			case '2':
			{
				var result = tmp.substring(index+1, recv_data.length);
				alert(result);
				if("OK" == result)
				{
					alert("ע��ɹ�!");
				}
				else
				{
					alert("ע��ʧ��!");
				}
			}
			break;
			//ע������
			case '3':
			{
			}
			break;
			//��ѯ����
			case '4':
			{
			}
			break;
			
			//��������
			default:
			{
				;//
			}
			break;
			
		}
		
		
		
	}
}

/*=====================�����ǶԲ�ͬ�û������Ļص�����========================*/

/*
	��������login
	������	�����û���½����
	������	��
	����ֵ����
	��ע��	��
*/
function login()
{
}


/*
	��������exit
	������	�����û��˳�����
	������	��
	����ֵ����
	��ע��	��
*/
function exit()
{
	window.open("","_self");    
	window.close(); 
}




/*
	��������add
	������	�����û�ע�����
	������	��
	����ֵ����
	��ע��	��
*/
function add()
{
	alert("����5����ˢ��ע�ᣬ����ʱ�޷�ע��");
	//ͨ��document����ȡ��ҳ���û���������������š��Ա���Ϣ
	var name=document.getElementById("name").value;
	var id=document.getElementById("id").value;
	var sex=document.getElementById("sex").value;
	//�����͸������������ݽ����������
	var send_data = "2:"+name+":"+id+":"+sex;
	//ͨ��alert��ʾ����������
	comm_with_cgi("/cgi-bin/deal.cgi", send_data, "GET", true, callback);
}

/*
	��������del
	������	�����û�ע�����
	������	��
	����ֵ����
	��ע��	��
*/
function del()
{
}


/*
	��������query
	������	�����û�ע�����
	������	��
	����ֵ����
	��ע��	��
*/
function query()
{
}
