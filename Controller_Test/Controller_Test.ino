void setup() {
  Serial.begin(9600);
  pinMode(3, OUTPUT);

}

void loop() {
  Serial.println("PWM Write: 160");
  analogWrite(3, 160);
  delay(5000);
  Serial.println("PWM Write: 180");
  analogWrite(3, 180);
  delay(5000);
  Serial.println("PWM Write: 200");
  analogWrite(3, 200);
  delay(5000);
  Serial.println("PWM Write: 220");
  analogWrite(3, 220);
  delay(5000);
  Serial.println("PWM Write: 240");
  analogWrite(3, 240);
  delay(5000);
  Serial.println("PWM Write: 254");
  analogWrite(3, 254);
  delay(5000);
  Serial.println("PWM Write: 150");
  analogWrite(3, 150);
  delay(50000);
}
