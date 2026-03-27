# cylinder-leakage-system
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

---

## Overview

The widespread use of LPG and other flammable gases in homes, restaurants, and industries makes gas leakage detection a critical safety requirement. This project implements an **IoT-based Gas Leakage Detection and Monitoring System** that:

- Detects combustible gas concentrations using the MQ gas sensor
- Provides **instant local alerts** via a buzzer when levels exceed a threshold
- Transmits sensor data to **ThingSpeak Cloud** for real-time visualization and remote monitoring
- Operates continuously at low cost with minimal infrastructure
  
---

## Features

-  Real-time gas concentration monitoring (0–1000 ppm range)
-  Audible buzzer alert when gas levels exceed safe threshold (>100 ppm)
-  Cloud dashboard via ThingSpeak for remote monitoring
-  Wi-Fi connectivity using ESP8266 (no additional hardware needed)
-  Low-cost, compact, and energy-efficient design
-  Continuous 24/7 operation capability
-  Long-term data logging for trend analysis

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

| Component | Description | Quantity | Cost(INR) |
|-----------|-------------|----------|
| ESP8266 NodeMCU | Wi-Fi enabled microcontroller (Espressif ESP8266EX) | 1 | | ₹180 |
| MQ Gas Sensor | Detects LPG, methane, propane, CO, smoke (MQ-2/MQ-5/MQ-6) | 1 | | ₹90 |
| Buzzer | Active buzzer for audible alert | 1 | | ₹50 |
| Power Supply | 5V DC regulated supply | 1 | | - |
| Jumper Wires | Male-to-male / male-to-female | As needed | | ₹60 |

## Software Requirements

| Tool | Purpose |
|------|---------|
| [Arduino IDE](https://www.arduino.cc/en/software) | Programming the ESP8266 |
| [ESP8266 Board Package](https://arduino.esp8266.com/stable/package_esp8266com_index.json) | ESP8266 support in Arduino IDE |
| [ThingSpeak Library](https://github.com/mathworks/thingspeak-arduino) | Cloud data upload |
| [ThingSpeak Account](https://thingspeak.com) | Free IoT cloud platform |

### Pin Connections

| Component | ESP8266 Pin | Notes |
|-----------|-------------|-------|
| MQ Sensor (AO) | A0 | Analog gas concentration reading |
| MQ Sensor (VCC) | 3.3V / 5V | Check sensor datasheet |
| MQ Sensor (GND) | GND | Common ground |
| Buzzer (+) | D0 | Digital HIGH/LOW control |
| Buzzer (–) | GND | Common ground |

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






