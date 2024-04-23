#include <SoftwareSerial.h>

SoftwareSerial BTserial(10, 11);  // Setup of Bluetooth module on pins 10 (TXD) and 11 (RXD);

// Define the pin connected to the sensor
const int pin1 = A0;
const int pin2 = A1;

const int motorSensor = 5;
const int motorDown = 75;  //moving the motor down - 1/4 quarter down
const int motorUp = 575;   //moving the motor up - 3/4 quarter rotation

const int lowerDistanceThreshold = 10;
const int upperDistanceThreshold = 30;
const int minDistanceChanged = -5;
const int mindelayTime = 500;
const int maxdelayTime = 1000;
bool isEntering = false;
bool isLeaving = false;
int counter = 0;
int maxOccupancy = 100;  //DEFAULT VALUE

float prev_distance1 = 0;
float prev_distance2 = 0;

void setup() {
  BTserial.begin(9600);
  Serial.begin(4800);
  pinMode(motorSensor, OUTPUT);
  digitalWrite(motorSensor, LOW);
}

void loop() {

  if (BTserial.available()) {
    String recievedData = BTserial.readStringUntil('\n');
    maxOccupancy = recievedData.toInt();
  }

  float distance1 = readSensorValue(pin1);
  float distance2 = readSensorValue(pin2);

  if ((distance1 <= upperDistanceThreshold) && (distance1 >= lowerDistanceThreshold)) {
    if ((prev_distance1 - distance1 <= minDistanceChanged)) {

      if (counter >= maxOccupancy) {
        digitalWrite(motorSensor, HIGH);
        delay(motorDown);  
        digitalWrite(motorSensor, LOW);
        Serial.println("Motor Down");
        // Serial.print("maxOccupancy: ");
        // Serial.print(maxOccupancy);
        // Serial.println();
      } else {
        counter++;
      }

      BTserial.print(counter);  //sends the data to bluetooth
      // BTserial.print(maxOccupancy);
      Serial.println(counter);
    }
  }


  if ((distance2 <= upperDistanceThreshold) && (distance2 >= lowerDistanceThreshold)) {
    // Serial.println(distance2);
    if ((prev_distance2 - distance2 <= minDistanceChanged)) {
      if (counter >= maxOccupancy) {
        Serial.println("Motor Up");
        digitalWrite(motorSensor, HIGH);
        delay(motorUp);  
        digitalWrite(motorSensor, LOW);
      }

      if (counter <= 0) {
        counter = 0;
      } else {
        counter--;
      }

      BTserial.print(counter);
      // BTserial.print(maxOccupancy);
      Serial.println(counter);
    }
  }


  prev_distance1 = distance1;
  prev_distance2 = distance2;

  delay(10);
}

float readSensorValue(int pin) {
  int sensorValue = analogRead(pin);
  float distance = (6787.0 / (sensorValue - 3.0)) - 4.0;
  return distance;
}
