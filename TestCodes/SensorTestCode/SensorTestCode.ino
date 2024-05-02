const int pin1 = A0;
const int pin2 = A1;
void setup() {
  // put your setup code here, to run once:
Serial.begin(4800);

}

void loop() {
  // put your main code here, to run repeatedly:

  float distance1 = readSensorValue(pin1);
  float distance2 = readSensorValue(pin2);

  Serial.print("distance1: ");
  Serial.print(distance1);

  Serial.print("     distance2: ");
  Serial.print(distance2);
  Serial.println();

  Serial.println();

  delay(1000);
}

float readSensorValue(int pin) {
  int sensorValue = analogRead(pin);
    float voltage = sensorValue * 0.00488;
  float distanceCM = 60.374 * pow(voltage, -1.16);
  // float distance = (6787.0 / (sensorValue - 3.0)) - 4.0;
  return distanceCM;
}

