var xhr = null;


/*====================以下是和ajax有关的操作==================*/
/*
	函数名：createXHR
	描述：	兼容不同的版本浏览器创建ajax	
	参数：	无
	返回值：创建好的ajax
	备注：	无
*/
function createXHR()
{
	var xmlhttp = null;
	
	//兼容Firefox、chrome、opera等
	if(window.XMLHttpRequest)
		xmlhttp = new XMLHttpRequest();
	//兼容高版本IE
	else if(window.ActiveXObject)
		xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
	//兼容低版本IE
	else
		xmlhttp = new ActiveXObject('Msxml2.XMLHTTP');
	
	//如果创建成功返回非null，否则浏览器不支持创建失败
	if(xmlhttp)
	{
		;//alert('create xmlhttp success!');
	}
	else
	{
		alert('浏览器不支持!');//alert会在网页里面弹出提示消息框，传入字符串或者变量即可在消息框中提示用户或者用于调试
	}
	
	return xmlhttp;
}

/*
	函数名：comm_with_cgi
	描述：	和cgi程序通信，将send_data数据发送给cgi_name，并通过callback回调函数处理返回后的数据
	参数：	cgi_name:和哪个cgi程序通信；
			send_data:要发送给cgi_name的数据；
			method:"GET"方法和”POST”方法，GET方法数据长度有限并且发送的数据是和URL?组合在一起的，明文方式；POST方法长度不受限制，数据是通过send函数发送出去的，密文发送
			async:true:异步；false:同步，异步的方式不阻塞等待服务器的返回，通过事先设置好的回调函数处理服务器的返回，同步方式会阻塞等待，直至服务器有返回
			callback：处理cgi返回数据的回调函数
	返回值：无
	备注：	整个过程采用的异步通信方式
*/
function comm_with_cgi(cgi_name, send_data1, method, async, callback)
{
	//网页数据如果是中文需要先转码然后才能正确传递
	alert(send_data1);
	var send_data = encodeURI(send_data1);


	//指定哪个cgi程序处理网页数据
	var URL = cgi_name;
	if("GET" == method)
	{
		URL+="?";
		URL+=send_data;
	}	
	
	// alert(URL);
	//创建ajax来实现网页和cgi程序通信
	xhr = createXHR();
	
	//创建ajax成功返回非null
	if(xhr)
	{
		// callback();
		//异步通信时，如果服务器有返回了，通过此处设置的回调函数处理服务器返回的信息
		if(true == async)
			xhr.onreadystatechange = callback;
				
		/*
			创建http请求：采用GET方法，指定由URL处理请求，采用异步方式
			false:同步;true:异步；同步会阻塞等待服务器返回，异步不会阻塞，等服务器返回后由回调函数处理服务器响应的信息
		*/
		xhr.open(method,URL,async);
		
		//清除浏览器缓冲的历史记录数据，保证每次请求的数据都是最新的，而不是历史记录
		xhr.setRequestHeader("If-Modified-Since", "0");
		
		//发送数据，如果请求时GET方法创建的，数据会附加URL?后面；POST方法发送的，数据会通过send的参数发送出去
		if("POST" == method)
			xhr.send(send_data);
		else if("GET" == method)
			xhr.send();
		
		//如果是同步方式发送的数据，发送数据后需要通过函数来处理后面服务器返回的数据
		if(false == async)
			callback();
		
	}
}


/*
	函数名：get_cgi_data
	描述：	获取服务器(cgi)返回给网页的数据
	参数：	xmlhttp 为ajax对象
			type为返回数据的类型，0是text;1为xml
	返回值：服务器(cgi)返回给网页的数据，服务器(cgi)没处理完成或者出错返回null
	备注：	无
*/
function get_cgi_data(xmlhttp, type)
{
	/*
		readyState:请求的状态。0 = 未初始化，1 = 正在加载，2 = 已加载，	3 = 交互中，4 = 完成
		status:服务器的HTTP状态码（200对应OK，404对应Not Found（未找到））
	*/
	if(4 == xmlhttp.readyState && 200 == xmlhttp.status)
	{
		//在调试过程中查看服务器返回的数据，正确后再进行解析，调试没问题课将其注释掉
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
	函数名：callback
	描述：	服务器(cgi程序)返回信息后的解析处理程序
	参数：	无
	返回值：无
	备注：	无
*/
function callback()
{
	//服务器(cgi程序)返回的数据格式：led:0(0-15)
	var recv_data = get_cgi_data(xhr, 0);
	
	//判断下服务器是否已经处理完成并返回数据
	if(null != recv_data)
	{
		//alert调试打印服务器返回的数据
		alert(recv_data);
		//根据协议做不同的处理:server:n:OK/NOTOK
		//先找到server:字符串位置
		var index = recv_data.indexOf(":")+1;
		//将server:切割掉
		var tmp = recv_data.substring(index, recv_data.length);
		//找到n后面的分好，以便于切割出n
		index = tmp.indexOf(":");
		var n = tmp.substring(0,index);

		switch(n)
		{
			//登陆处理
			case '1':
			{
			}
			break;
			//注册处理
			case '2':
			{
				var result = tmp.substring(index+1, recv_data.length);
				alert(result);
				if("OK" == result)
				{
					alert("注册成功!");
				}
				else
				{
					alert("注册失败!");
				}
			}
			break;
			//注销处理
			case '3':
			{
			}
			break;
			//查询处理
			case '4':
			{
			}
			break;
			
			//其他处理
			default:
			{
				;//
			}
			break;
			
		}
		
		
		
	}
}

/*=====================以下是对不同用户操作的回调函数========================*/

/*
	函数名：login
	描述：	处理用户登陆操作
	参数：	无
	返回值：无
	备注：	无
*/
function login()
{
}


/*
	函数名：exit
	描述：	处理用户退出操作
	参数：	无
	返回值：无
	备注：	无
*/
function exit()
{
	window.open("","_self");    
	window.close(); 
}




/*
	函数名：add
	描述：	处理用户注册操作
	参数：	无
	返回值：无
	备注：	无
*/
function add()
{
	alert("请在5秒内刷卡注册，否则超时无法注册");
	//通过document来获取网页中用户输入的姓名、工号、性别信息
	var name=document.getElementById("name").value;
	var id=document.getElementById("id").value;
	var sex=document.getElementById("sex").value;
	//将发送给服务器的数据进行组包处理
	var send_data = "2:"+name+":"+id+":"+sex;
	//通过alert显示组包后的数据
	comm_with_cgi("/cgi-bin/deal.cgi", send_data, "GET", true, callback);
}

/*
	函数名：del
	描述：	处理用户注册操作
	参数：	无
	返回值：无
	备注：	无
*/
function del()
{
}


/*
	函数名：query
	描述：	处理用户注册操作
	参数：	无
	返回值：无
	备注：	无
*/
function query()
{
}
