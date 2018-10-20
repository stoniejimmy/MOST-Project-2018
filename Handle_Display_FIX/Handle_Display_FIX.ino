#include <Wire.h>

void setup()
{
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
}

volatile int val1_a; volatile int val1_b; volatile int val1;
volatile int val2_a; volatile int val2_b; volatile int val2;
volatile int val3_a; volatile int val3_b; volatile int val3;



void loop()
{

  // ~~ START Inquire value from SlaveID#11 ~~ //
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
  delay(500);
  Serial.print("val1:"); Serial.println(val1);
  Serial.print("val2:"); Serial.println(val2);
  Serial.print("val3:"); Serial.println(val3);
  Serial.println("");
}
