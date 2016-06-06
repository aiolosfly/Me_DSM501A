# Me_DSM501A
1.Use the Temperature and Humidity Sensor,DSM501A Dust Sensor and TFT LCD Screen; 
2.Detect PM2.5 , Humidity and temperature ;
3.Display on TFT

改变连线以适应RJ25接口。由于在本案例中为检测pm2.5值，故最小粒子检测能力为1um。使用到的引脚为
#2（Vout2），
#3（电源正），
#5（电源地）

使用MeOrion上Port4进行控制。连接传感器Vout2引脚为Orion板上的数字引脚2.

案例介绍
使用Arduino进行编程。通过DSM501A烟尘传感器，温湿度传感器（Me Temperature and Humidity Sensor V1.0）检测空气的颗粒属性及温湿度，并将数据经过处理后输出到液晶屏（Me TFT LCD）.

更详细介绍参见DSM501A_report.docx
