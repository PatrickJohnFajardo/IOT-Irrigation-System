# Smart Irrigation System 🌱💧

A Wi-Fi enabled irrigation system that waters plants automatically based on soil moisture. Monitor and control your pump via a web browser.

---

## Features

* Auto pump ON/OFF based on soil moisture
* Real-time soil moisture display on LCD
* Manual control via web browser
* Works with ESP8266/ESP32

---

## Components

* ESP8266 (NodeMCU) or ESP32
* Soil Moisture Sensor
* 5V DC Pump + Relay Module
* LCD Display (I2C recommended)
* Jumper wires / Breadboard
* Power supply (USB or battery)

---

## Wiring (Quick Guide)

**Soil Moisture Sensor**

* VCC → 3.3V/5V
* GND → GND
* A0 → Analog pin

**Relay & Pump**

* IN → Digital pin (e.g., D1)
* VCC → 5V, GND → GND
* Pump → Relay COM/NO

**LCD (I2C)**

* SDA → D2, SCL → D1
* VCC → 3.3V/5V, GND → GND

*(Tip: Adjust pins in the code if needed)*

---

## Setup

1. Clone the repo:

```bash
git clone https://github.com/PatrickJohnFajardo/IOT-Irrigation-System.git
```

2. Open code in Arduino IDE.
3. Install required libraries: `ESP8266WiFi` / `WiFi`, `LiquidCrystal_I2C`
4. Update Wi-Fi credentials in the code.
5. Upload to ESP8266/ESP32.
6. Open Serial Monitor → Note IP address.
7. Open browser → Control pump from web page.

---

## How It Works

* Sensor reads soil moisture.
* Pump automatically turns ON/OFF based on threshold.
* LCD shows moisture and pump status.
* Web interface allows manual control.

---

## License

MIT License – free to use and modify.
