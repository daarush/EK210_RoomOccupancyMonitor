// Define pins for IR sensors
const int irSensor1Pin = 2;  // Connect IR sensor 1 to digital pin 2
const int irSensor2Pin = 3;  // Connect IR sensor 2 to digital pin 3
const int motorSensor = 5;

// Define variables for counting
int counter = 0;

int occupancy = 10;

void setup() {
  // Initialize serial communication
  
  Serial.begin(9600);

  // Set IR sensor pins as inputs
  pinMode(irSensor1Pin, INPUT);
  pinMode(irSensor2Pin, INPUT);

  pinMode(motorSensor, OUTPUT);
}

void loop() {
  digitalWrite(motorSensor, LOW);
  // Read distance values from IR sensors
  int distance1 = digitalRead(irSensor1Pin);
  int distance2 = digitalRead(irSensor2Pin);
  Serial.println(distance1);

  // Check if only sensor 1 detects a person (entering)
  if (distance1 == 0) {
    counter++;
    Serial.print("Total: ");
    Serial.println(counter);
    delay(1000);  // Delay to prevent multiple counts for the same person
  }
  // Check if only sensor 2 detects a person (leaving)
  else if (distance2 == 0) {
    if (counter <= 0) {
      counter = 0;
    } else {
      counter--;
    }
    Serial.print("Total: ");
    Serial.println(counter);
    delay(1000);  // Delay to prevent multiple counts for the same person
  }

  if (counter >= occupancy) {
    digitalWrite(motorSensor, HIGH);
  }

  // Delay for stability
  delay(100);
}
