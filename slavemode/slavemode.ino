#include <Servo.h>
#define button 8
Servo myServo;
int state = 20;
int buttonState = 0;

void setup() {
  pinMode(button, INPUT);
  myServo.attach(9);
  Serial.begin(38400); // Default communication rate of the Bluetooth module
}

void loop() {
 if(Serial.available() > 0){ // Checks whether data is comming from the serial port
  //if (Serial.read() != 1) {
    state = Serial.read(); // Reads the data from the serial port
    Serial.println(state);
  }

 
 // Controlling the servo motor  
  delay(50);
 
 // Reading the button
 buttonState = digitalRead(button);

}
