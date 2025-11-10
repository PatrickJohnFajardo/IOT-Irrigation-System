#include <ESP8266WiFi.h>  // Use <WiFi.h> for ESP32
#include <LiquidCrystal_I2C.h>  // Optional: I2C LCD

// Wi-Fi credentials
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

// Pins
const int soilPin = A0;
const int relayPin = D1;  // GPIO for relay

int soilValue;
int threshold = 500;  // Default threshold
bool pumpState = false;

WiFiServer server(80);

LiquidCrystal_I2C lcd(0x27, 16, 2); // For I2C LCD

void setup() {
  Serial.begin(115200);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);

  lcd.begin();
  lcd.backlight();
  lcd.print("Connecting WiFi");

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  lcd.clear();
  lcd.print("WiFi Connected");

  server.begin();
}

void loop() {
  soilValue = analogRead(soilPin);

  // Auto Pump Control
  if (soilValue > threshold) {
    digitalWrite(relayPin, HIGH);
    pumpState = true;
  } else {
    digitalWrite(relayPin, LOW);
    pumpState = false;
  }

  // Display on LCD
  lcd.setCursor(0,0);
  lcd.print("Moisture: " + String(soilValue));
  lcd.setCursor(0,1);
  lcd.print("Pump: " + String(pumpState ? "ON " : "OFF"));

  // Web Server
  WiFiClient client = server.available();
  if (client) {
    String request = client.readStringUntil('\r');
    Serial.println(request);
    client.flush();

    // Check URL commands
    if (request.indexOf("/pump/on") != -1) {
      digitalWrite(relayPin, HIGH);
      pumpState = true;
    }
    if (request.indexOf("/pump/off") != -1) {
      digitalWrite(relayPin, LOW);
      pumpState = false;
    }

    // Respond to client
    client.print("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
    client.print("<h1>Smart Irrigation</h1>");
    client.print("Moisture: " + String(soilValue) + "<br>");
    client.print("Pump: " + String(pumpState ? "ON" : "OFF") + "<br>");
    client.print("<a href=\"/pump/on\">Turn Pump ON</a><br>");
    client.print("<a href=\"/pump/off\">Turn Pump OFF</a><br>");
    client.stop();
  }

  delay(1000);
}
