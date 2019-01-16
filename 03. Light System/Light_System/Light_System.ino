#include <IRremote.h>

int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;
int tail = 0; //0=off 1=on
int left = 0;
int right = 0;
int both = 0;

void setup()
{
  pinMode(2, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver

  analogWrite(3, 255);
  delay(500);
  analogWrite(3, 0);
}

void loop() {
  if (irrecv.decode(&results)) {
    //Serial.println(results.value HEX);
    int compare = 0;
    compare = results.value;
    Serial.println(compare);
    if ((compare) == -7177) {
      Serial.println("2");
      if (tail == 0) {
        tail = 1;
      }
      else if (tail == 1) {
        tail = 0;
      }
    }
    if ((compare) == 6375) {
      Serial.println("2");
      if (tail == 0) {
        tail = 1;
      }
      else if (tail == 1) {
        tail = 0;
      }
    }
    if ((compare) == 25979) {
      Serial.println("4");
    }
    if ((compare) == 4335) {
      Serial.println("4");
      if (left == 0) {
        left = 1;
      }
      else if (left == 1) {
        left = 0;
      }
    }
    if ((compare) == 14535) {
      Serial.println("5");
      if (both == 0) {
        both = 1;
        left = 0;
        right = 0;
      }
      else if (both == 1) {
        both = 0;
        left = 0;
        right = 0;
      }
    }
    if ((compare) == 15547) {
      Serial.println("5");
      if (both == 0) {
        both = 1;
        left = 0;
        right = 0;
      }
      else if (both == 1) {
        both = 0;
        left = 0;
        right = 0;
      }
    }
    if ((compare) == 23205) {
      Serial.println("6");
      if (right == 0) {
        right = 1;
      }
      else if (right == 1) {
        right = 0;
      }
    }
    if ((compare) == -6241)
    {
      Serial.println("6");
      if (right == 0) {
        right = 1;
      }
      else if (right == 1) {
        right = 0;
      }
    }
    irrecv.resume(); // Receive the next value
  }
  if (tail == 1) {
    analogWrite(3, 255);
  }
  else if (tail == 0) {
    analogWrite(3, 0);
  }
  else {
    analogWrite(3, 0);
  }
  if (left == 0 && right == 0 && both == 0) {
    analogWrite(5, 0);
    analogWrite(6, 0);
    left = 0;
    right = 0;
    both = 0;
  }
  else if (left == 1 && right == 0 && both == 0) {
    analogWrite(5, 255);
    analogWrite(6, 0);
    delay(750 * 5);
    analogWrite(5, 0);
    analogWrite(6, 0);
    left = 0;
    right = 0;
    both = 0;
  }
  else if (left == 0 && right == 1 && both == 0) {
    analogWrite(5, 0);
    analogWrite(6, 255);
    delay(750 * 5);
    analogWrite(5, 0);
    analogWrite(6, 0);
    left = 0;
    right = 0;
    both = 0;
  }
  else if (left == 0 && right == 0 && both == 1) {
    analogWrite(5, 255);
    analogWrite(6, 255);
    delay(750 * 5);
    analogWrite(5, 0);
    analogWrite(6, 0);
    left = 0;
    right = 0;
    both = 0;
  }
  else {
    analogWrite(5, 255);
    analogWrite(6, 0);
    delay(750 * 5);
    analogWrite(5, 0);
    analogWrite(6, 0);
    left = 0;
    right = 0;
    both = 0;
  }

}
