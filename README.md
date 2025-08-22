# Development of a Quadruped Robot with Sensor Integration and AI-based Object Detection

## 📌 Project Description

This project focuses on the design and development of a **quadruped robot** (similar to Boston Dynamics' SPOT) integrating **mechanical design, real-time control, sensor feedback, and AI-based object detection**. The system is designed for **autonomous navigation, obstacle detection, and stable locomotion**.

The robot incorporates a **SolidWorks-based mechanical structure**, an **ESP32 microcontroller** for real-time control and wireless connectivity, and multiple sensors for environmental awareness and safety.

### ✅ Key Highlights:
- **Quadruped Locomotion** with gait planning and balance control.
- **Sensor Integration** for real-time feedback.
- **AI-based Object Detection** for obstacle avoidance and recognition.
- **Wireless Connectivity** via ESP32 (Wi-Fi & Bluetooth).
- **Applications** in search and rescue, autonomous inspection, and robotics research.

---

## 🛠️ Features

- **Mechanical Design**
  - Modeled in **SolidWorks** with optimized structural components for stability and durability.

- **Control System**
  - Powered by **ESP32 microcontroller** for high-speed processing and remote communication.

- **Sensor Integration**
  - **IMU (Accelerometer, Gyroscope, Magnetometer)** – Provides orientation, acceleration, and angular velocity data for stability control.
  - **Pressure Sensors** – Mounted on feet for detecting ground contact and maintaining proper weight distribution.
  - **Temperature Sensor** – Monitors thermal conditions to prevent overheating.

- **AI-based Object Detection**
  - Implemented using **YOLO / MobileNet / TensorFlow Lite** for real-time object recognition.
  - Deployed on an edge device or onboard processor for **low-latency inference**.

---

## ⚙️ Hardware Components
- ESP32 Microcontroller
- Servo Motors (for leg actuation)
- IMU Sensor (e.g., MPU6050)
- Pressure Sensors
- Temperature Sensor
- Camera Module for vision and object detection
- Battery Pack & Power Management Circuit

---

## 💻 Software Components
- **Mechanical Design**: SolidWorks
- **Firmware**: Arduino IDE / PlatformIO
- **Object Detection**: TensorFlow Lite / OpenCV
- **Communication**: Wi-Fi & Bluetooth (ESP32)
- **Programming Languages**: C++, Python

---

## 📐 System Workflow
1. **Gait Planning** – Calculates step sequences for walking.
2. **Sensor Feedback** – IMU & pressure sensors provide stability and orientation data.
3. **Motor Control** – ESP32 controls servo motors based on gait and feedback.
4. **Object Detection** – AI model processes video feed and detects obstacles.
5. **Autonomous Navigation** – Robot adjusts path based on sensor and vision input.

---

## 🔍 Applications
- Search and Rescue Operations
- Industrial Inspection
- Autonomous Surveillance
- Robotics and AI Research

---

## 🚀 Future Enhancements
- Integration with **ROS 2** for advanced motion planning.
- SLAM (Simultaneous Localization and Mapping) for full autonomy.
- Improved AI model for multi-object recognition and tracking.

---



- Email: your.email@example.com
- GitHub: [YourGitHubProfile](https://github.com/YourGitHubProfile)
