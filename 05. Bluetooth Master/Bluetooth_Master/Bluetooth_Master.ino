#include <SoftwareSerial.h> //libaray of I2C
SoftwareSerial BT(3, 4); //define serial BT  RX=3, TX=4
#include <Wire.h>

int time = millis(); //millisceond

volatile int tosend_A_a; volatile int tosend_A_b; volatile int tosend_A;
volatile int tosend_B_a; volatile int tosend_B_b; volatile int tosend_B;
volatile int tosend_C_a; volatile int tosend_C_b; volatile int tosend_C;
volatile int tosend_D_a; volatile int tosend_D_b; volatile int tosend_D;
volatile int tosend_E_a; volatile int tosend_E_b; volatile int tosend_E;
volatile int tosend_F_a; volatile int tosend_F_b; volatile int tosend_F;

void setup()
{
  Serial.begin(9600);
  BT.begin(9600);
  pinMode(13, OUTPUT);
  Wire.begin();
}

void loop()
{
  if (BT.available()) //received BT data
  {
    int LED = BT.read();
    Serial.print("Received BT cmd: ");
    Serial.println(LED);
    if (LED == 1)                    //turn on LED if BT cmd is 1
      digitalWrite(13, HIGH);
    else if (LED == 0)               //turn off LED if BT cmd is 0
      digitalWrite(13, LOW);
  }
  int now_time = millis();
  if ((now_time - time) >= 1)    //actives every 100 milliseconds
  {
    int LED_status = digitalRead(13);  //send the status of LED to smartphone over BT
    BT.write(LED_status);
    //Serial.print("Send LED_status: ");
    //Serial.println(LED_status);
    time = now_time;
  }
  Wire.requestFrom(12, 12);
  while (Wire.available())
  {
    tosend_A_a = Wire.read(); tosend_A_b = Wire.read();
    tosend_A = (tosend_A_b << 8) | tosend_A_a;
    tosend_B_a = Wire.read(); tosend_B_b = Wire.read();
    tosend_B = (tosend_B_b << 8) | tosend_B_a;
    tosend_C_a = Wire.read(); tosend_C_b = Wire.read();
    tosend_C = (tosend_C_b << 8) | tosend_C_a;
    tosend_D_a = Wire.read(); tosend_D_b = Wire.read();
    tosend_D = (tosend_D_b << 8) | tosend_D_a;
    tosend_E_a = Wire.read(); tosend_E_b = Wire.read();
    tosend_E = (tosend_E_b << 8) | tosend_E_a;
    tosend_F_a = Wire.read(); tosend_F_b = Wire.read();
    tosend_F = (tosend_F_b << 8) | tosend_F_a;
  }
  Serial.print("A:");
  Serial.print(tosend_A);
  Serial.print(" B:");
  Serial.print(tosend_B);
  Serial.print(" C:");
  Serial.print(tosend_C);
  Serial.print(" D:");
  Serial.print(tosend_D);
  Serial.print(" E:");
  Serial.print(tosend_E);
  Serial.print(" F:");
  Serial.println(tosend_F);

}
