#include <SoftwareSerial.h>

SoftwareSerial mySerial (2,3); // RX, TX

void setup () {
    mySerial.begin(9600);
    Serial.begin(9600);
    Serial.println("Enter AT commands:");
}

void loop() {
    while (mySerial.available()) {
        Serial.write(mySerial.read());
    }

    while (Serial.available()) {
        mySerial.write(Serial.read());
    }
}
