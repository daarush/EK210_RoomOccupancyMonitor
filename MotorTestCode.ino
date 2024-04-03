const int motorSensor = 5;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Set IR sensor pins as inputs
  pinMode(motorSensor, OUTPUT);
}


void loop() {
  digitalWrite(motorSensor, LOW);
  delay(1000);
  digitalWrite(motorSensor, HIGH);
  delay(1000);
}
