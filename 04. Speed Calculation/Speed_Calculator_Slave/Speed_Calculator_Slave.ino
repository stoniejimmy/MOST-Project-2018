#include <Wire.h>

int refsig = 200;
int val_digital;
int prev_val = 0;
unsigned long t, cur_t;


void setup()
{
  Serial.begin(9600);
  pinMode(A0, INPUT);
}

void loop()//Measure RPM
{
  {
    int sig = analogRead(A0); //read raw value of hall sensor
    if (sig > refsig) val_digital = HIGH; //convert it to digital 0,1 form
    else val_digital = LOW;
    if (prev_val == 0 && val_digital == 1) { //check for rising edge
      cur_t = micros();
      float RPM = 0;
      RPM = (1000000 * 60 / (cur_t - t));
      if (RPM >= 0 && RPM <= 800) {
        Serial.print("RPM: ");
        Serial.print(RPM); //print the rpm
        Serial.print("   Speed: ");
        Serial.print(RPM * 0.020944);
        Serial.print("   To Send: ");
        int tosend = 0;
        tosend = RPM * 0.020944 * 10;
        Serial.println(tosend);
      }
      t = micros();
    }
    prev_val = val_digital;
  }
}
