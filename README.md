# Autonomous Tracking Trolley
## Overview
The Autonomous Tracking Trolley is an intelligent, user-friendly solution designed to assist elderly individuals or those needing support in carrying luggage. This trolley autonomously follows its user by analyzing Wi-Fi signal strength and features advanced functionalities such as obstacle avoidance, face recognition for security, and location monitoring via an online server.

## Features
1. ### User Tracking via Wi-Fi Signal Strength
    * Measures Wi-Fi signal strength received from multiple access points.
    * Utilizes an SVM machine learning model to classify the user's region and the trolley's region.
    * Employs a mapping algorithm to navigate the trolley to the user.
2. ### Mapping Feature
    * Users can send the trolley to a specific location via the mapping system.
3. ### Security Feature
    * Locker access is secured using Face ID recognition via a camera.
4. ### Online Monitoring via Firebase
    * Tracks the battery charge percentage and requests recharging when necessary.
    * Monitors the trolley's real-time location using a GPS sensor.
5. ### Obstacle Avoidance
    * Ultrasonic sensors detect obstacles to ensure safe navigation.
## System Architecture
## Microcontrollers
  * **Arduino Uno**: Controls ultrasonic sensors and handles obstacle avoidance and communicates with the ATmega32 via I2C protocol.
  * **ATmega32**: Controls the 4 DC motors through H-bridges.
  * **ESP32**: One ESP32 gathers Wi-Fi signal strength and applies the mapping algorithm. Another ESP32 monitors the battery and location, sending data to the online server.
## Communication Protocols
  * **I2C**: Used between Arduino Uno and ATmega32 for obstacle-related commands.
  * **UART**: Used between ESP32 and ATmega32 for mapping-related commands.
  * **ESP-NOW**: Enables communication between the user and the trolley.
## Motor Control
  * 4 DC motors and 4 wheels are controlled by 2 H-bridges for movement and navigation.
## Additional Components
* Ultrasonic sensors for obstacle detection.
* Camera for face recognition.
* GPS sensor for location tracking.
## System Workflow
1. ### Tracking the User
    * Measure Wi-Fi signal strength and classify regions using SVM.
    * Use mapping algorithms to navigate the trolley.
2. ### Mapping and Navigation
    * The user can send commands to the trolley for specific destinations.
3. ### Security and Monitoring
    * Face ID recognition for locker security.
    * Firebase server for monitoring battery status and location.
4. ### Obstacle Avoidance
    * Ultrasonic sensors trigger immediate stops via external interrupt and rerouting when obstacles are detected.
## Technologies Used
 * **Hardware**: Arduino Uno, ATmega32, ESP32, Ultrasonic sensors, GPS sensor, Camera, DC Motors, H-bridges.
 * **Machine Learning**: SVM for region classification.
 * **Cloud Services**: Firebase for battery and location monitoring.
 * **Communication**: I2C, UART, ESP-NOW.
## Prototype
<div style="display: flex; flex-wrap: wrap; justify-content: center; gap: 10px;">
  <img src="https://github.com/user-attachments/assets/e18923ca-410c-4148-92d4-ed0d48210340" alt="Description 1" style="width: 200px; height: 200px; object-fit: cover;">
  <img src="https://github.com/user-attachments/assets/db5297d6-aefa-46b7-a831-f97a42fdc250" alt="Description 2" style="width: 200px; height: 200px; object-fit: cover;">
  <img src="https://github.com/user-attachments/assets/e9dae197-a8ea-4620-8718-a4438d47ae61" alt="Description 3" style="width: 200px; height: 200px; object-fit: cover;">
  <img src="https://github.com/user-attachments/assets/ebebf11a-f129-4726-b979-cf41d978d8a4" alt="Description 4" style="width: 200px; height: 200px; object-fit: cover;">
</div>

