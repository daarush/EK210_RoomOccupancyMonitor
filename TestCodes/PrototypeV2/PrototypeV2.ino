// TEAM DALE
//distance sensors
const int sensorPin1 = A2; 
const int sensorPin2 = A3;

//motor
const int motorSensor = 5;

const int lowerDistanceThreshold = 20;
const int upperDistanceThreshold = 60;
const int threshHoldDistance = 75;
const int thresholdTime = 500;  // ms
const int totalDelay = 100;

int counter = 0;
int maxOccupancy = 10;
const int closeMotor_time = 1000;
const int openMotor_time = 3000;

float distance1;
float distance2;
int initialDistance1 = 0;
int initialDistance2 = 0;
int previousDistance1 = 0;
int previousDistance2 = 0;
unsigned long startTime1 = 0;
unsigned long startTime2 = 0;


// Setup function
void setup() {
  Serial.begin(9600);

  pinMode(motorSensor, OUTPUT);
}

// Main loop function
void loop() {
  handleSensor(sensorPin1, distance1, previousDistance1, startTime1, 1);
  // handleSensor(sensorPin2, distance2, previousDistance2, startTime2, 2);

  // if (counter >= maxOccupancy) {
  //   turnMotor(0);
  // } 

  delay(totalDelay);
}

// Function to handle each sensor's logic
void handleSensor(int sensorPin, float& distance, int& previousDistance, unsigned long& startTime, const int sensorName) {
  distance = readDistance(sensorPin);
  unsigned long currentTime = millis();
  unsigned long timeDifference = currentTime - startTime;

  printDistanceVals(distance, "sadsdad");
  if ((distance >= lowerDistanceThreshold) && (distance <= upperDistanceThreshold)) {
    if (timeDifference >= thresholdTime) {
      float distanceChange = previousDistance - distance;
      if (distanceChange >= threshHoldDistance) {
        if (sensorName == 1) {
          counter++;
        } else if (sensorName == 2) {
          counter--;
        }
        Serial.print("counter");
        Serial.print(": ");
        Serial.println(counter);
      }
    }
    // Reset the start time if needed
    startTime = currentTime;
  }

  // Update the previous distance with the current distance
  previousDistance = distance;
}

// Function to read distance from a given pin
float readDistance(int pin) {
  int sensorValue = analogRead(pin);
  return 10650.08 * pow(sensorValue, -0.935) - 10;
}

// Function to print distance values
void printDistanceVals(float distance, const char* sensorName) {
  Serial.print(sensorName);
  Serial.print(" Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
}

void motorControl(int state) {
  if (state == 0){
    turnMotor(1000);
  } else if (state == 1) {
    turnMotor(3000);
  }
}

void turnMotor(int time) {
  digitalWrite(motorSensor, HIGH);
  delay(time);
  digitalWrite(motorSensor, LOW);
}
