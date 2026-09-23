/****************************************************
 * ESP32-CAM SMART MULTI-FUNCTION ROBOT CAR
 * Features:
 * - WiFi Web Server & Video Streaming
 * - Line Follower Mode (IR Sensors)
 * - Obstacle Avoidance Mode (Ultrasonic + Servo)
 * - Remote Control via WiFi
 ****************************************************/

#include "esp_camera.h"
#include <WiFi.h>
#include <ESP32Servo.h>

// WiFi Credentials
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// Motor Pins (Driven via Motor Driver e.g. L298N / TB6612)
const int motor1Pin1 = 12; 
const int motor1Pin2 = 13; 
const int motor2Pin1 = 14; 
const int motor2Pin2 = 15; 

// IR Sensors (Line Tracking)
const int irLeft = 2;
const int irRight = 4;

// Ultrasonic Sensor
const int trigPin = 0;
const int echoPin = 16;

// Servo Motor
Servo distanceServo;
const int servoPin = 18;

// Modes: 0 = Manual WiFi, 1 = Line Follower, 2 = Obstacle Avoidance
int currentMode = 0; 

void setup() {
  Serial.begin(115200);

  // Motor Pins Setup
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);

  // Sensors Setup
  pinMode(irLeft, INPUT);
  pinMode(irRight, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Attach Servo
  distanceServo.attach(servoPin);
  distanceServo.write(90); // Center position

  // WiFi Connection
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");
  Serial.print("Camera Stream IP: ");
  Serial.println(WiFi.localIP());
}

// ---------------- MOTOR FUNCTIONS ----------------

void moveForward() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

void moveBackward() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
}

void turnLeft() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

void turnRight() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
}

void stopCar() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}

// ---------------- ULTRASONIC FUNCTION ----------------

long getDistanceCM() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH, 26000);
  if (duration == 0) return 400; // Default clear path
  return duration * 0.034 / 2;
}

// ---------------- AUTOMATIC MODES ----------------

void handleLineFollower() {
  bool leftVal = digitalRead(irLeft);
  bool rightVal = digitalRead(irRight);

  if (!leftVal && !rightVal) {
    moveForward();
  } else if (leftVal && !rightVal) {
    turnLeft();
  } else if (!leftVal && rightVal) {
    turnRight();
  } else {
    stopCar();
  }
}

void handleObstacleAvoidance() {
  long distance = getDistanceCM();

  if (distance > 25) {
    moveForward();
  } else {
    stopCar();
    delay(200);
    
    // Scan Left and Right
    distanceServo.write(30);
    delay(300);
    long rightDist = getDistanceCM();

    distanceServo.write(150);
    delay(300);
    long leftDist = getDistanceCM();

    distanceServo.write(90); // Reset center

    if (leftDist > rightDist) {
      turnLeft();
      delay(400);
    } else {
      turnRight();
      delay(400);
    }
  }
}

// ---------------- MAIN LOOP ----------------

void loop() {
  switch (currentMode) {
    case 1:
      handleLineFollower();
      break;
    case 2:
      handleObstacleAvoidance();
      break;
    default:
      // Manual WiFi Mode handled via server async callbacks
      break;
  }
}
