<!--大幅的行车路线地图，带坐标转换-->  
<!DOCTYPE html>  
<html>  
<head>  
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />  
  
<?php  
      
    $jingwei="new BMap.Point($longitude,$latitude);"  
      
?>  
<title>环评项目定位</title>  
<script type="text/javascript" src="http://api.map.baidu.com/api?v=1.3"></script>  
<script type="text/javascript" src="http://dev.baidu.com/wiki/static/map/API/examples/script/convertor.js"></script>  <!--引用坐标转换脚本-->  
</head>  
<body>  
    <h2 align="center">环评项目定位</h2>  
    <div style="width:800px;height:500px;margin-left: auto;margin-right: auto;border:1px solid gray"id="container"></div>  
    <?php include("foot.php");?>    
</body>  
</html>  
<script type="text/javascript">  
translateCallback = function (point){ //转换坐标  
    map.clearOverlays();  
      
    var marker = new BMap.Marker(point); //创立坐标点      
    map.addOverlay(marker); //加入标注  
    map.setCenter(point);//将标注放入地图  
    marker.setAnimation(BMAP_ANIMATION_BOUNCE); //跳动的动画  
    map.centerAndZoom(point,15); //设置中心点  
      
    var pointb=new BMap.Point(116.138100,39.729679);//设置起始点房山环保局  
    var driving = new BMap.DrivingRoute(map, {renderOptions:{map: map, autoViewport: true}});//驾车路线  
    driving.search(pointb, point);//两点驾车  
      
    map.addControl(new BMap.NavigationControl());               // 添加平移缩放控件  
    map.addControl(new BMap.ScaleControl());                    // 添加比例尺控件  
    map.addControl(new BMap.MapTypeControl());          //添加地图类型控件  
    map.setCurrentCity("房山");          // 设置地图显示的城市 此项是必须设置的  
    map.enableScrollWheelZoom(true);//鼠标缩放  
}  
  
  
var map = new BMap.Map("container",{mapType: BMAP_NORMAL_MAP});      //设置普通地图为底图  
var gpsPoint = <?php echo $jingwei?>//将PHP的经纬度值传给JS  
    BMap.Convertor.translate(gpsPoint,0,translateCallback);//调用坐标转换函数  
  
  
  
  
</script>  