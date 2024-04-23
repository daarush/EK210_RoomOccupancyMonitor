#include <SoftwareSerial.h>

SoftwareSerial BTserial(10, 11);  // Setup of Bluetooth module on pins 10 (TXD) and 11 (RXD);

int redPin = 4;
int greenPin = 5;
int bluePin = 6;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  BTserial.begin(9600);  // Bluetooth at baud 9600 for talking to the node server
  Serial.begin(4800);    // Default Serial on Baud 4800 for printing out some messages in the Serial Monitor
}

void loop() {

  // Calls on BTSerial and sends the string to any connected devices.
  // BTserial.print("From Arduino with mild ambivalence\n");

  // readStringUntil()
  // Reads all bytes off of the the Serial buffer until it finds the escape character '/n'
  // And then removes these bytes from the buffer
  // Returns the value as a string, which we print to the Serial monitor

  String state = BTserial.readStringUntil('\n');
  Serial.println(state);

  

  if (state == "red") {
    setColor(255, 0, 0);  // Red Color
  } else if (state == "green") {
    setColor(0, 255, 0);  // Green Color
  } else if (state == "blue") {
    setColor(127, 127, 127);  // Light Blue
  }



  //Just so the Serial Monitor on Arduino and console on the Node server don't get too spammed
  delay(500);
}

bool subString(String data, String substr) {
  int pos = data.indexOf(substr);
  if (pos != -1) {
    return 1;
  } else {
    return 0;
  }
}

void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}
