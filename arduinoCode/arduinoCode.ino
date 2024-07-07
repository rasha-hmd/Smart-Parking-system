#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

// Define the LCD address and dimensions
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Define SoftwareSerial pins for communication with ESP32
SoftwareSerial mySerial(2, 3); // RX, TX

Servo servo; // Servo for gate and parking area

int trigPin1 = 12; // Trigger pin for the first ultrasonic sensor
int echoPin1 = 11;  // Echo pin for the first ultrasonic sensor

int trigPin2 = 9;  // Trigger pin for the second ultrasonic sensor
int echoPin2 = 10;  // Echo pin for the second ultrasonic sensor

// Defines variables
long duration1;
long duration2;
int distance1;
int distance2;

const int totalParkingSpots = 10; // Total number of parking spots
int carsInParking = 0; // Number of cars currently in the parking

bool gateOpen = false;
bool parkingState=false;

void setup() {
  Serial.begin(9600); // Initialize serial communication with computer
  mySerial.begin(9600); // Initialize serial communication with ESP32

  // Setup for servo
  servo.attach(13); // Attach servo to pin 13
  servo.write(90); // Initial position of the gate (closed)
  delay(100);

  // Setup for ultrasonic sensors
  pinMode(trigPin1, OUTPUT); // Set trigPin1 as an Output
  pinMode(echoPin1, INPUT);  // Set echoPin1 as an Input
  
  pinMode(trigPin2, OUTPUT); // Set trigPin2 as an Output
  pinMode(echoPin2, INPUT);  // Set echoPin2 as an Input

  // Setup for LCD
  lcd.init();        // Initialize the LCD
  lcd.backlight();   // Turn on the backlight
  lcd.print("Parking System");
  delay(2000);
  updateLCD();
}

void loop() {
  String State = mySerial.readStringUntil('\n'); // Read the command from ESP32
  State.trim(); // Remove leading and trailing whitespace
  Serial.println("Received State"+State);
  if (State.equals("ENABLE")) {
  parkingState=true;
  Serial.println("Received command: ENABLE");
} else if(State.equals("DISABLE-")){
  parkingState=false;
  Serial.println("Received command: DISABLE");
}

  // Measure distance from first ultrasonic sensor
  distance1 = measureDistance(trigPin1, echoPin1);
  
  // Measure distance from second ultrasonic sensor
  distance2 = measureDistance(trigPin2, echoPin2);

if(parkingState==true){
  // Check car entry or exit
  if (distance1 <= 13 && distance2 > 13 && carsInParking < totalParkingSpots) {
    // Car detected by sensor 1 first
    openGate();
    delayUntilCarDetected(trigPin2, echoPin2); // Wait until sensor 2 detects the car
    if (carsInParking < totalParkingSpots) {
      carsInParking++;
      mySerial.println(carsInParking);
      Serial.println("Car Entered");
    }
  } else if (distance2 <= 13 && distance1 > 13 && carsInParking > 0) {
    // Car detected by sensor 2 first
    openGate();
    delayUntilCarDetected(trigPin1, echoPin1); // Wait until sensor 1 detects the car
    if (carsInParking > 0) {
      carsInParking--;
      mySerial.println(carsInParking);
      Serial.println("Car Exited");
    }
  }

  // Close the gate after a fixed delay if it's open
  if (gateOpen) {
    delay(3000); // Keep the gate open for 3 seconds
    closeGate();
  }
}
String command = mySerial.readStringUntil('\n'); // Read the command from ESP32
command.trim(); // Remove leading and trailing whitespace

if (command.equals("OPEN")) {
  openGate(); // Open the gate
  Serial.println("Received command: OPEN");
  if (distance1 <= 13 && distance2 > 13 && carsInParking < totalParkingSpots){
     carsInParking++;
     mySerial.println(carsInParking);
     Serial.println("Car Entered");
     delay(3000);
  }else if (distance2 <= 13 && distance1 > 13 && carsInParking > 0){
    carsInParking--;
    mySerial.println(carsInParking);
    Serial.println("Car Exited");
    delay(3000);
  }
} else if (command.equals("CLOSE")) {
  closeGate(); // Close the gate
  Serial.println("Received command: CLOSE");
}

  // Update LCD display
  updateLCD();
  Serial.println(carsInParking); // Send carsInParking to serial monitor
  //mySerial.println(carsInParking);

  delay(100); // Short delay before next loop iteration
}

int measureDistance(int trigPin, int echoPin) {
  // Clear the trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Set the trigger pin HIGH for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echo pin, returns the sound wave travel time in microseconds
  long duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in cm
  int distance = duration * 0.034 / 2;

  return distance;
}

void delayUntilCarDetected(int trigPin, int echoPin) {
  int distance;
  do {
    distance = measureDistance(trigPin, echoPin);
  } while (distance > 13);
}

void openGate() {
  servo.write(0); // Open the gate
  gateOpen = true;
}

void closeGate() {
  servo.write(90); // Close the gate
  gateOpen = false;
}

void updateLCD() {
  lcd.clear();
  if (carsInParking >= totalParkingSpots) {
    lcd.print("Parking is Full");
  } else {
    lcd.print("Free Spots: ");
    lcd.print(totalParkingSpots - carsInParking);
  }
}

