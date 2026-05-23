
#include <GxEPD2_BW.h>
#include <U8g2_for_Adafruit_GFX.h>
#include <HTTPClient.h>
#include <stdlib.h>
#include <SPI.h>
#include <stdint.h>
#include <ThreeWire.h>
#include <RtcDS1302.h>
#include <TimeLib.h>
#include <NtpClientLib.h>
#include <ESP8266_Seniverse.h>
#include <OneButton.h>

//当升级开始时，打印日志
void update_started() {

}
//当升级结束时，打印日志
void update_finished() {

}
//当升级中，打印日志
void update_progress(int cur, int total) {

}
//当升级失败时，打印日志
void update_error(int err) {
  Serial.printf("CALLBACK:  HTTP update fatal error code %d\n", err);
 }

#include <HTTPUpdate.h>
#include <SimpleTimer.h>

const String BINID = "1.0";
volatile int BT;
char* VERSION_URL;
volatile int WZ;
volatile bool SDcard;
volatile int page;
volatile int Mode;
volatile int chooes;
volatile int ZT;
volatile int i;
volatile int P;
volatile long K;
String RWB;
volatile int TQGX;
volatile int CSX;
volatile int SX;
volatile int LED;
String Bin;
String cmd;
ThreeWire Wire_14_27_12(14, 27, 12);
RtcDS1302<ThreeWire> rtc(Wire_14_27_12);
String TQ[]={"N/A", "N/A", "N/A", "N/A", "N/A", "N/A", "N/A", "N/A", "N/A", "N/A", "N/A", "N/A", "N/A", "N/A", "N/A"};

int8_t timeZone = 8;
const PROGMEM char *ntpServer = "ntp1.aliyun.com";
Forecast forecast;
WeatherNow weatherNow;
String WB[]={"System", "N/A", "N/A", "N/A", "N/A", "N/A", "N/A", "N/A"};

OneButton button33(33, true);
OneButton button26(26, true);
OneButton button32(32, true);
SimpleTimer timer;

//墨水屏初始化
GxEPD2_BW<GxEPD2_154_T8, GxEPD2_154_T8::HEIGHT> display(GxEPD2_154_T8(5, 21, 15, 16));
U8G2_FOR_ADAFRUIT_GFX u8g2;

#include <WiFiManager.h>
  WiFiManager wm;
  bool res;
#include <SdFat.h>
#include <string.h>
extern SdFs sd;
SdFat SD;
SdFat sd;
SdFile myFile;
void attachDoubleClick33() {
  if (ZT == 1) {
    ZT = 2;

  }
  SX = 0;

}

void attachLongPressStart26() {
  if (page == 1) {
    page++;

  }
  SX = 0;

  clearEPD();
}

void attachLongPressStart32() {
  if (page == 2 && Mode == 0) {
    page--;

  }
  if (ZT >= 1) {
    Mode = 1;

  } else {
    Mode = 0;

  }
  if (ZT >= 1) {
    //设置中文字体字号15
    u8g2.setFont(u8g2_font_wqy12_t_gb2312);
    display.fillRoundRect(25, 45, 95, 52, 5, GxEPD_WHITE);
    display.drawRoundRect(30, 50, 90, 50, 5, GxEPD_BLACK);
    showCH(50, 70, "保存中...");
    JSX(0, 0, 255, 255);
    (createFileWithContent("Save", Sou(chooes), K));
    ZT = 0;

  }
  chooes = 1;
  SX = 0;
  clearEPD();
 
}

void attachDuringLongPress33() {
  if (ZT == 2 && K > 50) {
    K = K - 100;

  }
  if (Bin != " " && (Mode == 4 && chooes == 2)) {
    if (Bin == BINID) {
      //设置中文字体字号15
      u8g2.setFont(u8g2_font_wqy12_t_gb2312);
      display.fillRoundRect(25, 45, 95, 52, 5, GxEPD_WHITE);
      display.drawRoundRect(30, 50, 90, 50, 5, GxEPD_BLACK);
      showCH(50, 70, "开始更新");
      showCH(40, 85, "大概需要2~3分钟");
      JSX(0, 0, 255, 255);
      WiFiClient OTAUpdateClient;
 
      httpUpdate.onStart(update_started);//当升级开始时
      httpUpdate.onEnd(update_finished); //当升级结束时
      httpUpdate.onProgress(update_progress); //当升级中
      httpUpdate.onError(update_error); //当升级失败时
      t_httpUpdate_return ret = httpUpdate.update(OTAUpdateClient, "http://bin.bemfa.com/b/314612/3BcMGEyM2QyNzliZGI1NGYyYzgyNDdjNTZlMzRmYzZiZTY=eBook.bin");
      switch(ret) {
        case HTTP_UPDATE_FAILED:      //当升级失败
      
          break;
        case HTTP_UPDATE_NO_UPDATES:  //当无升级
     
          break;
        case HTTP_UPDATE_OK:         //当升级成功

          break;
        }

    }

  }
  SX = 0;
 
}

void attachClick26() {
  if (((page == 2 && chooes < 5) && Mode == 0) && ZT == 0) {
    chooes++;

  }
  if (Mode == 1 && ZT == 0) {
    chooes++;
    i = 1;
    P = 0;

  }
  if (Mode == 4) {
    chooes++;

  }
  if (ZT == 1) {
    K = K + 1;

  }
  if (ZT == 2) {
    K = K + 10;

  }
  clearEPD();
  SX = 0;

}

void Simple_timer_1() {
  if (page == 1) {
    SX = 0;
    clearEPD();

  }
}

void Simple_timer_2() {
  TQGX = 0;
}

void attachDuringLongPress26() {
  if (ZT == 2) {
    K = K + 50;

  }
  clearEPD();
  SX = 0;
}

void attachClick32() {
  if ((page == 2 && chooes > 1) && Mode == 0) {
    chooes--;

  }
  if (Mode == 1 && ZT == 0) {
    chooes--;
    i = 1;
    P = 0;

  }
  if (Mode == 4) {
    chooes--;

  }
  if (ZT == 1) {
    K = K - 1;

  }
  clearEPD();
  SX = 0;

}

void attachClick33() {
  if (Mode == 1 && ZT == 0) {
    ZT = 1;
    //设置中文字体字号15
    u8g2.setFont(u8g2_font_wqy12_t_gb2312);
    display.fillRoundRect(25, 25, 95, 72, 5, GxEPD_WHITE);
    display.drawRoundRect(30, 30, 90, 70, 5, GxEPD_BLACK);
    showCH(50, 45, "读取中...");
    showCH(32, 65, "首次耗时较长");
    showCH(32, 85, "可能要5~6分钟");
    JSX(0, 0, 255, 255);
    K = RadeSave("Save", Sou(chooes));

  }
  if (page == 2 && Mode == 0) {
    Mode = chooes;
    if (Mode == 4) {
      chooes = 1;

    }

  }
  if (ZT == 2 && K > 10) {
    K = K - 50;

  }
  i = 1;
  P = 0;
  clearEPD();
  SX = 0;

  if (page == 2 && Mode == 0) {
    Mode = chooes;
    if (Mode == 4) {
      chooes = 1;

    }

  }
  if (Mode == 4) {
    if (chooes == 2) {
      display.fillRoundRect(15, 45, 105, 90, 5, GxEPD_WHITE);
      display.drawRoundRect(16, 50, 105, 88, 5, GxEPD_BLACK);
      // wifi的状态
      if (WiFi.status() == 3) {
        showCH(20, 70, "正在获取最新版本...");
        showCH(20, 90, "可长按返回中断");
        JSX(0, 0, 255, 255);
        Bin = "";
        while (Bin == "") {
          Bin = getServerVersion();
          delay(1500);
          if (digitalRead(26) == 0) {
            Bin = "获取失败";

          }
   
        }
        if (Bin != "获取失败") {
          display.fillRoundRect(15, 45, 105, 52, 5, GxEPD_WHITE);
          display.drawRoundRect(20, 50, 100, 50, 5, GxEPD_BLACK);
          showCH(30, 70, "获取成功");
          JSX(0, 0, 255, 255);
          delay(600);

        }

      } else {
        showCH(40, 70, "网络未连接");

      }

    }
    if (chooes == 3) {
      //设置中文字体字号15
      u8g2.setFont(u8g2_font_wqy12_t_gb2312);
      display.fillRoundRect(25, 45, 95, 52, 5, GxEPD_WHITE);
      display.drawRoundRect(30, 50, 90, 50, 5, GxEPD_BLACK);
      // wifi的状态
      if (WiFi.status() == 3) {
        while (NTP.getDateYear() == 1970) {
          delay(500);
        }
        //设置中文字体字号12
        u8g2.setFont(u8g2_font_wqy12_t_gb2312);
        rtc.SetDateTime(RtcDateTime(NTP.getDateYear(), NTP.getDateMonth(), NTP.getDateDay(), NTP.getTimeHour24(), NTP.getTimeMinute(), NTP.getTimeSecond()));
        while (rtc.GetDateTime().Minute() != NTP.getTimeMinute()) {
          delay(100);
        }
        showCH(50, 65, "校准成功");

      } else {
        showCH(50, 65, "网络未连接");

      }
      JSX(0, 0, 255, 255);

    }

  }
  if (ZT == 2 && K > 10) {
    K = K - 50;

  }
  i = 1;
  P = 0;
  clearEPD();
  SX = 0;
 
}

char* changetxt(String str) {
  return const_cast<char*>(str.c_str());
}

void clearEPD() {
  display.fillScreen(GxEPD_WHITE); // 填充白色
}

void QSX() {
  display.display(false);
}

void attachDoubleClick26() {
  if (LED == 1) {
    dacWrite(25, 0);
    LED = 0;

  } else {
    dacWrite(25, 255);
    LED = 1;

  }
  //设置中文字体字号15
  u8g2.setFont(u8g2_font_wqy12_t_gb2312);
  display.fillRoundRect(25, 45, 95, 52, 5, GxEPD_WHITE);
  display.drawRoundRect(30, 50, 90, 50, 5, GxEPD_BLACK);
  if (LED == 1) {
    showCH(50, 70, "灯已开启");

  } else {
    showCH(50, 70, "灯已关闭");

  }
  JSX(0, 0, 255, 255);
  delay(500);
  clearEPD();
  SX = 0;
}

long RadeSave(char* path, char* filename) {

      String fullPath = String(path) + "/" + filename;

      if (myFile.open(fullPath.c_str(), O_READ)) {
          String numberStr = "";
          while (myFile.available()) {
              char c = myFile.read();
              if (isDigit(c) || c == '-') {
                  numberStr += c;
              }
          }
          myFile.close();

          if (numberStr.length() > 0) {
              int value = numberStr.toInt();
       
              return value;
          }
      }


      return 0;

}

bool createFileWithContent(char* path, char* filename, int value) {
   {
      // 构建完整文件路径
      String fullPath = String(path);
      if (!fullPath.endsWith("/")) {
          fullPath += "/";
      }
      fullPath += filename;

      // 先创建目录（如果不存在）
      if (!sd.exists(path)) {
          if (!sd.mkdir(path)) {
              Serial.print("Failed to create directory: ");
            
              return false;
          }
          Serial.print("Directory created: ");

      }

      // 在指定路径创建文件并写入整数
      if (myFile.open(fullPath.c_str(), O_RDWR | O_CREAT | O_TRUNC)) {
          myFile.println(value);
          myFile.close();
          Serial.print("File created with value: ");
          Serial.print(fullPath);
          Serial.print(" -> ");

          return true;
      } else {
   
          return false;
      }
  }
}

void Mode0() {
  if (Mode == 0) {
    if (page == 1) {
      if (TQGX == 0 && (weatherNow.update() && forecast.update())) {
        TQ[0] = weatherNow.getWeatherText();
        TQ[1] = weatherNow.getDegree();
        TQ[2] = forecast.getHigh(0);
        TQ[3] = forecast.getLow(0);
        TQ[4] = forecast.getRain(0);
        TQ[5] = forecast.getHumidity(0);
        TQ[6] = forecast.getWindDirection(0);
        TQ[7] = forecast.getWindSpeed(0);
        TQ[8] = forecast.getWindScale(0);
        TQGX = 1;

      }
      u8g2.setFont(u8g2_font_timR24_tf);
      showCH(10, 30, changetxt(String(rtc.GetDateTime().Hour()) + String(":") + String(rtc.GetDateTime().Minute())));
      //设置中文字体字号15
      u8g2.setFont(u8g2_font_wqy15_t_gb2312);
      showCH(92, 15, changetxt(String(rtc.GetDateTime().Month()) + String("月") + String(rtc.GetDateTime().Day()) + String("日")));
      switch (rtc.GetDateTime().DayOfWeek()) {
       case 0:
        showCH(95, 32, changetxt("星期天"));
        break;
       case 1:
        showCH(95, 32, changetxt("星期一"));
        break;
       case 2:
        showCH(95, 32, changetxt("星期二"));
        break;
       case 3:
        showCH(95, 32, changetxt("星期三"));
        break;
       case 4:
        showCH(95, 32, changetxt("星期四"));
        break;
       case 5:
        showCH(95, 32, changetxt("星期五"));
        break;
       case 6:
        showCH(95, 32, changetxt("星期六"));
        break;
      }
      display.drawRect(0, 0, 150, 35, GxEPD_BLACK);
      display.drawFastVLine(90, 0, 34, GxEPD_BLACK);
      //设置中文字体字号15
      u8g2.setFont(u8g2_font_wqy12_t_gb2312);
      if (BT == 2) {
         u8g2.setFont(u8g2_font_open_iconic_all_1x_t);
          u8g2.drawGlyph(130,50+1*8,94);

      }
      showCH(2, 50, changetxt(String("当前天气：") + String(TQ[0])));
      showCH(2, 65, changetxt(String("当前温度：") + String(TQ[1]) + String("℃")));
      showCH(50, 135, changetxt(String("剩余电量：") + String(getBatteryPercent()) + String("%")));
      //设置中文字体字号12
      u8g2.setFont(u8g2_font_wqy12_t_gb2312);
      showCH(0, 80, changetxt(String("降水概率：") + String(TQ[4]) + String("%")));
      showCH(0, 95, changetxt(String("湿度：") + String(TQ[5]) + String("%")));
      showCH(0, 110, changetxt(String("↑") + String(TQ[2]) + String("℃") + String("↓") + String(TQ[3]) + String("℃")));
      // wifi的状态
      if (WiFi.status() == 3) {
          u8g2.setFont(u8g2_font_open_iconic_all_2x_t);
          u8g2.drawGlyph(5,133+1*8,248);

      }
      if (SDcard == 1) {
          u8g2.setFont(u8g2_font_open_iconic_all_2x_t);
          u8g2.drawGlyph(30,133+1*8,167);

      }
      display.drawFastHLine(90, 17, 60, GxEPD_BLACK);
      display.drawFastHLine(0, 115, 150, GxEPD_BLACK);

    }
    if (page == 2) {
      //设置中文字体字号15
      u8g2.setFont(u8g2_font_wqy12_t_gb2312);
      showCH(5, 40, "阅读");
      showCH(65, 40, "天气");
      showCH(126, 40, "配网");
      showCH(126, 100, "设置");
        u8g2.setFont(u8g2_font_open_iconic_all_2x_t);
        u8g2.drawGlyph(10,5+2*8,97);
      //阅读图标
        u8g2.setFont(u8g2_font_open_iconic_all_2x_t);
        u8g2.drawGlyph(70,5+2*8,127);
      //天气图标
      u8g2.setFont(u8g2_font_open_iconic_all_2x_t);
        u8g2.drawGlyph(130,5+2*8,102);
      //配网图标
        u8g2.setFont(u8g2_font_open_iconic_all_2x_t);
        u8g2.drawGlyph(130,65+2*8,129);

      switch (chooes) {
       case 1:
        display.drawRoundRect(0, 2, 40, 42, 5, GxEPD_BLACK);
        break;
       case 2:
        display.drawRoundRect(57, 2, 40, 42, 5, GxEPD_BLACK);
        break;
       case 3:
        display.drawRoundRect(120, 2, 32, 42, 5, GxEPD_BLACK);
        break;
       case 4:
        display.drawRoundRect(120, 62, 32, 42, 5, GxEPD_BLACK);
        break;
      }

    }

  }
}

void showCH(int x, int y, char* contest) {
  u8g2.drawUTF8(x, y,contest);
}

String cuttxt(String contest, int a, int b) {

    if (a < 1 || b < a || contest.length() == 0) {
      return "";
    }

    const char* str = contest.c_str();
    int len = contest.length();
    int charCount = 0;
    int startPos = -1;
    int endPos = len;

    // 扫描UTF-8字符串找到起始和结束位置
    for (int i = 0; i < len; i++) {
      uint8_t byte = (uint8_t)str[i];

      // 检测UTF-8字符开始
      bool isCharStart = false;
      if (byte < 0x80) {
        // ASCII字符 (0xxxxxxx)
        isCharStart = true;
      } else if ((byte & 0xE0) == 0xC0) {
        // 2字节UTF-8开始 (110xxxxx)
        isCharStart = true;
      } else if ((byte & 0xF0) == 0xE0) {
        // 3字节UTF-8开始 (1110xxxx) - 中文字符
        isCharStart = true;
      } else if ((byte & 0xF8) == 0xF0) {
        // 4字节UTF-8开始 (11110xxx)
        isCharStart = true;
      }
      // 续字节 (10xxxxxx) 不计数

      if (isCharStart) {
        charCount++;

        // 标记起始位置
        if (charCount == a && startPos == -1) {
          startPos = i;
        }

        // 标记结束位置
        if (charCount == b + 1) {
          endPos = i;
          break;
        }
      }
    }

    // 如果没找到起始位置，返回空字符串
    if (startPos == -1) {
      return "";
    }

    // 提取子字符串
    return contest.substring(startPos, endPos);

}

void SX2() {
  if (ZT != 1) {
    if (CSX == 10) {
      QSX();
      CSX = 0;

    } else {
      JSX(0, 0, 255, 255);
      CSX++;

    }
    SX = 1;

  } else {
    if (CSX == 15) {
      QSX();
      CSX = 0;

    } else {
      JSX(0, 0, 255, 255);
      CSX++;

    }
    SX = 1;

  }
}

void JSX(int x, int y, int w, int h) {
  display.setPartialWindow(x, y, w, h);
  display.display(true);
}

String getServerVersion() {
    HTTPClient http;
    http.begin(VERSION_URL);

    int httpCode = http.GET();
    if (httpCode != HTTP_CODE_OK) {
      http.end();
      return "";
    }

    String ver = http.getString();
    http.end();
    ver.trim(); // 去掉空格、换行

    return ver;
}

char* Sou(int i) {

    static char name[256]; // 静态数组保证返回后内存有效
    name[0] = '\0'; // 初始化为空字符串

    FsFile root = sd.open("/");
    if(!root || !root.isDir()) {
      return name;
    }

    FsFile file;
    int count = 0;
    while((file = root.openNextFile())) { // 修改为直接检查文件是否有效
      if(count++ == i) {
        file.getName(name, sizeof(name));
        file.close();
        break;
      }
      file.close();
    }

    root.close();
    return name;

}

void attachDoubleClick32() {
  QSX();

}

void App() {
  //设置中文字体字号15
  u8g2.setFont(u8g2_font_wqy15_t_gb2312);
  if (Mode == 1) {
      if (ZT == 0) {
        P = 1;
        if (SDcard == 1) {
          if (chooes <= 7) {
            while (i <= 7) {
              WB[i] = Sou(i);
              if (i >= 2) {
                showCH(2, P * 20, changetxt(WB[i]));

              }
              i++;
              P++;
            }
            if (chooes == 1) {
              chooes = 2;

            }
            switch (chooes) {
             case 1:
              break;
             case 2:
              display.drawFastHLine(0, 42, 100, GxEPD_BLACK);
              break;
             case 3:
              display.drawFastHLine(0, 62, 100, GxEPD_BLACK);
              break;
             case 4:
              display.drawFastHLine(0, 82, 100, GxEPD_BLACK);
              break;
             case 5:
              display.drawFastHLine(0, 102, 100, GxEPD_BLACK);
              break;
             case 6:
              display.drawFastHLine(0, 122, 100, GxEPD_BLACK);
              break;
             case 7:
              display.drawFastHLine(0, 142, 100, GxEPD_BLACK);
              break;
            }

          }
          if (chooes > 7 && chooes <= 13) {
            while (i <= 7) {
              WB[i] = Sou(i + 6);
              showCH(2, P * 20, changetxt(WB[i]));
              i++;
              P++;
            }
            switch (chooes - 7) {
             case 1:
              display.drawFastHLine(0, 42, 100, GxEPD_BLACK);
              break;
             case 2:
              display.drawFastHLine(0, 62, 100, GxEPD_BLACK);
              break;
             case 3:
              display.drawFastHLine(0, 82, 100, GxEPD_BLACK);
              break;
             case 4:
              display.drawFastHLine(0, 102, 100, GxEPD_BLACK);
              break;
             case 5:
              display.drawFastHLine(0, 122, 100, GxEPD_BLACK);
              break;
             case 6:
              display.drawFastHLine(0, 142, 100, GxEPD_BLACK);
              break;
            }

          }
          if (chooes > 13) {
            while (i <= 7) {
              WB[i] = Sou(i + 12);
              showCH(2, P * 20, changetxt(WB[i]));
              i++;
              P++;
            }
            switch (chooes - 13) {
             case 1:
              display.drawFastHLine(0, 42, 100, GxEPD_BLACK);
              break;
             case 2:
              display.drawFastHLine(0, 62, 100, GxEPD_BLACK);
              break;
             case 3:
              display.drawFastHLine(0, 82, 100, GxEPD_BLACK);
              break;
             case 4:
              display.drawFastHLine(0, 102, 100, GxEPD_BLACK);
              break;
             case 5:
              display.drawFastHLine(0, 122, 100, GxEPD_BLACK);
              break;
             case 6:
              display.drawFastHLine(0, 142, 100, GxEPD_BLACK);
              break;
            }

          }

        } else {
          showCH(10, 50, "TF卡读取失败");
          showCH(0, 70, "请先断电然后插入TF卡");
          showCH(10, 90, "插入TF卡后重启设备");

        }
        //设置中文字体字号15
        u8g2.setFont(u8g2_font_wqy12_t_gb2312);
        showCH(20, 10, "仅支持UTF-8 编码");
        showCH(20, 22, "目前仅能同时阅读20本书");
        u8g2.setFont(u8g2_font_open_iconic_all_2x_t);
          u8g2.drawGlyph(2,10+1*8,171);
        display.drawFastHLine(0, 25, 255, GxEPD_BLACK);
        //设置中文字体字号15
        u8g2.setFont(u8g2_font_wqy12_t_gb2312);
        u8g2.setFont(u8g2_font_open_iconic_all_2x_t);
          u8g2.drawGlyph(2,10+1*8,171);
        display.drawFastHLine(0, 25, 255, GxEPD_BLACK);

      }
      if (ZT == 1) {
        //设置中文字体字号15
        u8g2.setFont(u8g2_font_wqy15_t_gb2312);
        clearEPD();
        display.drawFastHLine(0, 15, 255, GxEPD_BLACK);
        showCH(58, 12, changetxt(String(rtc.GetDateTime().Hour()) + String(":") + String(rtc.GetDateTime().Minute())));
        showCH(2, 12, changetxt(String(K)));
        showCH(120, 12, changetxt(String(String((getBatteryPercent()))) + String("%")));
        if (BT == 2) {
           u8g2.setFont(u8g2_font_open_iconic_all_1x_t);
            u8g2.drawGlyph(130,0+1*8,94);

        }
        if (K != 0) {
          RWB = String((opnetxt(Sou(chooes), K * 70, 70)));

        } else {
          RWB = String((opnetxt(Sou(chooes), 1, 70)));

        }
        //设置中文字体字号15
        u8g2.setFont(u8g2_font_wqy15_t_gb2312);
        showCH(2, 30, changetxt(cuttxt(RWB, 1, 10)));
        showCH(2, 50, changetxt(cuttxt(RWB, 11, 20)));
        showCH(2, 70, changetxt(cuttxt(RWB, 21, 30)));
        showCH(2, 90, changetxt(cuttxt(RWB, 31, 40)));
        showCH(2, 110, changetxt(cuttxt(RWB, 41, 50)));
        showCH(2, 130, changetxt(cuttxt(RWB, 51, 60)));
        showCH(2, 150, changetxt(cuttxt(RWB, 61, 70)));
        P++;
        if (P >= 11) {
          (createFileWithContent("Save", Sou(chooes), K));
          P = 1;

        }

      }
      if (ZT == 2) {
        clearEPD();
        //设置中文字体字号15
        u8g2.setFont(u8g2_font_wqy12_t_gb2312);
        showCH(2, 60, changetxt(String("当前文本") + String(Sou(chooes))));
        showCH(2, 40, "阅读进度调整");
        showCH(2, 80, changetxt(String("当前页数：") + String(K) + String("页")));

      }

    }
    if (Mode == 2) {
      //设置中文字体字号12
      u8g2.setFont(u8g2_font_wqy12_t_gb2312);
      showCH(10, 30, "制作中。。。");
      showCH(10, 60, "请留意更新");

    }
    if (Mode == 3) {
      //设置中文字体字号12
      u8g2.setFont(u8g2_font_wqy12_t_gb2312);
      showCH(5, 20, "请连接WIFI‘电子书’");
      showCH(5, 40, "连接后使用浏览器访问");
      showCH(5, 60, "192.168.4.1");
      showCH(5, 90, "按照网页提示进行配网");
      showCH(5, 110, "重启后将自动连接到网络");
      //刷新界面
      display.nextPage();
      // 一键配网（请让其只执行一次）
      wm.setEnableConfigPortal(1);
       wm.setConfigPortalTimeout(60);
      wm.startConfigPortal("电子书");
      wm.autoConnect("电子书联网");
      Mode = 0;
      page = 0;
      SX = 0;

    }
    if (Mode == 4) {
      //设置中文字体字号15
      u8g2.setFont(u8g2_font_wqy12_t_gb2312);
      showCH(10, 12, "关于");
      showCH(0, 33, "系统更新");
      showCH(0, 53, "时间校准");
      display.drawFastVLine(52, 0, 255, GxEPD_BLACK);
      switch (chooes) {
       case 1:
        display.drawRoundRect(0, 0, 50, 20, 1, GxEPD_BLACK);
        showCH(55, 10, "作者：Cwolf-Cc");
        showCH(55, 25, "B站Cwolf");
        showCH(55, 40, changetxt(String("当前版本：") + String(BINID)));
        break;
       case 2:
        display.drawRoundRect(0, 20, 50, 20, 1, GxEPD_BLACK);
        showCH(55, 10, changetxt(String("当前版本：") + String(BINID)));
        showCH(55, 30, changetxt(String("最新版本：") + String(Bin)));
        showCH(55, 50, "若搜索时间过长");
        showCH(55, 70, "可在B站搜索Cwolf");
        showCH(55, 90, "手动下载固件");
        showCH(55, 110, "使用配网界面更新");
        break;
       case 3:
        display.drawRoundRect(0, 40, 50, 20, 1, GxEPD_BLACK);
        showCH(55, 10, "单击确认键校准");
        break;
       case 4:
        display.drawRoundRect(0, 60, 50, 20, 1, GxEPD_BLACK);
        break;
      }
      SX = 0;

    }
}

int getBatteryPercent() {
  const int SAMPLES    = 30;       // 采样次数（越多越平滑）
      const float ALPHA    = 0.05;     // 滤波系数（0~1，越小滤波越强，建议0.02~0.1）
      const int DEADBAND   = 1;        // 百分比变化死区（小于此值不更新，消除微小跳变）

      static float smoothAdc = -1.0;   // 静态变量，保存平滑后的ADC值
      static int lastPercent  = -1;    // 上一次显示的百分比（用于死区）

      int pin = 35;
      long sum = 0;
      int minVal = 4095, maxVal = 0;

      // 1. 多次采样，去掉一个最大值和一个最小值后求平均
      for (int i = 0; i < SAMPLES; i++) {
          int val = analogRead(pin);
          sum += val;
          if (val < minVal) minVal = val;
          if (val > maxVal) maxVal = val;
          delay(2);  // 短暂延时让ADC稳定
      }
      sum = sum - minVal - maxVal;
      float rawAdc = (float)sum / (SAMPLES - 2);

      // 2. 一阶低通滤波（指数移动平均）
      if (smoothAdc < 0) {
          smoothAdc = rawAdc;           // 首次初始化
      } else {
          smoothAdc = smoothAdc * (1.0f - ALPHA) + rawAdc * ALPHA;
      }

      // 3. 将平滑后的ADC值映射为锂电池电压（沿用您原有的校准参数）
      //    原 mapfloat 逻辑：ADC 2150 -> 3.6V, ADC 2500 -> 4.2V
      float voltage = 3.6f + (smoothAdc - 2150.0f) * (4.2f - 3.6f) / (2500.0f - 2150.0f);

      // 4. 转换为原始百分比（完全保留您原有的计算公式）
      int percent = (int)(voltage * 166 - 597) + 42;

      // 5. 限制百分比范围 0~100
      if (percent > 100) percent = 100;
      if (percent < 0)   percent = 0;

      // 6. 死区判断：只有当变化超过 DEADBAND 时才更新显示值
      if (lastPercent >= 0 && abs(percent - lastPercent) <= DEADBAND) {
          return lastPercent;          // 变化太小，返回旧值
      }
      lastPercent = percent;
      return percent;
}

String opnetxt(String name, int a, int l) {
  if (name.isEmpty() || a < 1 || l < 1) {
      Serial.print("[opnetxt] 无效参数：name=");
      Serial.print(name);
      Serial.print(" a=");
      Serial.print(a);
      Serial.print(" l=");

      return "";
    }

    // 构建文件路径
    char txtPath[64];
    char idxPath[64];
    sprintf(txtPath, "/%s", name.c_str());
    sprintf(idxPath, "/Save/%s.idx2", name.c_str()); // 新索引后缀.idx2

    // 打开文本文件
    SdFile txtFile;
    if (!txtFile.open(txtPath, O_READ)) {

      return "";
    }
    uint64_t fileSize = txtFile.fileSize();
    if (fileSize == 0) {
      txtFile.close();
  
      return "";
    }

    // --------------------- 1. 检查并生成索引（仅第一次运行） ---------------------
    SdFile idxFile;
    bool indexExists = sd.exists(idxPath);
    if (!indexExists) {

      if (!sd.exists("/Save")) sd.mkdir("/Save"); // 确保Save目录存在

      if (!idxFile.open(idxPath, O_WRITE | O_CREAT | O_TRUNC)) {
 
        txtFile.close();
        return "";
      }

      // 生成索引：遍历文本，每70个字符记录一次字节偏移
      uint32_t charCount = 0;
      uint64_t currentOffset = 0;
      uint8_t buffer[2048];
      uint32_t pageIndex = 0;

      // 先写入第0页的偏移（0）
      uint32_t firstOffset = 0;
      idxFile.write((uint8_t*)&firstOffset, 4);
      pageIndex++;

      while (currentOffset < fileSize) {
        int bytesToRead = min((uint64_t)2048, fileSize - currentOffset);
        int bytesRead = txtFile.read(buffer, bytesToRead);
        if (bytesRead <= 0) break;

        for (int i = 0; i < bytesRead; ) {
          uint8_t firstByte = buffer[i];
          int utf8Len = 0;

          // 计算UTF-8字符长度
          if ((firstByte & 0x80) == 0x00) utf8Len = 1;
          else if ((firstByte & 0xE0) == 0xC0) utf8Len = 2;
          else if ((firstByte & 0xF0) == 0xE0) utf8Len = 3;
          else if ((firstByte & 0xF8) == 0xF0) utf8Len = 4;
          else { i++; continue; }

          if (i + utf8Len > bytesRead) {
            txtFile.seekSet(currentOffset + i);
            currentOffset = txtFile.curPosition();
            break;
          }

          charCount++;
          // 每70个字符（一页）记录一次偏移
          if (charCount % 70 == 0) {
            uint32_t pageOffset = currentOffset + i + utf8Len;
            idxFile.write((uint8_t*)&pageOffset, 4);
            pageIndex++;
          }

          i += utf8Len;
          yield(); // 避免看门狗超时
        }
        currentOffset = txtFile.curPosition();
        yield();
      }

      idxFile.close();
      Serial.print("[opnetxt] 索引生成完成！共 ");
      Serial.print(pageIndex);
  
    }

    // --------------------- 2. 加载索引并定位目标页 ---------------------
    // 计算目标页码（从1开始）
    uint32_t targetPage = (a - 1) / 70;
    if (!indexExists) {
      // 刚生成完索引，重新打开文本文件
      txtFile.seekSet(0);
    }

    // 打开索引文件
    if (!idxFile.open(idxPath, O_READ)) {

      txtFile.close();
      return "";
    }

    // 直接跳转到目标页的索引位置：targetPage * 4
    uint32_t idxOffset = targetPage * 4;
    if (!idxFile.seekSet(idxOffset)) {
    
      idxFile.close();
      txtFile.close();
      return "";
    }

    // 读取4字节的文本偏移
    uint32_t txtOffset;
    idxFile.read((uint8_t*)&txtOffset, 4);
    idxFile.close();

    // --------------------- 3. 从文本文件读取内容 ---------------------
    txtFile.seekSet(txtOffset);

    // 读取l个字符（默认70）
    String result;
    result.reserve(l * 4);
    uint32_t readCount = 0;
    uint64_t currentPos = txtOffset;
    uint8_t buffer[2048];

    while (currentPos < fileSize && readCount < l) {
      int bytesToRead = min((uint64_t)2048, fileSize - currentPos);
      int bytesRead = txtFile.read(buffer, bytesToRead);
      if (bytesRead <= 0) break;

      for (int i = 0; i < bytesRead && readCount < l; ) {
        uint8_t firstByte = buffer[i];
        int utf8Len = 0;

        if ((firstByte & 0x80) == 0x00) utf8Len = 1;
        else if ((firstByte & 0xE0) == 0xC0) utf8Len = 2;
        else if ((firstByte & 0xF0) == 0xE0) utf8Len = 3;
        else if ((firstByte & 0xF8) == 0xF0) utf8Len = 4;
        else { i++; continue; }

        if (i + utf8Len > bytesRead) {
          txtFile.seekSet(currentPos + i);
          currentPos = txtFile.curPosition();
          break;
        }

        // 追加字符到结果
        for (int j = 0; j < utf8Len; j++) {
          result += (char)buffer[i + j];
        }
        readCount++;
        i += utf8Len;
        yield();
      }
      currentPos = txtFile.curPosition();
      yield();
    }

    txtFile.close();
    Serial.print("[opnetxt] 读取完成：第 ");
    Serial.print(targetPage + 1);
    Serial.print(" 页，实际读取 ");
    Serial.print(readCount);
 

    return result;
}

void setup() {
  BT = 0;
  VERSION_URL = "https://cwolf-ux.github.io/eBook-bin/version.txt";
  WZ = 0;
  SDcard = 0;
  page = 1;
  Mode = 0;
  chooes = 1;
  ZT = 0;
  i = 1;
  P = 0;
  K = 1;
  RWB = "N/A";
  TQGX = 0;
  CSX = 0;
  SX = 0;
  LED = 0;
  Bin = "未获取";
  cmd = "";
  rtc.Begin();
  NTP.setInterval (600);
  NTP.setNTPTimeout (1500);
  NTP.begin (ntpServer, timeZone, false);
  Serial.begin(9600);
  forecast.config("Scl5KX2P01aG2qIue", "ip", "c", "zh-Hans");
  weatherNow.config("Scl5KX2P01aG2qIue", "ip", "c", "zh-Hans");
  // 一键配网初始化
  // （调试时请打开串口）
  // sd卡初始化

  //联用初始化
    display.init();
    u8g2.begin(display);
    u8g2.setFontMode(1);
    u8g2.setForegroundColor(GxEPD_BLACK);
    u8g2.setBackgroundColor(GxEPD_WHITE);
    display.setFullWindow();
    display.firstPage();
  pinMode(32, INPUT_PULLUP);
  pinMode(26, INPUT_PULLUP);
  pinMode(34, INPUT_PULLUP);
  pinMode(35, INPUT);
  pinMode(25, OUTPUT);
  // 天气页面更新相关数据
  // 天气页面更新相关数据
  // 天气页面更新相关数据
  // 为0即在文本选择界面为1则已经开始阅读
  // 阅读进度
  //设置中文字体字号15
  u8g2.setFont(u8g2_font_wqy15_t_gb2312);
  showCH(50, 60, "BY:Cwolf");
  showCH(50, 80, changetxt(BINID));
  SX2();
  SDcard = sd.begin(4,SD_SCK_MHZ(16));;
  wm.setEnableConfigPortal(false);// 完全禁用配置门户
  wm.setConfigPortalTimeout(60);
  wm.setConnectTimeout(3);
  res=wm.autoConnect("电子书联网");
  SX = 0;
  clearEPD();
  button33.attachDoubleClick(attachDoubleClick33);
  button26.attachLongPressStart(attachLongPressStart26);
  button32.attachLongPressStart(attachLongPressStart32);
  button33.attachDuringLongPress(attachDuringLongPress33);
  button26.attachClick(attachClick26);
  timer.setInterval(60000L, Simple_timer_1);

  timer.setInterval(300000L, Simple_timer_2);

  button26.attachDuringLongPress(attachDuringLongPress26);
  button32.attachClick(attachClick32);
  button33.attachClick(attachClick33);
  button26.attachDoubleClick(attachDoubleClick26);
  button32.attachDoubleClick(attachDoubleClick32);
}

void loop() {
  // 确认
  button33.tick();
  // 右键
  button26.tick();
  // 左键
  button32.tick();


  // 确认
  button33.tick();
  // 右键
  button26.tick();
  // 天气10分钟刷新一次
  timer.run();

  // 天气10分钟刷新一次
  timer.run();

  // 右键
  button26.tick();
  // 左键
  button32.tick();
  // 确认
  button33.tick();
  // 右键
  button26.tick();
  // 左键
  button32.tick();
  if (SX == 0) {
    Mode0();
    App();
    SX2();

  }
  delay(20);

}
