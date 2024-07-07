Smart Parking System
A smart parking system using Arduino and ESP32 to assure connection via a mobile app to control the parking gate and state.

Description
This project aims to design a smart parking system to enhance traditional parking management through automation and real-time monitoring. Using Arduino and ESP32, the system automates managing parking spaces, providing instant updates to parking owners via a mobile application.

Key components include:

Two ultrasonic sensors: Detect vehicle presence and absence.
Servo motor: Controls the entry barrier.
LCD module: Displays real-time parking status.
ESP32 microcontroller: Facilitates communication with the mobile app, allowing the owner to access the parking remotely.
The system addresses the increasing demand for efficient parking solutions due to urbanization and vehicle ownership growth. By providing automated, reliable, and user-friendly solutions, this project represents a significant advancement in parking management technology.

Table of Contents
Installation
Usage
Features
Contributing
License
Contact
Installation
Arduino Setup
Hardware Connections:

Connect Ultrasonic Sensor 1 to Arduino Uno:
Trig pin -> Pin 12
Echo pin -> Pin 11
GND pin -> Ground
Vcc pin -> 5V
Connect Ultrasonic Sensor 2 to Arduino Uno:
Trig pin -> Pin 9
Echo pin -> Pin 10
GND pin -> Ground
Vcc pin -> 5V
Connect Servo Motor to Arduino Uno:
Signal pin -> Pin 13
Power pin -> 5V
GND pin -> Ground
Connect LCD Module to Arduino Uno:
SDA pin -> Pin A4
SCL pin -> Pin A5
Vcc pin -> 5V
GND pin -> Ground
Connect ESP32 to Arduino Uno:
Pin 3 (Arduino) -> 1k resistor -> Pin 18 (ESP32)
Pin 18 (ESP32) -> 2k resistor -> GND
Pin 19 (ESP32) -> Pin 2 (Arduino)
Software Setup:

Install the Arduino IDE from here.
Install necessary libraries: Servo.h, Wire.h, LiquidCrystal_I2C.h, SoftwareSerial.h, WiFi.h, WiFiClientSecure.h, UniversalTelegramBot.h, ArduinoJson.h, HTTPClient.h.
Upload Code:

Open arduinoCode.ino in the Arduino IDE.
Select the correct board and port.
Upload the code to the Arduino Uno.
ESP32 Setup
Software Setup:

Install the ESP32 board in the Arduino IDE. Follow the instructions here.
Upload Code:

Open esp32.ino in the Arduino IDE.
Select the ESP32 board and port.
Upload the code to the ESP32.
Usage
Connect the hardware components as described in the Installation section.
Upload the provided codes to the respective boards (Arduino and ESP32).
Connect the mobile app (using Telegram) to control the parking system.
Use the mobile app to open/close the gate and monitor the parking status.
Features
Real-time monitoring: Provides instant updates on parking status.
Remote control: Allows owners to control the parking gate remotely via a mobile app.
Automated gate control: Automatically opens/closes the gate based on vehicle detection.
LCD display: Shows the number of available parking spots.
Contributing
Contributions are welcome! Please fork this repository and submit a pull request with your changes. For major changes, please open an issue first to discuss what you would like to change.

License
This project is licensed under the MIT License.

Contact
Author: Rasha Hammoud
Supervisors: Dr. Abed Ellatif Samhat, Dr. Rida El-Chall
For further information or queries, please contact us.