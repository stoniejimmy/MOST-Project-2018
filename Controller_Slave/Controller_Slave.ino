//2018 科技部大專學生研究計畫
//智能律動電動載具之控制研究
//National Koahsiung University of Science and Technology, Taiwan, R.O.C.
//Code by Stonie Tseng
//Facility Advisor: Professor Po-Wen Hsueh

//Created Date: 2018/4/2
//Last Modified: 2018/8/8

//引用Wire資料庫來使用i2c與主控制器連線
#include <Wire.h>

//顯示數字及燈號的變數設定
int seg_state = 0; //7段顯示器
int led_state_1 = 0; //右上方系統指示燈
int led_state_2 = 0; //右下方馬達狀態指示燈

//要透過i2c傳送的數值
int val1 = 0; //Numbers 0~9
int val2 = 0; //1=RED 2=GREEN 3=BLUE
int val3 = 0; //1=RED 2=GREEN 3=BLUE


void setup() {
  //開啟序列埠以做監控
  Serial.begin(9600);
  //準備Wire以做i2c傳送及接收，並在通道中定義為1號主機
  Wire.begin(1);
  //隨時有request訊號就丟出數值
  Wire.onRequest(requestEvent);
}

void loop() {
  //測試訊號
  seg_state = 2;
  led_state_1 = 2;
  led_state_2 = 2;
}


void requestEvent()
{
  val1 = seg_state;
  val2 = led_state_1;
  val3 = led_state_2;

  Serial.print("val1: ");
  Serial.println(val1);
  Serial.print("val2: ");
  Serial.println(val2);
  Serial.print("val3: ");
  Serial.println(val3);

  Wire.write(val1); //下位元
  Wire.write(val1 >> 8); //上位元

  Wire.write(val2); //下位元
  Wire.write(val2 >> 8); //上位元

  Wire.write(val3); //下位元
  Wire.write(val3 >> 8); //上位元
}
