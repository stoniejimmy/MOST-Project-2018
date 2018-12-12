#include <Wire.h>

int pwm_value = 0;

volatile int val1_a; volatile int val1_b; volatile int val1;
volatile int val2_a; volatile int val2_b; volatile int val2;
volatile int val3_a; volatile int val3_b; volatile int val3;
volatile int val4_a; volatile int val4_b; volatile int val4;

int seg_state = 0;
int led_state_1 = 0;
int led_state_2 = 0;

void setup()
{
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output

  pinMode(3, OUTPUT);
}



void loop()
{
  Wire.requestFrom(11, 8);
  while (Wire.available())
  {
    val4_a = Wire.read(); val4_b = Wire.read();
    val4 = (val4_b << 8) | val4_a;

  }
  pwm_value = val4;
  Serial.print("val4:"); Serial.println(val4);
  Serial.println("");

  if (pwm_value == 0) {
    Serial.println("PWM Write: 155");
    analogWrite(3, 155);
  }
  else if (pwm_value == 1) {
    Serial.println("PWM Write: 185");
    analogWrite(3, 185);
  }
  else if (pwm_value == 2) {
    Serial.println("PWM Write: 190");
    analogWrite(3, 190);
  }
  else if (pwm_value == 4) {
    Serial.println("PWM Write: 195");
    analogWrite(3, 195);
  }
  else if (pwm_value == 5) {
    Serial.println("PWM Write: 200");
    analogWrite(3, 200);
  }
  else if (pwm_value == 6) {
    Serial.println("PWM Write: 210");
    analogWrite(3, 210);
  }
  else if (pwm_value == 7) {
    Serial.println("PWM Write: 220");
    analogWrite(3, 220);
  }
  else if (pwm_value == 8) {
    Serial.println("PWM Write: 230");
    analogWrite(3, 230);
  }
  else if (pwm_value == 9) {
    Serial.println("PWM Write: 240");
    analogWrite(3, 240);
  }
  else{
    Serial.println("ERROR: 150");
    analogWrite(3, 150);
  }

}
