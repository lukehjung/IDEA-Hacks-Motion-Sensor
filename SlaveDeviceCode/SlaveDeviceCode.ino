#include <Servo.h>
#include <Wire.h>
//#include <SparkFun_APDS9960.h>
//#define button 8
// Pins
//#define APDS9960_INT    2 // Needs to be an interrupt pin
#define LEFTLED 3
#define RIGHTLED 4
#define ONLED 5
// Constants
// Global Variables
//SparkFun_APDS9960 apds = SparkFun_APDS9960();
int isr_flag = 0;
int pos = 0;    // variable to store the servo position
bool UP = true;
bool DOWN = false;
bool ford = true;
bool foru = true;

Servo myservo;
int state = 20;
//int buttonState = 0;

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  // Set interrupt pin as input
  //pinMode(APDS9960_INT, INPUT);
  pinMode(LEFTLED, OUTPUT);
  pinMode(RIGHTLED, OUTPUT);
  pinMode(ONLED, OUTPUT);
  digitalWrite(ONLED, HIGH);

  //pinMode(button, INPUT);
  Serial.begin(38400); // Default communication rate of the Bluetooth module

//  Serial.begin(9600);
//  Serial.println();
//  Serial.println(F("--------------------------------"));
//  Serial.println(F("SparkFun APDS-9960 - GestureTest"));
//  Serial.println(F("--------------------------------"));

  // Initialize interrupt service routine
  // attachInterrupt(digitalPinToInterrupt(APDS9960_INT), interruptRoutine, FALLING);
  // Initialize APDS-9960 (configure I2C and initial values)
//  if ( apds.init() ) {
//    Serial.println(F("APDS-9960 initialization complete"));
//  } else {
//    Serial.println(F("Something went wrong during APDS-9960 init!"));
//  }

//  // check input
//  if ( Serial.available() > 0 ) {
//    Serial.println(F("Bluetooth is now running - received!"));
//  } else {
//    Serial.println(F("Something went wrong during transmission init!"));
//  }
}

void loop() {
  
if (Serial.available() > 0) { // Checks whether data is comming from the serial port
    state = Serial.read(); // Reads the data from the serial port
    Serial.println(state);
    handleGesture(state);
}

//  if ( isr_flag == 1 ) {
//    detachInterrupt(0);
//    handleGesture(state);
//    isr_flag = 0;
//    attachInterrupt(0, interruptRoutine, FALLING);
//  }
  
//  digitalWrite(LEFTLED, LOW);
//  digitalWrite(RIGHTLED, LOW);
}

void interruptRoutine() {
  isr_flag = 1;
}

void handleGesture(int state) {
   switch ( state ) {
      case 49:  // up
        digitalWrite(LEFTLED, LOW);
        digitalWrite(RIGHTLED, LOW);
        if (foru) {
        Serial.println("OPEN BLINDS");
        for (pos = 0; pos <= 90; pos += 10) // goes from 0 degrees to 180 degrees
        { // in steps of 1 degree
          myservo.write(pos);              // tell servo to go to position in variable 'pos'
          delay(50);                       // waits 15ms for the servo to reach the position
        }}
        foru = false;
        break;
      case 50:   // down
        digitalWrite(LEFTLED, LOW);
        digitalWrite(RIGHTLED, LOW);
        if (ford) {
        Serial.println("CLOSE BLINDS");
        for (pos = 180; pos >= 90; pos -= 10) // goes from 180 degrees to 0 degrees
        {
          myservo.write(pos);              // tell servo to go to position in variable 'pos'
          delay(50);                       // waits 15ms for the servo to reach the position
        }}
        ford = false;
        break;
      case 51:   // left
        ford = true;
        foru = true;
        digitalWrite(RIGHTLED, LOW);
        Serial.println("LEFT");
        digitalWrite(LEFTLED, HIGH);
        delay(100);
        break;
      case 52:   // right
        ford = true;
        foru = true;
        digitalWrite(LEFTLED, LOW);
        Serial.println("RIGHT");
        digitalWrite(RIGHTLED, HIGH);
        delay(100);
        break;
      case 53:   // near
        ford = true;
        foru = true;
        digitalWrite(LEFTLED, LOW);
        digitalWrite(RIGHTLED, LOW);
        Serial.println("NEAR");
        break;
      case 54:   // far
        ford = true;
        foru = true;
        digitalWrite(LEFTLED, LOW);
        digitalWrite(RIGHTLED, LOW);
        Serial.println("FAR");
        break;
      case 55:
        ford = true;
        foru = true;
        digitalWrite(LEFTLED, LOW);
        digitalWrite(RIGHTLED, LOW);
        Serial.println("NONE");
//      default:
//        Serial.println("ERROR");
   }
}

