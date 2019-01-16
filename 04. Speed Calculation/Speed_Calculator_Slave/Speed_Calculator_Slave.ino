#include <Wire.h>

int refsig = 200;
int val_digital;
int prev_val = 0;
unsigned long t, cur_t;

int RPM = 0;
int offtime = 0;
int ontime = 0;


void setup()
{
  Serial.begin(9600);
  pinMode(A0, INPUT);
  Wire.begin(11);
  Wire.onRequest(requestEvent);
}

void loop()//Measure RPM
{
  int sig = analogRead(A0); //read raw value of hall sensor
  //    Serial.print("sig: ");
  //    Serial.println(sig);
  if (sig > refsig) val_digital = HIGH; //convert it to digital 0,1 form
  else val_digital = LOW;
  if (prev_val == 0 && val_digital == 1) { //check for rising edge
    offtime = 0;
    ontime = 0;
    cur_t = micros();
    RPM = (1000000 * 60 / (cur_t - t));
    if (RPM >= 0 && RPM <= 800) {
      Serial.print("RPM: ");
      Serial.println(RPM); //print the rpm
    }
    t = micros();
  }
  if (sig > 1000) {
    offtime = offtime + 1;
  }
  if (offtime > 10000) {
    RPM = 0;
    Serial.print("RPM: ");
    Serial.println(RPM); //print the rpm
  }
  if (sig < 1000) {
    ontime = ontime + 1;
  }
  if (ontime > 10000) {
    RPM = 0;
    Serial.print("RPM: ");
    Serial.println(RPM); //print the rpm
  }
  prev_val = val_digital;
}

void requestEvent()
{
  //  Serial.print("I2C Request!!! ");
  //  Serial.println(RPM);
  Wire.write(RPM); // lower byte
  Wire.write(RPM >> 8); // upper byte
}
