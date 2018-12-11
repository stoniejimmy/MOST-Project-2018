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
  Wire.requestFrom(11, 6);
  while (Wire.available())
  {
    val1_a = Wire.read(); val1_b = Wire.read();
    val1 = (val1_b << 8) | val1_a;
    val2_a = Wire.read(); val2_b = Wire.read();
    val2 = (val2_b << 8) | val2_a;
    val3_a = Wire.read(); val3_b = Wire.read();
    val3 = (val3_b << 8) | val3_a;
    val4_a = Wire.read(); val4_b = Wire.read();
    val4 = (val4_b << 8) | val4_a;

  }
  seg_state = val1;
  led_state_1 = val2;
  led_state_2 = val3;
  pwm_value = val4;

  Serial.print("val1:"); Serial.println(val1);
  Serial.print("val2:"); Serial.println(val2);
  Serial.print("val3:"); Serial.println(val3);
  Serial.print("val4:"); Serial.println(val4);
  Serial.println("");
}
