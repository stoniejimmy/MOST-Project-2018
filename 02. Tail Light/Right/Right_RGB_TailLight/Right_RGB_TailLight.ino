void setup() {
  delay(720);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
  pinMode(0, INPUT);
  pinMode(1, INPUT);
//  digitalWrite(A5, HIGH); delay(500); //G1
//  digitalWrite(A4, HIGH); delay(500); //G2
//  digitalWrite(A3, HIGH); delay(500); //G3
//  digitalWrite(A2, HIGH); delay(500); //G4
//  digitalWrite(A1, HIGH); delay(500); //G5
//  digitalWrite(A0, HIGH); delay(500); //G6
//  digitalWrite(13, HIGH); delay(500); //G7
//  digitalWrite(12, HIGH); delay(500); //G8
//  digitalWrite(11, HIGH); delay(500); //G9
  digitalWrite(10, HIGH); delay(70); //R1
  digitalWrite(9, HIGH); delay(70); //R2
  digitalWrite(2, HIGH); delay(70); //R3
  digitalWrite(3, HIGH); delay(70); //R4
  digitalWrite(4, HIGH); delay(70); //R5
  digitalWrite(5, HIGH); delay(70); //R6
  digitalWrite(6, HIGH); delay(70); //R7
  digitalWrite(7, HIGH); delay(70); //R8
  digitalWrite(8, HIGH); delay(70); //R9
}

void loop() {
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  if (digitalRead(0) == HIGH) {
    digitalWrite(10, LOW);
    digitalWrite(9, LOW);
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(10, HIGH); digitalWrite(A5, HIGH); delay(15);
    digitalWrite(9, HIGH); digitalWrite(A4, HIGH); delay(15);
    digitalWrite(2, HIGH); digitalWrite(A3, HIGH); delay(15);
    digitalWrite(3, HIGH); digitalWrite(A2, HIGH); delay(15);
    digitalWrite(4, HIGH); digitalWrite(A1, HIGH); delay(15);
    digitalWrite(5, HIGH); digitalWrite(A0, HIGH); delay(15);
    digitalWrite(6, HIGH); digitalWrite(13, HIGH); delay(15);
    digitalWrite(7, HIGH); digitalWrite(12, HIGH); delay(15);
    digitalWrite(8, HIGH); digitalWrite(11, HIGH); delay(15);
    delay(300);
    digitalWrite(2, LOW);
    digitalWrite(4, LOW);
    digitalWrite(6, LOW);
    digitalWrite(8, LOW);
    digitalWrite(10, LOW);
    digitalWrite(12, LOW);
    digitalWrite(A0, LOW);
    digitalWrite(A2, LOW);
    digitalWrite(A4, LOW);
    digitalWrite(3, LOW);
    digitalWrite(5, LOW);
    digitalWrite(7, LOW);
    digitalWrite(9, LOW);
    digitalWrite(11, LOW);
    digitalWrite(13, LOW);
    digitalWrite(A1, LOW);
    digitalWrite(A3, LOW);
    digitalWrite(A5, LOW);
    delay(400);
  }
}
