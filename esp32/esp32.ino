#define RXD2 18
#define TXD2 19
// Initialize Telegram BOT
#define BOTtoken "**********************************"  // Bot Token 
#define CHAT_ID "********"

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>   // Universal Telegram Bot Library written by Brian Lough: https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot
#include <ArduinoJson.h>
#include <HTTPClient.h>


// Replace with your network credentials
const char* ssid = "********";
const char* password = "*******";


WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

volatile int carsInParking = 0; // Initialize the number of cars in the parking
bool newData = false;

// Handle new receive messages
void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));
  for (int i=0; i<numNewMessages; i++) {
    // Chat id of the requester
    String chat_id = String(bot.messages[i].chat_id);
    if (chat_id != CHAT_ID){
      bot.sendMessage(chat_id, "Unauthorized user", "");
      continue;
    }
    // Print the received message
    String text = bot.messages[i].text;
    Serial.println(text);
    String from_name = bot.messages[i].from_name;
    if (text == "/start") {
      String welcome = "Welcome, " + from_name + ".\n";
      welcome += "Use the following commands to control your outputs.\n\n";
      welcome += "/enable to enable the automation of parking\n";
      welcome += "/disable to disable the automation of parking \n";
      welcome += "/open to open the gate \n";
      welcome += "/close to close the gate \n";
      welcome += "/state to request parking state \n";
      bot.sendMessage(chat_id, welcome, "");
    }
    if (text == "/enable") {
      bot.sendMessage(chat_id, "The parking is now automated", "");
      Serial2.println("ENABLE");
    }
    if (text == "/disable") {
      bot.sendMessage(chat_id, "The automation is disabled", "");
      Serial2.println("DISABLE-");
    }
    if (text == "/open") {
      bot.sendMessage(chat_id, "The gate is opening..", "");
      Serial2.println("OPEN");
    }
    if (text == "/close") {
      bot.sendMessage(chat_id, "The gate is closing..", "");
      Serial2.println("CLOSE");
    }
    if (text == "/state") {
      Serial.println(carsInParking);
      bot.sendMessage(chat_id, "Cars in parking: " + String(carsInParking), "");
    }
}
}

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);

  client.setInsecure();

  // Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  WiFi.setSleep(false);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());
  testTelegramConnection(BOTtoken);
}
void loop() {
    if (Serial2.available()) {
    String data = Serial2.readStringUntil('\n');
    if (data.length() > 0) {
      carsInParking = data.toInt();
      newData = true;
    }
  }
  int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
  if (numNewMessages > 0) {
      Serial.println("New messages received.");
      handleNewMessages(numNewMessages);
    } else {
      Serial.println("No new messages.");
    }
    if (newData) {
    Serial.println("Updated cars in parking: " + String(carsInParking));
    newData = false;
    }
    delay(1000);
}

void testTelegramConnection(const char* token) {
  HTTPClient http;

  // Construct the URL for sending a message
  String url = "https://api.telegram.org/bot";
  url += token;
  url += "/sendMessage";

  Serial.print("Testing connection to Telegram API...");

  // Prepare the message payload
  String message = "Welcome!";
  String payload = "chat_id=";
  payload += CHAT_ID;
  payload += "&text=";
  payload += message;

  // Send a POST request to the Telegram API
  http.begin(url);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpResponseCode = http.POST(payload);

  if (httpResponseCode > 0) {
    // If the request was successful, print the response
    String response = http.getString();
    Serial.println("Message sent successfully!");
    Serial.println("Response from Telegram API:");
    Serial.println(response);
  } else {
    // If the request failed, print the error code
    Serial.print("Failed to connect to Telegram API. Error code: ");
    Serial.println(httpResponseCode);
  }

  http.end();

  // Print ending message
  Serial.println("Test complete.");
}
