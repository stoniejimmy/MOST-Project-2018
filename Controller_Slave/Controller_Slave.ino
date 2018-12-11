#include <Wire.h>

int seg_state = 0;
int led_state_1 = 0;
int led_state_2 = 0;

int break_read = 0;
int throttle_read = 0;

int val1 = 0; //Numbers 0~9
int val2 = 0; //1=RED 2=GREEN 3=BLUE
int val3 = 0; //1=RED 2=GREEN 3=BLUE



void setup() {
  Serial.begin(9600);
  Wire.begin(11);
  Wire.onRequest(requestEvent);

  pinMode(13, OUTPUT);
}

void loop() {
  break_read = analogRead(A0);
  Serial.print("Break Value = ");
  Serial.println(break_read);

  throttle_read = analogRead(A1);
  Serial.print("Throttle Value = ");
  Serial.print(throttle_read);
  Serial.print("     ");

  if (break_read >= 900) {
    seg_state = 0;
    led_state_1 = 1;
    led_state_2 = 1;
  }
  else {
    led_state_1 = 2;
    led_state_2 = 2;
    if (throttle_read <= 300) {
      seg_state = 1;
      Serial.println("1");
      led_state_2 = 2;
    }
    else if (throttle_read > 300 & throttle_read <= 350) {
      seg_state = 2;
      Serial.println("2");
      led_state_2 = 2;
    }
    else if (throttle_read > 350 & throttle_read <= 450) {
      seg_state = 3;
      Serial.println("3");
      led_state_2 = 2;
    }
    else if (throttle_read > 450 & throttle_read <= 500) {
      seg_state = 4;
      Serial.println("4");
      led_state_2 = 2;
    }
    else if (throttle_read > 500 & throttle_read <= 550) {
      seg_state = 5;
      Serial.println("5");
      led_state_2 = 2;
    }
    else if (throttle_read > 550 & throttle_read <= 600) {
      seg_state = 6;
      Serial.println("6");
      led_state_2 = 3;
    }
    else if (throttle_read > 600 & throttle_read <= 650) {
      seg_state = 7;
      Serial.println("7");
      led_state_2 = 3;
    }
    else if (throttle_read > 650 & throttle_read <= 700) {
      seg_state = 8;
      Serial.println("8");
      led_state_2 = 1;
    }
    else if (throttle_read > 700) {
      seg_state = 9;
      Serial.println("9");
      led_state_2 = 1;
    }
  }
}

void requestEvent()
{
  digitalWrite(13, HIGH);
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

  digitalWrite(13, LOW);
}
