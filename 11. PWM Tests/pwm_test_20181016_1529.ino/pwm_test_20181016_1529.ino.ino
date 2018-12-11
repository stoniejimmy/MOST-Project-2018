int led = 3;      // LED 腳位

void setup()
{
  pinMode(led, OUTPUT);
}

void loop()
{
  analogWrite(led, 0);
  delay(1000);
  analogWrite(led, 2);
  delay(1000);
}
