Turret Controller v2.0 2019.07.06 designed by RAMSOL (http://earndesignlab.com/)
#include <SoftwareSerial.h>
#include <Servo.h>
Servo myservoH;
Servo myservoV;
SoftwareSerial btSerial(2, 3);
int laser = 7;

void setup() {
  myservoH.attach(5);
  myservoV.attach(6);
  myservoH.write(90);
  myservoV.write(90);
  pinMode(laser, OUTPUT);
  btSerial.begin(9600);
  Serial.begin(9600);
}

void loop() {
  //I only used 1byte(0~255) data in Bluetooth commuication.
  //so it had a low sensitivity.(input: 0~100 > output: 0~180)
  if (btSerial.available()) {
    int value = btSerial.read();
    if (value == 254) {
      digitalWrite(laser, HIGH);
    }
    if (value == 255) {
      digitalWrite(laser, LOW);
    }
    if (value < 250) {
      if (value <= 100) {
        value = map(value, 0, 100, 180, 0);
        myservoH.write(value);
        delay(5);
      }
      if (value > 100) {
        value = map(value, 100, 200, 0, 180);
        myservoV.write(value);
        delay(5);
      }
    }
  }
}
