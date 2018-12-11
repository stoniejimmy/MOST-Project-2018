void setup() {
  Serial.begin(9600);
  pinMode(3, OUTPUT);

}

void loop() {
  Serial.println("PWM Write: 170");
  analogWrite(3, 170);
  delay(5000);
  Serial.println("PWM Write: 175");
  analogWrite(3, 175);
  delay(5000);
  Serial.println("PWM Write: 180");
  analogWrite(3, 180);
  delay(5000);
  Serial.println("PWM Write: 190");
  analogWrite(3, 190);
  delay(5000);
  Serial.println("PWM Write: 200");
  analogWrite(3, 200);
  delay(5000);

  Serial.println("PWM Write: 200");
  analogWrite(3, 200);
  delay(5000);
}
