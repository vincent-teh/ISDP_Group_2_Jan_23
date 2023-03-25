#include <Servo.h>

Servo myservo;  // create servo object to control a servo
int angle = 0;

void setup() {
  Serial.begin(9600);  // initialize serial communication at 9600 baud rate
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  if (Serial.available()) {
    angle = Serial.readString().toInt();  // read the integer value entered by the user
    angle = constrain(angle, 0, 180);  // constrain the angle value between 0 and 180
    myservo.write(angle);  // move the servo to the desired angle
    Serial.print("Servo angle set to: ");
    Serial.println(angle);
  }
}
