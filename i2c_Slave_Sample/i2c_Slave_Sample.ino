#include <Wire.h>

int val1 = 123;
int val2 = 456;
int val3 = 789;

void setup()
{
  // Join i2c bus with address #11
  Wire.begin(11);
  Wire.onRequest(requestEvent);      // register event
}

void loop()
{
  delay(500);

}

// Function that executes whenever data is requested by master
// This function is registered as an event, see setup()
void requestEvent()
{
  Wire.write(val1); // lower byte
  Wire.write(val1 >> 8); // upper byte

  Wire.write(val2); // lower byte
  Wire.write(val2 >> 8); // upper byte

  Wire.write(val3); // lower byte
  Wire.write(val3 >> 8); // upper byte
}
