//科計部計畫 主控制器程式
//最後更新: 20190113
//實驗地點: NKUST T211-1

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


void setup() {
  Serial.begin(9600);

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

  digitalWrite(ur, HIGH); digitalWrite(lr, HIGH); delay(100); digitalWrite(ur, LOW); digitalWrite(lr, LOW);
  digitalWrite(ug, HIGH); digitalWrite(lg, HIGH); delay(100); digitalWrite(ug, LOW); digitalWrite(lg, LOW);
  digitalWrite(ub, HIGH); digitalWrite(lb, HIGH); delay(100); digitalWrite(ub, LOW); digitalWrite(lb, LOW);
  digitalWrite(ur, HIGH);
}

void loop() {
  seg_display();
  state_led_update();
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
