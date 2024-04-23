const int motorSensor = 5;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Set IR sensor pins as inputs
  pinMode(motorSensor, OUTPUT);

  
  // digitalWrite(motorSensor, LOW);
  // delay(750);
  digitalWrite(motorSensor, HIGH);
  delay(575); //575 (3/4) //75 (1/4)
  digitalWrite(motorSensor, LOW);
}


void loop() {
}
