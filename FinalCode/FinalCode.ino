#include <SoftwareSerial.h>

SoftwareSerial BTserial(10, 11);  // Setup of Bluetooth module on pins 10 (TXD) and 11 (RXD);

// Define the pin connected to the sensor
const int pin1 = A1;
const int pin2 = A0;

const int motorSensor = 5;
const int motorDown = 500;  //moving the motor down - 1/4 quarter down
const int motorUp = 2500;   //moving the motor up - 3/4 quarter rotation

const int lowerDistanceThreshold = 10;
const int upperDistanceThreshold = 50;
const int minDistanceChanged = -5;
const int mindelayTime = 750;
const int maxdelayTime = 1000;
bool isEntering = false;
bool isLeaving = false;
int counter = 0;
int maxOccupancy = 1;  //DEFAULT VALUE: 100

float prev_distance1 = 0;
float prev_distance2 = 0;

bool closed = false;
bool open = false;



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

      if (counter >= maxOccupancy && closed == false) {
        digitalWrite(motorSensor, HIGH);
        delay(motorDown);
        digitalWrite(motorSensor, LOW);
        Serial.println("Motor Down");
        closed = true;
        open = false;
      } else {
        if (counter <= maxOccupancy) {
          counter++;
        }
      }

      BTserial.print(counter);
      Serial.println(counter);
    }
  }


  if ((distance2 <= upperDistanceThreshold) && (distance2 >= lowerDistanceThreshold)) {
    if ((prev_distance2 - distance2 <= minDistanceChanged)) {
      if (counter >= maxOccupancy && open == false) {
        Serial.println("Motor Up");
        digitalWrite(motorSensor, HIGH);
        delay(motorUp);
        digitalWrite(motorSensor, LOW);
        closed = false;
        open = true;
      }

      if (counter <= 0) {
        counter = 0;
      } else {
        counter--;
      }

      BTserial.print(counter);
      Serial.println(counter);
    }
  }


  prev_distance1 = distance1;
  prev_distance2 = distance2;

  delay(10);
}

float readSensorValue(int pin) {
  int sensorValue = analogRead(pin);
  float voltage = sensorValue * 0.00488;
  float distanceCM = 60.374 * pow(voltage, -1.16);
  // float distance = (6787.0 / (sensorValue - 3.0)) - 4.0;
  return distanceCM;
}
