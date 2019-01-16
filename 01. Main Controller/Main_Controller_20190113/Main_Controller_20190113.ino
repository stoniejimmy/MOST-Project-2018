//科計部計畫 主控制器程式
//最後更新: 20190113
//實驗地點: NKUST T211-1

#include <Wire.h>

/*
  七段顯示器接腳說明:
  七段顯示器的74LS47
  正電:紅線-1-紅線 5V
  負電:黑線-2-棕線 GND
  A點:黃線-3-黑線 => Pin 41
  B點:紫線-4-白線 => Pin 42
  C點:白線-5-灰線 => Pin 43
  D點:綠線-6-紫線 => Pin 44
  Switch點:橘線-7-藍線 => Pin 45
*/
int seg_state = 0; //七段顯示器數值
int seg_a = 41;
int seg_b = 42;
int seg_c = 43;
int seg_d = 44;
int seg_rst = 45;

/*
  狀態LED接腳說明:
  上紅:綠線-藍線 => Pin 47
  上綠:橘線-橘線 => Pin 48
  上籃:白線-白線 => Pin 49
  下紅:紅線-紅線 => Pin 50
  下綠:黃線-棕線 => Pin 51
  下藍:紫線-黑線 => Pin 52
*/
int led_state_1 = 0;
int led_state_2 = 0;
int ur = 47;
int ug = 48;
int ub = 49;
int lr = 50;
int lg = 51;
int lb = 52;

/*
  安全緊急開關
  接於46腳位，是使用自鎖開關
  按下: 導通狀態=>中斷loop執行
  沒按下: 斷電狀態=>loop正常執行
  安全開關指示燈 紅色Pin13 綠色Pin12 藍色Pin11
*/
int safety_switch_data = 0;
int safety_switch_state = 0; //0=Initial 1=Unsafe, 2=Safe
int safety_red = 13;
int safety_green = 12;
int safety_blue = 11;

/*
  油門訊號
  紅線(橘線)5V 黑線GND 綠線Signal
  綠色訊號線接到A15
*/
int throttle_pin = A15;
int throttle_data = 0;
int throttle_level = 0;

/*
  煞車訊號
  黃線5V 綠線Signal
  綠色訊號線接到A14
*/
int break_pin = A14;
int break_data = 0;
int break_state = 0; //0=Initial 1=Break, 2=Normal

/*
  馬達控制器PWM訊號
  綠線Signal接在PWM Pin9
*/
int PWM_pin = 9;
int pwm_percent = 0; //2.55 * pwm_percent
int pwm_value = 127.5; //要輸出的真實value

/*
  電壓感測器
  電池: A6 馬達: A7 Arduino: A8
*/
int voltage_read1;
float voltage_1;
int voltage_sensor_1 = A6;
int voltage_read2;
float voltage_2;
int voltage_sensor_2 = A7;
int voltage_read3;
float voltage_3;
int voltage_sensor_3 = A8;
/*
  車燈控制
*/
int head_light = 25;
int head_light_state = 0; // 0=OFF 1=HIGH
int left_turn_indicator = 26;
int right_turn_indicator = 27;
int turn_indicator_state = 0; //0=off 1=left 2=right 3=both


/*
  藍芽模組
  TX:14 RX:15
*/
#include <SoftwareSerial.h>
SoftwareSerial I2CBT(2, 3); // TX:3, RX:4
byte serialA;
int BT_Speed = 0;
int BT_Battery_Voltage = 0;
int BT_Kilos = 0;
int BT_Sys_State = 0;
int BT_Light = 0;
int BT_Motor_Voltage = 0;
int BT_Throttle = 0;
int BT_Angle = 0;

/*
  I2C
  rpm Calculator: 11
*/
volatile int rpm_a; volatile int rpm_b; volatile int rpm;
float Speed = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Setup Running.....");

  Wire.begin();

  I2CBT.begin(9600);

  pinMode(seg_a, OUTPUT);
  pinMode(seg_b, OUTPUT);
  pinMode(seg_c, OUTPUT);
  pinMode(seg_d, OUTPUT);
  pinMode(seg_rst, OUTPUT);

  pinMode(ur, OUTPUT);
  pinMode(ug, OUTPUT);
  pinMode(ub, OUTPUT);
  pinMode(lr, OUTPUT);
  pinMode(lg, OUTPUT);
  pinMode(lb, OUTPUT);

  pinMode(safety_red, OUTPUT);
  pinMode(safety_green, OUTPUT);
  pinMode(safety_blue, OUTPUT);

  pinMode(head_light, OUTPUT);
  pinMode(left_turn_indicator, OUTPUT);
  pinMode(right_turn_indicator, OUTPUT);

  // 開始七段顯示器測試
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
  digitalWrite(seg_rst, HIGH); digitalWrite(seg_a, LOW); digitalWrite(seg_b, LOW); digitalWrite(seg_c, LOW); digitalWrite(seg_d, LOW);

  digitalWrite(ur, HIGH); digitalWrite(lr, HIGH); delay(100); digitalWrite(ur, LOW); digitalWrite(lr, LOW);
  digitalWrite(ug, HIGH); digitalWrite(lg, HIGH); delay(100); digitalWrite(ug, LOW); digitalWrite(lg, LOW);
  digitalWrite(ub, HIGH); digitalWrite(lb, HIGH); delay(100); digitalWrite(ub, LOW); digitalWrite(lb, LOW);
  digitalWrite(ur, HIGH);
  Serial.println("Setup Ended");

  digitalWrite(left_turn_indicator, HIGH);
  delay(735);
  digitalWrite(left_turn_indicator, LOW);
  delay(100);
}

void loop() {
  safety_switch_state = 0; //Overwirte in safety_switch_detection if its safe.
  safety_switch_detection();
  safety_switch_led_update();
  voltage_detection();
  if (safety_switch_state == 2) {
    break_process();
    throttle_process();
  }
  pwm_process();
  seg_display();
  state_led_update();
  i2c_request();
  bluetooth();
}

void safety_switch_detection() {
  safety_switch_data = 0;
  safety_switch_state = 0;
  safety_switch_data = analogRead(11);
  Serial.print("Safety_Switch:");
  Serial.print(safety_switch_data);
  Serial.print(",");
  if (safety_switch_data >= 1000 && safety_switch_data <= 1023) {
    safety_switch_state = 1;
    throttle_level = 0;
    Serial.print("1,Unsafe.");
  }
  else {
    safety_switch_state = 2;
    Serial.print("2,Safe.");
  }
}
void safety_switch_led_update() {
  if (safety_switch_state == 1) {
    analogWrite(safety_red, 50);
    analogWrite(safety_green, 0);
    analogWrite(safety_blue, 0);
    led_state_1 = 1;
    led_state_2 = 0;
    seg_state = 0;
  }
  else if (safety_switch_state == 2) {
    analogWrite(safety_red, 0);
    analogWrite(safety_green, 50);
    analogWrite(safety_blue, 0);
    led_state_1 = 2;
  }
  else {
    analogWrite(safety_red, 0);
    analogWrite(safety_green, 0);
    analogWrite(safety_blue, 50);
  }
}
void voltage_detection() {
  float temp1;
  voltage_read1 = analogRead(voltage_sensor_1);
  temp1 = voltage_read1 / 4.092;
  voltage_1 = (temp1 / 10);
  Serial.print(" Voltage_1:");
  Serial.print(voltage_1);
  float temp2;
  voltage_read2 = analogRead(voltage_sensor_2);
  temp2 = voltage_read2 / 4.092;
  voltage_2 = (temp2 / 10);
  Serial.print(" Voltage_2:");
  Serial.print(voltage_2);
  float temp3;
  voltage_read3 = analogRead(voltage_sensor_3);
  temp3 = voltage_read3 / 4.092;
  voltage_3 = (temp3 / 10);
  Serial.print(" Voltage_3:");
  Serial.print(voltage_3);
}
void break_process() {
  break_data = analogRead(break_pin);
  Serial.print(" Break Value=");
  Serial.print(break_data);
  Serial.print(",State:");
  if (break_data >= 900) {
    break_state = 1;
    Serial.print("Break!");
    led_state_1 = 3;
  }
  else {
    break_state = 2;
    Serial.print("Normal");
  }
}
void throttle_process() {
  throttle_data = analogRead(throttle_pin);
  Serial.print(" Throttle_Value=");
  Serial.print(throttle_data);
  Serial.print(",Level: ");
  if (throttle_data <= 300) {
    seg_state = 1;
    throttle_level = 1;
    Serial.print("1");
  }
  else if (throttle_data > 300 & throttle_data <= 350) {
    seg_state = 2;
    throttle_level = 2;
    Serial.print("2");
  }
  else if (throttle_data > 350 & throttle_data <= 450) {
    seg_state = 3;
    throttle_level = 3;
    Serial.print("3");
  }
  else if (throttle_data > 450 & throttle_data <= 500) {
    seg_state = 4;
    throttle_level = 4;
    Serial.print("4");
  }
  else if (throttle_data > 500 & throttle_data <= 550) {
    seg_state = 5;
    throttle_level = 5;
    Serial.print("5");
  }
  else if (throttle_data > 550 & throttle_data <= 600) {
    seg_state = 6;
    throttle_level = 6;
    Serial.print("6");
  }
  else if (throttle_data > 600 & throttle_data <= 650) {
    seg_state = 7;
    throttle_level = 7;
    Serial.print("7");
  }
  else if (throttle_data > 650 & throttle_data <= 700) {
    seg_state = 8;
    throttle_level = 8;
    Serial.print("8");
  }
  else if (throttle_data > 700) {
    seg_state = 9;
    throttle_level = 9;
    Serial.print("9");
  }
}
void pwm_process() {
  if (throttle_level == 0) {
    pwm_percent = 50;
  }
  else if (throttle_level == 1) {
    pwm_percent = 55;
  }
  else if (throttle_level == 2) {
    pwm_percent = 60;
  }
  else if (throttle_level == 3) {
    pwm_percent = 61;
  }
  else if (throttle_level == 4) {
    pwm_percent = 62;
  }
  else if (throttle_level == 5) {
    pwm_percent = 64;
  }
  else if (throttle_level == 6) {
    pwm_percent = 65;
  }
  else if (throttle_level == 7) {
    pwm_percent = 68;
  }
  else if (throttle_level == 8) {
    pwm_percent = 70;
  }
  else if (throttle_level == 9) {
    pwm_percent = 75;
  }
  else {
    pwm_percent = 50;
  }
  pwm_value = 0;
  pwm_value = 2.55 * pwm_percent;
  analogWrite(PWM_pin, pwm_value);
  Serial.print(" PWM_Out:");
  Serial.print(pwm_value);
}
void seg_display() {
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
    digitalWrite(seg_a, LOW); digitalWrite(seg_b, HIGH); digitalWrite(seg_c, HIGH); digitalWrite(seg_d, LOW);
  }
  else if (seg_state == 7) {
    digitalWrite(seg_a, HIGH); digitalWrite(seg_b, HIGH); digitalWrite(seg_c, HIGH); digitalWrite(seg_d, LOW);
  }
  else if (seg_state == 8) {
    digitalWrite(seg_a, LOW); digitalWrite(seg_b, LOW); digitalWrite(seg_c, LOW); digitalWrite(seg_d, HIGH);
  }
  else if (seg_state == 9) {
    digitalWrite(seg_a, HIGH); digitalWrite(seg_b, LOW); digitalWrite(seg_c, LOW); digitalWrite(seg_d, HIGH);
  }
}
void state_led_update() {
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
  else {
    digitalWrite(ur, LOW); digitalWrite(ug, LOW); digitalWrite(ub, LOW);
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
  else {
    digitalWrite(lr, LOW); digitalWrite(lg, LOW); digitalWrite(lb, LOW);
  }
}
void i2c_request() {
  Wire.requestFrom(11, 2);
  while (Wire.available())
  {
    rpm_a = Wire.read(); rpm_b = Wire.read();
    rpm = (rpm_b << 8) | rpm_a;
    float Speed_Calc = 0;
    Speed_Calc = rpm * 0.020944;
    if (Speed_Calc >= 0 && Speed_Calc <= 20) {
      Speed = Speed_Calc;
    }
    else {
      Speed = 0;
    }
  }
  if (rpm >= 1 && rpm <= 700) {
    Serial.print(" i2c:");
    Serial.print(rpm);
    Serial.print(" Speed:");
    Serial.print(Speed);
    Serial.print("km/h");
  }
  else if (rpm <= 1) {
    Serial.print(" i2c:");
    Serial.print("0");
    Serial.print(" Speed:");
    Serial.print(Speed);
    Serial.print("km/h");
  }
  else {
    Serial.print(" i2c:");
    Serial.print("ERROR ");
    Serial.print(" Speed:");
    Serial.print(Speed);
    Serial.print("km/h");
  }
}
void bluetooth() {
  byte Data[18];
  byte cmmd[20];
  int insize;
  serialA = I2CBT.read();
  int tosend_A = 0;
  tosend_A = Speed * 100;
  int tosend_B = 0;
  if (voltage_1 >= 1 && voltage_1 <= 25) {
    tosend_B = voltage_1 * 100;
  }
  else {
    tosend_B = 0;
  }
  int tosend_C = 0;
  tosend_C = (safety_switch_state * 1000) + (break_state * 100) + (head_light_state * 10) + (turn_indicator_state * 1);
  int tosend_D = 0;
  if (voltage_2 >= 1 && voltage_2 <= 25) {
    tosend_D = voltage_2 * 100;
  }
  else {
    tosend_D = 0;
  }
  int tosend_E = 0;
  tosend_E = (throttle_level * 1000) + (throttle_data * 1);
  int tosend_F = 0;
  tosend_F = rpm;

  Data[0] = 'a';
  Data[1] = tosend_A / 256;
  Data[2] = tosend_A % 256;
  Data[3] = 'b';
  Data[4] = tosend_B / 256;
  Data[5] = tosend_B % 256;
  Data[6] = 'c';
  Data[7] = tosend_C / 256;
  Data[8] = tosend_C % 256;
  Data[9] = 'd';
  Data[10] = tosend_D / 256;
  Data[11] = tosend_D % 256;
  Data[12] = 'e';
  Data[13] = tosend_E / 256;
  Data[14] = tosend_E % 256;
  Data[15] = 'f';
  Data[16] = tosend_F / 256;
  Data[17] = tosend_F % 256;
  /*
    49 ＋ 00 = 49 : OFF OFF
    49 ＋ 10 = 59 : ON  OFF
    49 ＋ 01 = 50 : OFF ON
    49 ＋ 11 = 60 : ON  ON
  */
  Serial.print(" SerailA=");
  Serial.println(serialA);

  if (serialA == 255) {
    for (int j = 0; j < 21; j++) {
      I2CBT.write(Data[j]);
      //Serial.print("Data Sent:");
      //Serial.println(Data[j]);
    }
  }
  if (serialA == 59) {
    for (int j = 0; j < 21; j++) {
      I2CBT.write(Data[j]);
      //Serial.print("Data Sent:");
      //Serial.println(Data[j]);
    }
  }
  if (serialA == 50) {
    for (int j = 0; j < 21; j++) {
      I2CBT.write(Data[j]);
      //Serial.print("Data Sent:");
      //Serial.println(Data[j]);
    }
  }
  if (serialA == 60) {
    for (int j = 0; j < 21; j++) {
      I2CBT.write(Data[j]);
      //Serial.print("Data Sent:");
      //Serial.println(Data[j]);
    }
  }
  serialA = 0;
}
