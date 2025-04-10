# Arduino Smart Electric Vehicle 

This repository contains the complete source code and documentation for a smart electric vehicle prototype built and evolved across multiple academic projects at Drexel University. The system models a miniaturized intelligent car with adaptive driving logic, real-time environmental sensing, secure access, and live telemetry visualization - designed to simulate core elements of modern autonomous vehicles.

---

## Project Evolution

### 🔹 Phase 1: ENGR 113 – Freshman Design ("The Backseat Driver")
- Constructed a remote-controlled (RC) car with a 4-wheel base and a mounted Arduino microcontroller for embedded control.
- Designed a gesture-based glove controller worn by the user, featuring an MPU6050 sensor (accelerometer + gyroscope) and an Arduino Nano/Uno to capture real-time hand motion and orientation.
- Integrated a servo motor to enable precise left and right steering functionality.
- Users could tilt their hand to move the car forward, left, or right.
- Implemented wireless communication using NRF24L01 modules to transmit sensor data from the hand controller to the car.
- Focused on **rapid prototyping**, 3D modeling, SolidWorks, basic Arduino motor control, and accelerometer integration.
- Achieved responsive gesture control with an average delay of just **~0.2 seconds**.

### 🔹 Phase 2: ECE 303 – Embedded Systems Test-Bed (Individual Build)
- Rebuilt the system with added **collision avoidance**, **adaptive speed control**, **live dashboard**, and **sensor integration**.
- Introduced **RFID authentication**, **IR remote control**, and **buzzer alerts**.
- Developed a custom **MATLAB GUI** to display live data (distance, motor speed, temperature, coolant level, headlight status).
- Implemented **PWM-based motor logic** to adjust speed based on sensor data using `analogWrite()`.
- Used **LCD** and **serial communication** for redundant, on-device visualization.

---

## Features

-  **RFID Authentication**  
  Prevents unauthorized users from starting the vehicle. Each card’s UID is verified before activation.

-  **Ultrasonic Obstacle Detection & Speed Control**  
  Dynamically adjusts motor speed or halts the car completely based on object distance.

-  **Environmental Monitoring**  
  Real-time tracking of temperature (via DHT11).

- **IR Remote Input**  
  Used to control headlight intensity and simulate user interaction.

- **LCD Display**  
  Displays sensor readings and vehicle status — temperature, motor speed, coolant levels.

- **Live MATLAB Dashboard**  
  Reads serial data from the Arduino and displays it as a digital dashboard with warning indicators.

-  **Modular, Real-Time Logic**  
  Implements sensor fusion and decision-making for autonomous behavior using C++ classes and timers.

---

## 🛠Technologies Used

### Hardware
- Arduino Mega 2560  
- HC-SR04 Ultrasonic Distance Sensor  
- DHT11 Temperature and Humidity Sensor  
- MFRC522 RFID Module  
- AX-1838HS IR Receiver  
- LCD1602 Display  
- Buzzer and LEDs  
- DC Motor & Motor Driver  
- Potentiometer (optional manual speed control)

### Software
- C/C++ (Arduino)  
- PlatformIO & Arduino IDE  
- MATLAB App Designer (GUI)  
- Serial Communication Protocol  
- Custom Libraries: `digitalpin`, `IRremote`, `LiquidCrystal`, `MFRC522`, `DHT`

---

##  Repository Structure

```
ArduinoSmartCar/
├── .pio/                    # servo codes
├── src/                     # Main logic for the vehicle
├── lib/                     # Custom & third-party libraries
│   ├── IRremote             # IR remote decoding logic
│   ├── MFRC522              # RFID tag reading & security
│   ├── digitalpin           # Direct register manipulation for custom IO
│   ├── liquidcrystal        # LCD driver library
│   └── dht                  # Temperature/humidity sensing
├── include/                 # Class headers and support files
├── test/                    # Placeholder for unit tests
├── platformio.ini           # PlatformIO board config 
└── README.md                # You’re reading it!
```

---

##  System Behavior Logic

| Distance to Obstacle | Motor Speed     | LED Feedback        |
|----------------------|------------------|----------------------|
| > 50 cm              | Full speed       | All OFF              |
| 35–50 cm             | Medium speed     | 1 LED ON             |
| 15–35 cm             | Low speed        | 2 LEDs ON            |
| < 15 cm              | Stop             | 3 LEDs or buzzer     |

Additionally:
- Headlights can be set to **off, dim, or bright** via remote.
- Warnings are displayed in **MATLAB GUI** if coolant is low or temperature exceeds safe thresholds.

---
## Project Preview:

## Freshmen Design:
![image](https://github.com/user-attachments/assets/150b59ef-0410-4a13-8397-ebaa02cd26a7)

![image](https://github.com/user-attachments/assets/b9515faf-d9e5-4145-ac79-7d2ed1bd3b4c)


## ECE 303 - Project Continuation
![image](https://github.com/user-attachments/assets/f94a9169-f4d0-4355-95c2-9b994cdec0f0)
![image](https://github.com/user-attachments/assets/b8379c39-a6e4-47f3-ad40-657dbe45e85e)
![image](https://github.com/user-attachments/assets/f0310120-84dc-423b-86b3-d0818572fafb)
![image](https://github.com/user-attachments/assets/ea50561d-d6ce-49ee-b4a9-b87f6f535693)
![image](https://github.com/user-attachments/assets/6af610a8-8547-45c7-adea-5d83828b7f4c)

![image](https://github.com/user-attachments/assets/f17cfcad-43f5-4e46-90ec-4473ec7f54c5)



###  Academic Acknowledgment

Portions of this project were developed for:
- **ENGR 113 – First-Year Design**  
- **ECE 303 – Embedded Systems Lab**

Special thanks to Drexel ECE Department for their guidance.
