# cylinder-leakage-system
Gas Leakage Detection and Monitoring System

An IoT-based real-time gas leakage detection system using ESP8266 NodeMCU, MQ Gas Sensor, and ThingSpeak Cloud Platform.

![Platform](https://img.shields.io/badge/Platform-ESP8266%20NodeMCU-blue)
![IDE](https://img.shields.io/badge/IDE-Arduino-teal)
![Cloud](https://img.shields.io/badge/Cloud-ThingSpeak-orange)
![License](https://img.shields.io/badge/License-MIT-green)
![Status](https://img.shields.io/badge/Status-Completed-brightgreen)

---

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [System Architecture](#system-architecture)
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Circuit Diagram](#circuit-diagram)
- [Algorithm](#algorithm)
- [Getting Started](#getting-started)
- [ThingSpeak Setup](#thingspeak-setup)
- [Code Walkthrough](#code-walkthrough)
- [Results](#results)
- [Advantages & Limitations](#advantages--limitations)
- [Future Work](#future-work)
- [Team](#team)
- [Acknowledgements](#acknowledgements)
- [References](#references)

---

## Overview

The widespread use of LPG and other flammable gases in homes, restaurants, and industries makes gas leakage detection a critical safety requirement. This project implements an **IoT-based Gas Leakage Detection and Monitoring System** that:

- Detects combustible gas concentrations using the MQ gas sensor
- Provides **instant local alerts** via a buzzer when levels exceed a threshold
- Transmits sensor data to **ThingSpeak Cloud** for real-time visualization and remote monitoring
- Operates continuously at low cost with minimal infrastructure

> Developed under the **IoT Club**, Department of Electronics & Telecommunication Engineering  
> Bharati Vidyapeeth's College of Engineering for Women, Pune – 43  
> Savitribai Phule Pune University

---

## Features

- ✅ Real-time gas concentration monitoring (0–1000 ppm range)
- ✅ Audible buzzer alert when gas levels exceed safe threshold (>100 ppm)
- ✅ Cloud dashboard via ThingSpeak for remote monitoring
- ✅ Wi-Fi connectivity using ESP8266 (no additional hardware needed)
- ✅ Low-cost, compact, and energy-efficient design
- ✅ Continuous 24/7 operation capability
- ✅ Long-term data logging for trend analysis

---

## System Architecture

```
┌─────────────┐     Analog Signal     ┌─────────────────┐
│  MQ Gas     │ ───────────────────►  │                 │
│  Sensor     │                       │  ESP8266        │  ──────►  ThingSpeak Cloud
└─────────────┘                       │  NodeMCU        │           (Real-time Graph)
                                      │                 │
┌─────────────┐     Digital Output    │  (Wi-Fi Module) │
│   Buzzer    │ ◄───────────────────  │                 │
│  (Alert)    │                       └─────────────────┘
└─────────────┘                              │
                                        5V DC Supply
```

**Data Flow:**
1. MQ Sensor reads ambient gas concentration → outputs analog voltage
2. ESP8266 ADC pin reads voltage → maps to ppm value
3. If ppm > 100 → Buzzer ON + Serial alert
4. Data uploaded to ThingSpeak every 3 seconds for cloud visualization

---

## Hardware Requirements

| Component | Description | Quantity |
|-----------|-------------|----------|
| ESP8266 NodeMCU | Wi-Fi enabled microcontroller (Espressif ESP8266EX) | 1 |
| MQ Gas Sensor | Detects LPG, methane, propane, CO, smoke (MQ-2/MQ-5/MQ-6) | 1 |
| Buzzer | Active buzzer for audible alert | 1 |
| Power Supply | 5V DC regulated supply | 1 |
| Breadboard | For prototyping connections | 1 |
| Jumper Wires | Male-to-male / male-to-female | As needed |

### Pin Connections

| Component | ESP8266 Pin | Notes |
|-----------|-------------|-------|
| MQ Sensor (AO) | A0 | Analog gas concentration reading |
| MQ Sensor (VCC) | 3.3V / 5V | Check sensor datasheet |
| MQ Sensor (GND) | GND | Common ground |
| Buzzer (+) | D0 | Digital HIGH/LOW control |
| Buzzer (–) | GND | Common ground |

---

## Software Requirements

| Tool | Purpose |
|------|---------|
| [Arduino IDE](https://www.arduino.cc/en/software) | Programming the ESP8266 |
| [ESP8266 Board Package](https://arduino.esp8266.com/stable/package_esp8266com_index.json) | ESP8266 support in Arduino IDE |
| [ThingSpeak Library](https://github.com/mathworks/thingspeak-arduino) | Cloud data upload |
| [ThingSpeak Account](https://thingspeak.com) | Free IoT cloud platform |

### Arduino Libraries Required

```
ESP8266WiFi.h     - Built-in with ESP8266 board package
ThingSpeak.h      - Install via Arduino Library Manager
```

---

## Circuit Diagram

> See [`docs/circuit_diagram.jpg`](docs/circuit_diagram.jpg) for the full wiring schematic.

**Quick Reference:**
- MQ sensor analog output → ESP8266 `A0`
- Buzzer signal pin → ESP8266 `D0`
- All components share common GND
- System powered via USB (5V) or external 5V DC supply

---

## Algorithm

```
START
  ├── Initialize: WiFi, ThingSpeak, Serial, Buzzer pin
  ├── Connect to WiFi (loop until connected)
  └── LOOP (every 3 seconds):
        ├── Read analogRead(A0)  →  gasValue (0–1023)
        ├── Map gasValue to ppm  →  gasPPM (0–1000)
        ├── Upload gasPPM to ThingSpeak Field 1
        ├── IF gasPPM > 100:
        │     └── Buzzer ON  +  Print "Gas level HIGH!!!"
        └── ELSE:
              └── Buzzer OFF
END
```

---

## Getting Started

### 1. Clone the Repository

```bash
git clone https://github.com/<your-username>/gas-leakage-detection.git
cd gas-leakage-detection
```

### 2. Install Arduino IDE and ESP8266 Board

1. Download and install [Arduino IDE](https://www.arduino.cc/en/software)
2. Go to **File → Preferences** and add this URL to "Additional Board Manager URLs":
   ```
   https://arduino.esp8266.com/stable/package_esp8266com_index.json
   ```
3. Go to **Tools → Board → Board Manager**, search `ESP8266`, and install

### 3. Install Required Libraries

In Arduino IDE, go to **Sketch → Include Library → Manage Libraries**:
- Search and install: `ThingSpeak`

### 4. Configure Credentials

Open `src/gas_leakage_detection.ino` and update:

```cpp
const char* ssid     = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

unsigned long myChannelNumber = YOUR_CHANNEL_ID;
const char* myWriteAPIKey     = "YOUR_WRITE_API_KEY";
```

### 5. Upload the Code

1. Connect ESP8266 NodeMCU via USB
2. Select **Tools → Board → NodeMCU 1.0 (ESP-12E Module)**
3. Select the correct COM port under **Tools → Port**
4. Click **Upload**

---

## ThingSpeak Setup

1. Create a free account at [thingspeak.com](https://thingspeak.com)
2. Click **New Channel** and configure:
   - **Name:** Gas Leakage Monitor
   - **Field 1:** Gas Concentration (ppm)
3. Save the channel and copy your:
   - **Channel ID**
   - **Write API Key**
4. Paste these values into the code (see Step 4 above)

---

## Code Walkthrough

The main source file is [`src/gas_leakage_detection.ino`](src/gas_leakage_detection.ino).

```cpp
#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

// WiFi & ThingSpeak credentials
const char* ssid     = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";
unsigned long myChannelNumber = YOUR_CHANNEL_ID;
const char* myWriteAPIKey     = "YOUR_API_KEY";

WiFiClient client;
int gasSensorPin = A0;
int buzzer1      = D0;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { delay(1000); }
  ThingSpeak.begin(client);
  pinMode(buzzer1, OUTPUT);
  digitalWrite(buzzer1, LOW);
}

void loop() {
  int gasValue  = analogRead(A0);
  float gasPPM  = map(gasValue, 0, 1023, 0, 1000);

  Serial.print("Gas Sensor Value: ");
  Serial.println(gasPPM);

  ThingSpeak.writeField(myChannelNumber, 1, gasPPM, myWriteAPIKey);

  if (gasPPM > 100) {
    digitalWrite(buzzer1, HIGH);
    Serial.println("Gas level HIGH!!!");
  } else {
    digitalWrite(buzzer1, LOW);
  }

  delay(3000);
}
```

> **Note:** Replace placeholder credentials before uploading. Never commit real API keys to public repositories — use environment variables or a `secrets.h` file (see `.gitignore`).

---

## Results

The system was successfully tested with the following observations:

- Gas concentration readings displayed in real-time on the ThingSpeak dashboard
- Buzzer activated reliably when gas levels exceeded the 100 ppm threshold
- Data uploaded to cloud at ~3-second intervals with stable Wi-Fi connectivity
- Remote monitoring confirmed functional from separate devices via ThingSpeak URL

> See [`docs/results/`](docs/results/) for screenshots of the ThingSpeak dashboard and hardware setup.

---

## Advantages & Limitations

### ✅ Advantages

- **Real-time monitoring** — continuous cloud updates via ThingSpeak
- **Early warning** — instant buzzer alert prevents fire/explosion risks
- **Remote accessibility** — monitor from anywhere via ThingSpeak dashboard
- **Low cost** — affordable components (MQ sensor + ESP8266 + buzzer)
- **Energy-efficient** — suitable for 24/7 continuous operation
- **Scalable** — easily extended with more sensors (temperature, smoke, CO₂)
- **Compact** — easy to install in homes, labs, or vehicles

### ⚠️ Limitations

- MQ sensors are sensitive to humidity and temperature variations
- Requires continuous Wi-Fi for cloud uploads
- ThingSpeak free tier limits updates to every 15 seconds
- No battery backup — system fails during power outages

---

## Future Work

| Enhancement | Description |
|-------------|-------------|
| Multi-gas Detection | Add MQ-7 (CO), MQ-135 (CO₂) for broader coverage |
| Mobile App | Push notifications via Android/iOS app |
| AI Prediction | ML model to predict leaks before threshold breach |
| Battery/Solar Power | Backup power for uninterrupted operation |
| Auto Ventilation | Trigger exhaust fans / shutoff valves automatically |
| Voice Alerts | Integration with Alexa or Google Assistant |
| Industrial Version | Rugged, long-range model for factories and refineries |

---

## Team

Developed by students of **BE Electronics & Telecommunication Engineering**  
Under the **IoT Club**, Bharati Vidyapeeth's College of Engineering for Women, Pune

| Roll No. | Name |
|----------|------|
| 41124 | Shreya Dhane |
| 41133 | Diksha Gunje |
| 41137 | Sophiya Inamdar |
| 41143 | Siddhi Jaiswal |
| 41152 | Samruddhi Kale |
| 41167 | Sneha Dalavi |
| 41171 | Sayali Shinde |

**Guide:** Prof. Dr. Savita Itkarkar (Club In-Charge)  
**HOD:** Prof. Dr. S. R. Patil

---

## Acknowledgements

We extend our sincere gratitude to **Prof. Dr. P. V. Jadhav** (Principal), **Prof. Dr. S. R. Patil** (HOD), and the **IoT Club** of the Department of Electronics and Telecommunication Engineering for their constant motivation, guidance, and support throughout this project.

---

## References

1. [LPG Gas Leakage Detection Using IoT](https://www.researchgate.net/publication/354309093) — ResearchGate, 2025
2. [Implementation of a Gas Leakage Detection System Using MQ-6 Sensor](https://www.researchgate.net/publication/361937209) — ResearchGate, 2025
3. [IoT-based Fire and Gas Monitoring System](https://www.researchgate.net/publication/353708037) — ResearchGate, 2025
4. NK Jumaa — [IoT Based Gas Leakage Detection and Alarming System](https://pdfs.semanticscholar.org/ce34/dbedfcb62ee62e9e91578075bdfc6180bd66.pdf) — Semantic Scholar, 2022
5. N. Fuadi et al. — [Gas Leakage Monitoring System Based on Android and NodeMCU ESP8266](https://www.researchgate.net/publication/385404219) — ResearchGate, 2024
6. M.A. Baballe — [Automatic Gas Leakage Monitoring System Using MQ-5](https://ideas.repec.org/a/pkp/rocere/v8y2021i2p64-75id1488.html) — 2021
7. [Arduino IDE Documentation](https://www.arduino.cc/en/software)
8. [ThingSpeak IoT Platform](https://thingspeak.com)

---

*© 2025 — IoT Club, Dept. of Electronics & Telecommunication Engineering, Bharati Vidyapeeth's College of Engineering for Women, Pune*
