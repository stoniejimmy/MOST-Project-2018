/*
  接腳說明:
  七段顯示器的74LS47
  正電:紅線1
  負電:黑線2
  A點:黃線3
  B點:紫線4
  C點:白線5
  D點:綠線6
  Switch點:橘線7

  狀態LED
  上紅:綠線-藍
  上綠:橘線-橘
  上籃:白線-白ˊ
  下藍:紫線-黑
*/


#include <Wire.h>

int num = 0;

int seg_rst = 13;
int seg_a = A0;
int seg_b = A3;
int seg_c = A1;
int seg_d = A2;

int ur = 7;
int ug = 8;
int ub = 9;
int lr = 10;
int lg = 11;
int lb = 12;

volatile int val1_a; volatile int val1_b; volatile int val1;
volatile int val2_a; volatile int val2_b; volatile int val2;
volatile int val3_a; volatile int val3_b; volatile int val3;

int seg_state = 0;
int led_state_1 = 0;
int led_state_2 = 0;

void setup()
{
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output

  pinMode(seg_a, OUTPUT); //黃色線
  pinMode(seg_b, OUTPUT); //紫色線
  pinMode(seg_c, OUTPUT); //白色線
  pinMode(seg_d, OUTPUT); //綠色線
  pinMode(seg_rst, OUTPUT); // //橘色線
  pinMode(ur, OUTPUT);
  pinMode(ug, OUTPUT);
  pinMode(ub, OUTPUT);
  pinMode(lr, OUTPUT);
  pinMode(lg, OUTPUT);
  pinMode(lb, OUTPUT);

  digitalWrite(ur, HIGH); digitalWrite(lr, HIGH); delay(100); digitalWrite(ur, LOW); digitalWrite(lr, LOW);
  digitalWrite(ug, HIGH); digitalWrite(lg, HIGH); delay(100); digitalWrite(ug, LOW); digitalWrite(lg, LOW);
  digitalWrite(ub, HIGH); digitalWrite(lb, HIGH); delay(100); digitalWrite(ub, LOW); digitalWrite(lb, LOW);
  digitalWrite(ur, HIGH);
  digitalWrite(seg_rst, HIGH); digitalWrite(seg_a, LOW); digitalWrite(seg_b, LOW); digitalWrite(seg_c, LOW); digitalWrite(seg_d, LOW); delay(100); digitalWrite(seg_rst, LOW);
  digitalWrite(seg_a, HIGH); digitalWrite(seg_b, LOW); digitalWrite(seg_c, LOW); digitalWrite(seg_d, LOW); delay(100); //1
  digitalWrite(seg_a, LOW); digitalWrite(seg_b, HIGH); digitalWrite(seg_c, LOW); digitalWrite(seg_d, LOW); delay(100); //2
  digitalWrite(seg_a, HIGH); digitalWrite(seg_b, HIGH); digitalWrite(seg_c, LOW); digitalWrite(seg_d, LOW); delay(100); //3
  digitalWrite(seg_a, LOW); digitalWrite(seg_b, LOW); digitalWrite(seg_c, HIGH); digitalWrite(seg_d, LOW); delay(100); //4
  digitalWrite(seg_a, HIGH); digitalWrite(seg_b, LOW); digitalWrite(seg_c, HIGH); digitalWrite(seg_d, LOW); delay(100); //5
  digitalWrite(seg_a, LOW); digitalWrite(seg_b, HIGH); digitalWrite(seg_c, HIGH); digitalWrite(seg_d, LOW); delay(100); //6
  digitalWrite(seg_a, HIGH); digitalWrite(seg_b, HIGH); digitalWrite(seg_c, HIGH); digitalWrite(seg_d, LOW); delay(100); //7
  digitalWrite(seg_a, LOW); digitalWrite(seg_b, LOW); digitalWrite(seg_c, LOW); digitalWrite(seg_d, HIGH); delay(100); //8
  digitalWrite(seg_a, HIGH); digitalWrite(seg_b, LOW); digitalWrite(seg_c, LOW); digitalWrite(seg_d, HIGH); delay(100); //9
}



void loop()
{
  Wire.requestFrom(11, 6);
  while (Wire.available())
  {
    val1_a = Wire.read(); val1_b = Wire.read();
    val1 = (val1_b << 8) | val1_a;
    val2_a = Wire.read(); val2_b = Wire.read();
    val2 = (val2_b << 8) | val2_a;
    val3_a = Wire.read(); val3_b = Wire.read();
    val3 = (val3_b << 8) | val3_a;
  }
  seg_state = val1;
  led_state_1 = val2;
  led_state_2 = val3;
  Serial.print("val1:"); Serial.println(val1);
  Serial.print("val2:"); Serial.println(val2);
  Serial.print("val3:"); Serial.println(val3);
  Serial.println("");

  Serial.print("Received 7 Segment Display Value: ");
  Serial.println(seg_state);

  Serial.print("Received LED1 Value: ");
  Serial.println(led_state_1);

  Serial.print("Received LED2 Value: ");
  Serial.println(led_state_2);

  if (seg_state == 0) {
    digitalWrite(seg_rst, HIGH); digitalWrite(seg_a, LOW); digitalWrite(seg_b, LOW); digitalWrite(seg_c, LOW); digitalWrite(seg_d, LOW);
  }
  else if (seg_state == 1) {
    digitalWrite(seg_a, HIGH); digitalWrite(seg_b, LOW); digitalWrite(seg_c, LOW); digitalWrite(seg_d, LOW);
  }
  else if (seg_state == 2) {
    digitalWrite(seg_a, LOW); digitalWrite(seg_b, HIGH); digitalWrite(seg_c, LOW); digitalWrite(seg_d, LOW);
  }
  else if (seg_state == 3) {
    digitalWrite(seg_a, HIGH); digitalWrite(seg_b, HIGH); digitalWrite(seg_c, LOW); digitalWrite(seg_d, LOW);
  }
  else if (seg_state == 4) {
    digitalWrite(seg_a, LOW); digitalWrite(seg_b, LOW); digitalWrite(seg_c, HIGH); digitalWrite(seg_d, LOW);
  }
  else if (seg_state == 5) {
    digitalWrite(seg_a, HIGH); digitalWrite(seg_b, LOW); digitalWrite(seg_c, HIGH); digitalWrite(seg_d, LOW);
  }
  else if (seg_state == 6) {
    //digitalWrite(seg_rst, LOW); digitalWrite(seg_a, LOW); digitalWrite(seg_b, LOW); digitalWrite(seg_c, LOW); digitalWrite(seg_d, LOW);
    digitalWrite(seg_a, LOW); digitalWrite(seg_b, HIGH); digitalWrite(seg_c, HIGH); digitalWrite(seg_d, LOW);
  }
  if (seg_state == 7) {
    //digitalWrite(seg_rst, LOW); digitalWrite(seg_a, LOW); digitalWrite(seg_b, LOW); digitalWrite(seg_c, LOW); digitalWrite(seg_d, LOW);
    digitalWrite(seg_a, HIGH); digitalWrite(seg_b, HIGH); digitalWrite(seg_c, HIGH); digitalWrite(seg_d, LOW);
  }
  else if (seg_state == 8) {
    //digitalWrite(seg_rst, LOW); digitalWrite(seg_a, LOW); digitalWrite(seg_b, LOW); digitalWrite(seg_c, LOW); digitalWrite(seg_d, LOW);
    digitalWrite(seg_a, LOW); digitalWrite(seg_b, LOW); digitalWrite(seg_c, LOW); digitalWrite(seg_d, HIGH);
  }
  else if (seg_state == 9) {
    //digitalWrite(seg_rst, LOW); digitalWrite(seg_a, LOW); digitalWrite(seg_b, LOW); digitalWrite(seg_c, LOW); digitalWrite(seg_d, LOW);
    digitalWrite(seg_a, HIGH); digitalWrite(seg_b, LOW); digitalWrite(seg_c, LOW); digitalWrite(seg_d, HIGH);
  }
  else if (seg_state == 10) {
    digitalWrite(seg_rst, LOW); digitalWrite(seg_a, LOW); digitalWrite(seg_b, LOW); digitalWrite(seg_c, LOW); digitalWrite(seg_d, LOW);
    digitalWrite(ur, LOW); digitalWrite(ug, LOW); digitalWrite(ub, LOW);
    digitalWrite(lr, LOW); digitalWrite(lg, LOW); digitalWrite(lb, LOW);
    digitalWrite(ur, HIGH); delay(250); digitalWrite(ur, LOW);
  }
  if (led_state_1 == 1) {
    digitalWrite(ur, LOW); digitalWrite(ug, LOW); digitalWrite(ub, LOW);
    digitalWrite(ur, HIGH);
  }
  else if (led_state_1 == 2) {
    digitalWrite(ur, LOW); digitalWrite(ug, LOW); digitalWrite(ub, LOW);
    digitalWrite(ug, HIGH);
  }
  else if (led_state_1 == 3) {
    digitalWrite(ur, LOW); digitalWrite(ug, LOW); digitalWrite(ub, LOW);
    digitalWrite(ub, HIGH);
  }

  if (led_state_2 == 1) {
    digitalWrite(lr, LOW); digitalWrite(lg, LOW); digitalWrite(lb, LOW);
    digitalWrite(lr, HIGH);
  }
  else if (led_state_2 == 2) {
    digitalWrite(lr, LOW); digitalWrite(lg, LOW); digitalWrite(lb, LOW);
    digitalWrite(lg, HIGH);
  }
  else if (led_state_2 == 3) {
    digitalWrite(lr, LOW); digitalWrite(lg, LOW); digitalWrite(lb, LOW);
    digitalWrite(lb, HIGH);
  }
}
