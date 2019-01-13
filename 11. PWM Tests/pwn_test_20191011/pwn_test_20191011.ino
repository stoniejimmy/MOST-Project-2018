int PWM_pin1 = 3;
int PWM_pin2 = 9;
int PWM_pin3 = 10;
int PWM_pin4 = 11;
int pwm_percent = 2.55*55;

void setup()
{
  pinMode(PWM_pin1, OUTPUT);
  pinMode(PWM_pin2, OUTPUT);
  pinMode(PWM_pin3, OUTPUT);
  pinMode(PWM_pin4, OUTPUT);
}

void loop()
{
  analogWrite(PWM_pin1, pwm_percent);
  analogWrite(PWM_pin2, pwm_percent);
  analogWrite(PWM_pin3, pwm_percent);
  analogWrite(PWM_pin4, pwm_percent);
}
