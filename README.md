# 🚜 Smart Multi-Function Tracked Robot Tank

An advanced tracked robot platform powered by an **Arduino Uno** and **ESP32**, featuring WiFi connectivity, obstacle detection, ambient sound alarm system, and custom track-drive mechanics.

---

## 📸 Overview & Features

<img width="720" height="1280" alt="image" src="https://github.com/user-attachments/assets/0ea57939-84e3-4f9c-8110-34c3428b42f4" />

<img width="720" height="1280" alt="image" src="https://github.com/user-attachments/assets/4f95a219-4441-4142-aa1a-290bd8600dbc" />

### Demo Video
https://github.com/user-attachments/assets/6095ce28-f1f4-445e-a9a6-0f81646c7f03

- **Tracked Chassis (Tank Drive):** High-traction dual-track movement system for versatile terrain navigation.
- **Dual Processing Architecture:**
  - **ESP32:** Handles WiFi wireless control, camera streaming, and high-level logic.
  - **Arduino Uno:** Manages low-level sensor reading (PIR, Ultrasonic), status indicators (LEDs), and audio alerts (Buzzer).
- **Obstacle Avoidance & Radar:** Ultrasonic sensor mounted on a Servo motor for scanning ahead.
- **Integrated Security System:** Built-in motion detection, adjustable sensitivity threshold via potentiometer, and multi-LED indicator states.

---

## 🛠️ Hardware Components

- **Main Controllers:** Arduino Uno & ESP32 / ESP32-CAM
- **Chassis:** Tracked Tank Chassis with DC Motors
- **Sensors:**
  - Ultrasonic Sensor (HC-SR04)
  - PIR Motion Sensor
  - IR Line Tracking Sensors
- **Actuators & Output:**
  - SG90 Micro Servo Motor
  - Piezo Buzzer
  - Status LEDs (Blue, Green, Yellow, Red)
- **Control & Power:**
  - Potentiometer (Sensitivity adjustment)
  - Joystick Pushbutton (Arm/Disarm)
  - 3.7V Li-ion Rechargeable Batteries

---

## 📂 Repository Structure

```text
├── src/
│   ├── arduino_security.ino   # Arduino Uno code for security & sensor alerts
│   └── esp32_robot_car.ino    # ESP32 code for motor control & WiFi connectivity
└── README.md                  # Project documentation
