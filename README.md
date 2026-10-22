# 🚗 Smart Parking System

An **Arduino- and ESP32-based Smart Parking System** that combines vehicle detection, automated gate control, and remote monitoring through a Telegram bot.

## 📌 Overview

The Smart Parking System aims to simplify parking management by automating vehicle detection and providing remote access to parking controls. Built using **Arduino Uno, ESP32, ultrasonic sensors, and a servo motor**, the system detects vehicle presence, manages the entry barrier, and displays parking availability in real time.

An ESP32 provides Wi-Fi connectivity, allowing the parking owner to monitor the system and remotely control the gate through a Telegram bot.

This project explores the integration of **embedded systems, sensor-based automation, and IoT communication** to create a practical solution for smarter parking management.

## ✨ Features

- **🚘 Vehicle Detection:** Two ultrasonic sensors detect vehicle presence and absence.
- **🚧 Automated Gate Control:** A servo motor operates the parking barrier.
- **📱 Remote Access:** Open or close the gate remotely through a Telegram bot.
- **📡 IoT Connectivity:** ESP32 enables wireless communication over Wi-Fi.
- **🖥️ Real-Time Display:** An LCD module displays parking availability.
- **⚙️ Embedded Integration:** Arduino Uno handles sensor inputs and hardware control, while the ESP32 manages network communication.

## 🛠️ Hardware Components

| Component | Purpose |
|---|---|
| Arduino Uno | Main controller for sensor readings and gate automation |
| ESP32 | Wi-Fi connectivity and remote communication |
| 2 × Ultrasonic sensors | Vehicle detection |
| Servo motor | Parking barrier control |
| I2C LCD module | Parking status display |
| Resistors and jumper wires | Circuit connections and signal interfacing |

## 🏗️ System Architecture

The system is divided into two main parts:

1. **Arduino Uno — Local Control:** Reads ultrasonic sensor measurements, controls the servo motor, and updates the LCD display.
2. **ESP32 — Wireless Communication:** Connects to Wi-Fi and communicates with the Telegram bot to support remote monitoring and gate control.

The two microcontrollers exchange information through serial communication.

```text
    Ultrasonic Sensors
             │
             ▼
       ┌───────────┐
       │ Arduino   │
       │   Uno     │
       └─────┬─────┘
             │
       Serial Communication
             │
             ▼
       ┌───────────┐
       │   ESP32   │◄──────► Wi-Fi
       └───────────┘           │
                               ▼
                         Telegram Bot
                         (Remote Control)

       Arduino Uno
          │     │
          ▼     ▼
       Servo   I2C LCD
       Motor   Display
```

## 🔌 Hardware Connections

### Arduino Uno

**Ultrasonic Sensor 1**

| Pin | Arduino connection |
|---|---|
| TRIG | Digital pin 12 |
| ECHO | Digital pin 11 |
| VCC | 5V |
| GND | GND |

**Ultrasonic Sensor 2**

| Pin | Arduino connection |
|---|---|
| TRIG | Digital pin 9 |
| ECHO | Digital pin 10 |
| VCC | 5V |
| GND | GND |

**Servo Motor**

| Pin | Arduino connection |
|---|---|
| Signal | Digital pin 13 |
| Power | 5V supply, as appropriate for the servo |
| GND | GND |

**I2C LCD Module**

| Pin | Arduino connection |
|---|---|
| SDA | A4 |
| SCL | A5 |
| VCC | 5V, if supported by the module |
| GND | GND |

### Arduino Uno ↔ ESP32

The microcontrollers communicate using serial signals.

| Connection | Purpose |
|---|---|
| Arduino pin 3 → 1 kΩ resistor → ESP32 GPIO18 | Serial signal with voltage-divider network |
| ESP32 GPIO18 → 2 kΩ resistor → GND | Voltage-divider connection |
| ESP32 GPIO19 → Arduino pin 2 | Return serial signal |

> **⚠️ Important:** Verify that these connections match the serial interfaces configured in your source code. The ESP32 uses **3.3 V logic and its GPIO pins are not 5 V tolerant**. Ensure that any signal originating from the Arduino Uno is level-shifted appropriately before reaching an ESP32 input. Do not connect the Arduino's 5 V TX signal directly to an ESP32 GPIO.

## 💻 Software Requirements

- [Arduino IDE](https://www.arduino.cc/en/software)
- Arduino Uno board support
- [ESP32 board support](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html)
- A Telegram account and bot token
- Wi-Fi network access

### Required Libraries

Install the libraries used by your source code through the Arduino IDE Library Manager or the appropriate library installation method.

**Arduino Uno**
- `Servo.h`
- `Wire.h`
- `LiquidCrystal_I2C.h`
- `SoftwareSerial.h`

**ESP32**
- `WiFi.h`
- `WiFiClientSecure.h`
- `UniversalTelegramBot.h`
- `ArduinoJson.h`
- `HTTPClient.h`

Some libraries are included with the relevant board packages, while others must be installed separately.

## 🚀 Installation and Setup

### 1. Clone the Repository

```bash
git clone https://github.com/rasha-hmd/Smart-Parking-System.git
cd Smart-Parking-System
```

Replace the repository URL with the actual GitHub repository URL if the project uses a different name or path.

### 2. Configure the Arduino Uno

1. Open `arduinoCode.ino` in the Arduino IDE.
2. Install the required libraries.
3. Select **Arduino Uno** as the board.
4. Select the correct serial port.
5. Connect the hardware according to the wiring tables.
6. Upload the sketch.

### 3. Configure the ESP32

1. Install ESP32 board support in the Arduino IDE.
2. Open `esp32.ino`.
3. Configure the Wi-Fi credentials and Telegram bot settings as required by the source code.
4. Select the correct ESP32 board and serial port.
5. Upload the sketch.

**Security note:** Keep Wi-Fi passwords and Telegram bot tokens private. Avoid committing real credentials to a public repository.

### 4. Set Up Telegram

1. Create a Telegram bot using [@BotFather](https://t.me/BotFather).
2. Obtain the bot token.
3. Configure the token and any required chat ID in the ESP32 sketch.
4. Connect the ESP32 to a Wi-Fi network.
5. Start a conversation with your bot and test the commands implemented in the code.

## 📲 Usage

Once the hardware and software are configured:

1. Power on both microcontrollers.
2. Wait for the ESP32 to establish its Wi-Fi connection.
3. Monitor parking availability on the LCD.
4. Use the Telegram bot to check parking status and control the gate.
5. Allow the ultrasonic sensors to detect vehicle presence and update the system accordingly.

The exact Telegram commands and gate-control behavior depend on the implementation in `esp32.ino` and `arduinoCode.ino`.

## 📂 Project Structure

```text
Smart-Parking-System/
├── arduinoCode.ino    # Arduino Uno: sensors, servo and LCD
├── esp32.ino          # ESP32: Wi-Fi and Telegram communication
└── README.md          # Project documentation
```

Adjust the structure above to match the actual repository files.

## 🎯 Project Objectives

- Apply microcontroller programming to a real-world automation problem.
- Integrate sensors and actuators into an embedded system.
- Establish serial communication between two microcontrollers.
- Explore IoT connectivity and remote hardware control.
- Develop a user-friendly approach to monitoring parking availability.

## 🔮 Possible Improvements

- Add a mobile application with a dedicated graphical interface.
- Introduce additional parking sensors to monitor multiple spaces.
- Implement user authentication and more robust remote-access security.
- Add historical parking data and usage statistics.
- Improve fault detection and communication reliability.

## 🤝 Contributing

Contributions and suggestions are welcome.

1. Fork the repository.
2. Create a feature branch.
3. Commit your changes.
4. Submit a pull request describing the improvements.

For significant changes, consider opening an issue first to discuss the proposed solution.

## 📄 License

This project is intended to be licensed under the MIT License. Include a `LICENSE` file containing the MIT License text in the repository to make the licensing explicit.

## 👩‍💻 Authors

**Rasha Hammoud**

Academic supervisors:
- Dr. Abed Ellatif Samhat
- Dr. Rida El-Chall

For questions or further information, feel free to open an issue in the repository.

---

*Developed as an embedded systems and IoT project exploring automated parking management.*
