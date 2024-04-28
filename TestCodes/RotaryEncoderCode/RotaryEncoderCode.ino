#define ENCODER_PIN1 2 // clk -> clockwise roation
#define ENCODER_PIN2 3 // dt -> ccw roation
#define BUTTON_PIN 4 // button

volatile long encoderPos = 0;
int lastEncoded = 0;
boolean buttonState = false;
boolean lastButtonState = false;
  
void setup() {
  Serial.begin(9600);

  pinMode(ENCODER_PIN1, INPUT_PULLUP);
  pinMode(ENCODER_PIN2, INPUT_PULLUP);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(ENCODER_PIN1), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER_PIN2), updateEncoder, CHANGE);
}

void loop() {
  Serial.print("EncoderPos: ");
  Serial.println(encoderPos);
  buttonState = digitalRead(BUTTON_PIN);
  
  if (buttonState == LOW && lastButtonState == HIGH) {
    encoderPos = ceilToMultipleOfTen(encoderPos);
    Serial.print("Rounded value to ceiling of 10: ");
    Serial.println(encoderPos);
  }
  
  lastButtonState = buttonState;
  
  delay(100); // Add delay to prevent rapid button presses
}

int ceilToMultipleOfTen(double x) {
  int n = x;
  if (n % 10) {
    n = n + (10 - n % 10);
  }
  return n;
}


void updateEncoder() {
  int MSB = digitalRead(ENCODER_PIN1);
  int LSB = digitalRead(ENCODER_PIN2);

  int encoded = (MSB << 1) | LSB;

  int sum = (lastEncoded << 2) | encoded;

  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) {
    encoderPos++;
  } else if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) {
    encoderPos--;
  }

  lastEncoded = encoded;
}
