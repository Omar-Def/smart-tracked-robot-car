/****************************************************
 * SMART SECURITY SYSTEM (NO LCD)
 * Components:
 * - PIR sensor (motion detection)
 * - Ultrasonic sensor (distance detection)
 * - 4 LEDs (status indicators)
 * - Buzzer (alarm)
 * - Joystick (arm/disarm + mode control)
 * - Potentiometer (sensitivity control)
 ****************************************************/

// ---------------- PIN DEFINITIONS ----------------

// Ultrasonic
const int trigPin = 8;
const int echoPin = 9;

// PIR
const int pirPin = 10;

// Buzzer
const int buzzerPin = 12;

// LEDs
const int greenLED = 2;
const int yellowLED = 3;
const int redLED = 4;
const int blueLED = 5;

// Joystick
const int joyButton = 11;

// Potentiometer
const int potPin = A2;

// ---------------- SYSTEM STATE ----------------

bool systemArmed = false;
int mode = 0; // 0 = normal, 1 = test/radar style (future expansion)

unsigned long lastButtonPress = 0;
const int debounceDelay = 300;

// ---------------- SETUP ----------------

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(pirPin, INPUT);

  pinMode(buzzerPin, OUTPUT);

  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(blueLED, OUTPUT);

  pinMode(joyButton, INPUT_PULLUP);

  Serial.begin(9600);
}

// ---------------- ULTRASONIC FUNCTION ----------------

long readDistanceCM() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000); // timeout 30ms

  long distance = duration * 0.034 / 2;

  return distance;
}

// ---------------- BUZZER PATTERNS ----------------

void safeBeep() {
  noTone(buzzerPin);
}

void warningBeep() {
  tone(buzzerPin, 800, 100);
}

void alertBeep() {
  tone(buzzerPin, 1500, 200);
}

// ---------------- LED CONTROL ----------------

void setLEDs(bool g, bool y, bool r, bool b) {
  digitalWrite(greenLED, g);
  digitalWrite(yellowLED, y);
  digitalWrite(redLED, r);
  digitalWrite(blueLED, b);
}

// ---------------- JOYSTICK HANDLER ----------------

void handleJoystick() {
  if (digitalRead(joyButton) == LOW) {
    if (millis() - lastButtonPress > debounceDelay) {
      systemArmed = !systemArmed;
      lastButtonPress = millis();
    }
  }
}

// ---------------- MAIN LOOP ----------------

void loop() {

  handleJoystick();

  // Potentiometer controls sensitivity
  int potValue = analogRead(potPin);

  // Map sensitivity threshold (adjustable)
  int dangerThreshold = map(potValue, 0, 1023, 50, 200);

  // Read sensors
  bool motionDetected = digitalRead(pirPin);

  long distance = readDistanceCM();

  // Debug
  Serial.print("Armed: ");
  Serial.print(systemArmed);
  Serial.print(" | Motion: ");
  Serial.print(motionDetected);
  Serial.print(" | Distance: ");
  Serial.print(distance);
  Serial.print(" cm");
  Serial.print(" | Threshold: ");
  Serial.println(dangerThreshold);

  // ---------------- SYSTEM OFF ----------------

  if (!systemArmed) {
    setLEDs(0, 0, 0, 1); // Blue ON
    safeBeep();
    delay(200);
    return;
  }

  // ---------------- SAFE STATE ----------------

  if (!motionDetected && (distance > dangerThreshold || distance == 0)) {
    setLEDs(1, 0, 0, 0); // Green
    safeBeep();
    delay(200);
    return;
  }

  // ---------------- WARNING STATE ----------------

  if (motionDetected || (distance <= dangerThreshold && distance > dangerThreshold / 2)) {
    setLEDs(0, 1, 0, 0); // Yellow
    warningBeep();
    delay(150);
    return;
  }

  // ---------------- ALERT STATE ----------------

  if (distance > 0 && distance <= dangerThreshold / 2) {
    setLEDs(0, 0, 1, 0); // Red

    // Rapid alarm
    alertBeep();
    delay(80);
    alertBeep();
    delay(80);

    return;
  }
}
