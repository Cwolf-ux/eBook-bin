# eBook-bin
这是一个基于esp32的电子书可以用来阅读小说和察看天气目前我还没有添加太多功能后续我还打算给它加上连接蓝牙耳机听音乐的功能（也许吧）
总之目前可以使用就对了（因为我是高中生所以可能没什么时间更新代码请见谅）B站：Cwolf
时钟芯片使用DS1302
屏幕的话使用的时1.54寸的黑白双色屏 如果你的屏幕是arduino中的GxEPD2_54_T8驱动也可以直接使用，24p的接口
购买链接
【闲鱼】https://m.tb.cn/h.iEBmmNw?tk=L2Xv5OOD1jG CA381 「快来捡漏【全新1.54寸 WFT0154CZ17 黑白墨水屏】」
#小程序://闲鱼/UHppd5wqVrUnHnr
点击链接直接打开

<img width="1279" height="1706" alt="5e49f3b043350d6cdf3bbe58eff1679a" src="https://github.com/user-attachments/assets/d358e820-c773-47bc-b370-c3b33e23556f" />
<img width="1279" height="1706" alt="1a4ab55a5c0fa75fe380342cb2c60797" src="https://github.com/user-attachments/assets/3371846a-299f-4a06-a1c4-7cb434ed1c72" />
<img width="1279" height="1706" alt="3bd9f81abdd300e44c9b036ef0b76970" src="https://github.com/user-attachments/assets/ec273c95-bf7d-43ca-89fd-a5b45a5bb7ce" />
<img width="1279" height="1706" alt="18b52c07360b9da5afa7ad33fd001fbd" src="https://github.com/user-attachments/assets/da2ce6ad-b990-4e3d-b235-9f8375b4f3ab" />
电路板就暂时不开源了如有需要请联系我，请各位谅解！！！

接线
========================================
 ESP32 电子书硬件接线图 (依据代码引脚)
========================================

一、墨水屏 (GxEPD2_154_T8)
--------------------------------------
ESP32引脚    墨水屏引脚
GPIO5   ->   CS
GPIO21  ->   DC
GPIO15  ->   RST
GPIO16  ->   BUSY
GPIO18  ->   SCK  (SPI时钟)
GPIO23  ->   MOSI (SPI数据输出)
3.3V    ->   VCC
GND     ->   GND

二、SD卡模块 (SPI模式)
--------------------------------------
ESP32引脚    SD卡模块引脚
GPIO4   ->   CS
GPIO18  ->   SCK   (与墨水屏共用)
GPIO19  ->   MISO
GPIO23  ->   MOSI  (与墨水屏共用)
3.3V    ->   VCC
GND     ->   GND

三、DS1302 实时时钟
--------------------------------------
ESP32引脚    DS1302引脚
GPIO14  ->   DAT (I/O)
GPIO27  ->   CLK (SCLK)
GPIO12  ->   RST (CE)
3.3V    ->   VCC
GND     ->   GND

四、按钮 (内部上拉，按下为低电平)
--------------------------------------
左键: GPIO26 --[按键]-- GND
中键: GPIO32 --[按键]-- GND
右键: GPIO33 --[按键]-- GND

五、LED背光
--------------------------------------
GPIO25 --[220欧电阻]-- LED阳极 -- LED阴极 -- GND

六、电池电压测量 (两电阻分压)
--------------------------------------
电池正极 (+)
   │
   ├── 10kΩ电阻 ──┬── GPIO35 (ADC)
   │               │
   └── 电池负极 ── 10kΩ电阻 ── GND

说明：两个10kΩ电阻串联，中点接GPIO35。
满电4.2V时，ADC引脚电压为2.1V，安全。

七、电源连接
--------------------------------------
所有模块的VCC接ESP32的3.3V输出。
所有GND共地。
电池通过分压电路测量，ESP32主供电建议使用稳定3.3V电源。

========================================
        注意事项
========================================
1. SPI总线(18/19/23)为ESP32默认VSPI，墨水屏与SD卡仅CS不同。
2. 按钮使用内部上拉(INPUT_PULLUP)，外部无需上拉电阻。
3. 电池分压电阻已固定，软件已做校准。
4. GPIO35仅能做输入，适合ADC测量。
5. 如开发板引脚定义不同，请根据实际型号调整。

========================================
制作：Cwolf-Cc
版本：1.0
========================================

