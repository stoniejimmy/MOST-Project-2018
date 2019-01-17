#include <SoftwareSerial.h>
SoftwareSerial BT(3, 5);

long serialA = 0;

int tail = 0;
int left = 0;
int right = 0;
int both = 0;

void setup()
{
  Serial.begin(9600);
  BT.begin(9600);
  pinMode(A5, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  digitalWrite(9, HIGH);
}

void loop() {
  serialA = BT.read();
  Serial.print("serialA = ");
  Serial.println(serialA);
  if (serialA == 110) {
    digitalWrite(A5, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(A0, LOW);
    digitalWrite(A1, LOW);
  }
  else if (serialA == 111) {
    digitalWrite(A5, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(A0, HIGH);
    digitalWrite(A1, LOW);
  }
  else if (serialA == 112) {
    digitalWrite(A5, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(A0, LOW);
    digitalWrite(A1, HIGH);
  }
  else if (serialA == 113) {
    digitalWrite(A5, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(A0, HIGH);
    digitalWrite(A1, HIGH);
  }
  else if (serialA == 100) {
    digitalWrite(A5, HIGH);
    digitalWrite(9, LOW);
    digitalWrite(A0, LOW);
    digitalWrite(A1, LOW);
  }
  else if (serialA == 101) {
    digitalWrite(A5, HIGH);
    digitalWrite(9, LOW);
    digitalWrite(A0, HIGH);
    digitalWrite(A1, LOW);
  }
  else if (serialA == 102) {
    digitalWrite(A5, HIGH);
    digitalWrite(9, LOW);
    digitalWrite(A0, LOW);
    digitalWrite(A1, HIGH);
  }
  else if (serialA == 103) {
    digitalWrite(A5, HIGH);
    digitalWrite(9, LOW);
    digitalWrite(A0, HIGH);
    digitalWrite(A1, HIGH);
  }
  else if (serialA == 10) {
    digitalWrite(A5, LOW);
    digitalWrite(9, HIGH);
    digitalWrite(A0, LOW);
    digitalWrite(A1, LOW);
  }
  else if (serialA == 11) {
    digitalWrite(A5, LOW);
    digitalWrite(9, HIGH);
    digitalWrite(A0, HIGH);
    digitalWrite(A1, LOW);
  }
  else if (serialA == 12) {
    digitalWrite(A5, LOW);
    digitalWrite(9, HIGH);
    digitalWrite(A0, LOW);
    digitalWrite(A1, HIGH);
  }
  else if (serialA == 13) {
    digitalWrite(A5, LOW);
    digitalWrite(9, HIGH);
    digitalWrite(A0, HIGH);
    digitalWrite(A1, HIGH);
  }
  else if (serialA == 0) {
    digitalWrite(A5, LOW);
    digitalWrite(9, LOW);
    digitalWrite(A0, LOW);
    digitalWrite(A1, LOW);
  }
  else if (serialA == 1) {
    digitalWrite(A5, LOW);
    digitalWrite(9, LOW);
    digitalWrite(A0, HIGH);
    digitalWrite(A1, LOW);
  }
  else if (serialA == 2) {
    digitalWrite(A5, LOW);
    digitalWrite(9, LOW);
    digitalWrite(A0, LOW);
    digitalWrite(A1, HIGH);
  }
  else if (serialA == 3) {
    digitalWrite(A5, LOW);
    digitalWrite(9, LOW);
    digitalWrite(A0, HIGH);
    digitalWrite(A1, HIGH);
  }
}
