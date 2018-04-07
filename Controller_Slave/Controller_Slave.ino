#include <Wire.h>

int seg_state = 0;
int led_state_1 = 0;
int led_state_2 = 0;

int val1 = 0; //Numbers 0~9
int val2 = 0; //1=RED 2=GREEN 3=BLUE
int val3 = 0; //1=RED 2=GREEN 3=BLUE



void setup() {
  Serial.begin(9600);
  Wire.begin(1);
  Wire.onRequest(requestEvent);
}

void loop() {
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

  Wire.write(val1); // lower byte
  Wire.write(val1 >> 8); // upper byte

  Wire.write(val2); // lower byte
  Wire.write(val2 >> 8); // upper byte

  Wire.write(val3); // lower byte
  Wire.write(val3 >> 8); // upper byte
}
