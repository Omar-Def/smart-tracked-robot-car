# 🚜 Smart Multi-Function Tracked Robot Tank

An advanced tracked robot platform powered by an **Arduino Uno** and **ESP32**, featuring WiFi connectivity, obstacle detection, ambient sound alarm system, and custom track-drive mechanics.

---

## 📸 Overview & Features
<p align="center">
  <img src="https://github.com/user-attachments/assets/b71c1c3d-4931-4114-9ed5-48b4ddc515a4" width="300" />
  <img src="https://github.com/user-attachments/assets/a4b186c8-8747-4c6f-8717-d23d4286218d" width="300" />
</p>

<p align="center">
  <video src="https://github.com/user-attachments/assets/872ac5d8-5d94-49a6-8da2-7cbcc0ddf8a3" width="600" controls></video>
</p>
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
