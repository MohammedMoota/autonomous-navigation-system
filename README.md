# 🤖 Autonomous Navigation & Intelligent Safety Systems

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Platform](https://img.shields.io/badge/platform-ESP32-blue.svg)](https://www.espressif.com/en/products/socs/esp32)
[![Wokwi](https://img.shields.io/badge/Simulate-Wokwi-green.svg)](https://wokwi.com)

An advanced IoT-based autonomous robot system featuring intelligent obstacle avoidance, line-following capabilities, and real-time cloud monitoring via ThingSpeak. Built with ESP32 microcontroller and designed for simulation on Wokwi platform.

## Table of Contents

- [Features](#-features)
- [System Architecture](#-system-architecture)
- [Hardware Components](#-hardware-components)
- [Pin Configuration](#-pin-configuration)
- [Software Requirements](#-software-requirements)
- [Installation & Setup](#-installation--setup)
- [Usage](#-usage)
- [Control Commands](#-control-commands)
- [IoT Integration](#-iot-integration)
- [Operation Modes](#-operation-modes)
- [Safety Features](#-safety-features)
- [Troubleshooting](#-troubleshooting)
- [Contributing](#-contributing)
- [License](#-license)
- [Acknowledgments](#-acknowledgments)

## Features

### Core Capabilities

- **Dual Operation Modes**: Seamless switching between autonomous line-following and manual keyboard control
- **Intelligent Obstacle Detection**: Real-time obstacle sensing using ultrasonic sensor (20cm detection range)
- **Autonomous Collision Avoidance**: Automatic evasive maneuvers in auto mode
- **Real-time Cloud Monitoring**: Live data streaming to ThingSpeak platform
- **Visual Feedback**: 16x2 LCD display for system status and alerts
- **Audible Warnings**: Buzzer alerts for obstacle detection
- **Safety Override**: Automatic movement blocking when obstacles detected in manual mode

### IoT Features

- WiFi connectivity (Wokwi virtual network)
- ThingSpeak cloud integration
- Real-time distance monitoring
- Obstacle status logging
- 15-second update intervals

## System Architecture

```mermaid
graph TD
    A[ESP32 Microcontroller] --> B[Sensor Input Layer]
    A --> C[Actuator Output Layer]
    A --> D[IoT Communication Layer]
    A --> E[Display & Feedback Layer]
    
    B --> B1[HC-SR04 Ultrasonic Sensor]
    B --> B2[5x IR Line Sensors]
    B --> B3[Serial Input]
    
    C --> C1[Left Motor Forward/Back]
    C --> C2[Right Motor Forward/Back]
    C --> C3[Servo Motor Scanner]
    
    D --> D1[WiFi Module]
    D --> D2[ThingSpeak API]
    
    E --> E1[16x2 LCD I2C Display]
    E --> E2[Buzzer Alert]
    E --> E3[LED Indicators]
    
    style A fill:#4CAF50,stroke:#333,stroke-width:3px,color:#fff
    style D fill:#2196F3,stroke:#333,stroke-width:2px,color:#fff
</mermaid>

##  Hardware Components

| Component | Model/Type | Quantity | Purpose |
|-----------|-----------|----------|---------|
| Microcontroller | ESP32 DevKit C v4 | 1 | Main processing unit |
| Display | LCD 16x2 I2C (0x27) | 1 | Status display |
| Distance Sensor | HC-SR04 Ultrasonic | 1 | Obstacle detection |
| Line Sensors | IR Sensors | 5 | Line detection |
| Servo Motor | SG90 | 1 | Scanner mechanism |
| Buzzer | Active Buzzer | 1 | Audio alerts |
| Motors | DC Motors | 2 | Left & Right drive |
| LED Indicators | Standard LEDs | 4 | Motor status (Green/Red) |

##  Pin Configuration

### Digital I/O Pins

| Pin | Component | Function |
|-----|-----------|----------|
| GPIO 5 | Ultrasonic (TRIG) | Trigger signal |
| GPIO 18 | Ultrasonic (ECHO) | Echo reception |
| GPIO 13 | Buzzer | Alert output |
| GPIO 23 | Servo | PWM control |
| GPIO 26 | Left Motor | Forward |
| GPIO 27 | Left Motor | Backward |
| GPIO 12 | Right Motor | Forward |
| GPIO 14 | Right Motor | Backward |

### Line Sensor Array

| Pin | Sensor Position |
|-----|----------------|
| GPIO 15 | Far Left |
| GPIO 4 | Left |
| GPIO 16 | Center |
| GPIO 17 | Right |
| GPIO 19 | Far Right |

### I2C Bus

| Pin | Function |
|-----|----------|
| GPIO 21 | SDA (Data) |
| GPIO 22 | SCL (Clock) |

##  Software Requirements

### Libraries
- `WiFi.h` - ESP32 WiFi connectivity
- `Wire.h` - I2C communication
- `LiquidCrystal_I2C.h` - LCD display control
- `ESP32Servo.h` - Servo motor control
- `ThingSpeak.h` - Cloud platform integration

### Development Environment
- Arduino IDE 1.8.x or higher
- ESP32 Board Support Package
- Wokwi Simulator (for virtual testing)

##  Installation & Setup

### 1. Clone the Repository

```bash
git clone https://github.com/MohammedMoota/autonomous-navigation-system.git
cd autonomous-navigation-system
```

### 2. Install Arduino IDE & Dependencies

1. Download and install [Arduino IDE](https://www.arduino.cc/en/software)
2. Add ESP32 board support:
   - Go to **File → Preferences**
   - Add to "Additional Board Manager URLs":

     ```
     https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
     ```

   - Go to **Tools → Board → Boards Manager**
   - Search "ESP32" and install

3. Install required libraries via **Library Manager** (Tools → Manage Libraries):
   - LiquidCrystal I2C
   - ESP32Servo
   - ThingSpeak

### 3. Configure ThingSpeak

1. Create a free account at [ThingSpeak.com](https://thingspeak.com)
2. Create a new channel with 2 fields:
   - **Field 1**: Distance (cm)
   - **Field 2**: Obstacle Status (0/1)
3. Note your **Channel ID** and **Write API Key**
4. Update `sketch.ino`:

```cpp
unsigned long myChannelNumber = YOUR_CHANNEL_ID;         // Line 36
const char * myWriteAPIKey = "YOUR_WRITE_API_KEY";      // Line 37
```

### 4. Upload to ESP32

1. Connect ESP32 via USB
2. Select board: **Tools → Board → ESP32 Dev Module**
3. Select correct COM port: **Tools → Port**
4. Click **Upload** button

### 5. Simulate on Wokwi (Optional)

1. Visit [Wokwi.com](https://wokwi.com)
2. Create new ESP32 project
3. Copy contents of `sketch.ino`, `diagram.json`, and `libraries.txt`
4. Click **Start Simulation**

## Usage

### Starting the System

1. Power on the ESP32
2. Wait for WiFi connection (indicated on Serial Monitor)
3. System initializes in **MANUAL MODE** by default
4. LCD displays: `SYSTEM READY` → `MODE: MANUAL`

### Serial Monitor Setup

- **Baud Rate**: 115200
- **Line Ending**: Newline (NL)

### Control Interface

The Serial Monitor displays a comprehensive control guide on startup:

```
=========================================
      ROBOT CONTROL SYSTEM V1.0      
=========================================
[ CONTROL GUIDE ]
  [W] or [F] : Move Forward
  [S] or [B] : Move Backward
  [A] or [L] : Turn Left
  [D] or [R] : Turn Right
  [X]        : Stop Immediately
  [1]        : Switch Mode (Auto/Manual)
=========================================
```

## 🎮 Control Commands

### Manual Mode Commands

| Key | Alternative | Action |
|-----|------------|--------|
| `W` | `F` | Move Forward |
| `S` | `B` | Move Backward |
| `A` | `L` | Turn Left |
| `D` | `R` | Turn Right |
| `X` | - | Emergency Stop |
| `1` | - | Toggle Auto/Manual Mode |

> **Note**: Commands are case-insensitive

### Safety Restrictions

In **Manual Mode**, forward movement is **automatically blocked** when obstacles are detected within 20cm. Only backward movement (`S` or `B`) and mode switching (`1`) are permitted.

## 🌐 IoT Integration

### ThingSpeak Data Streaming

The system automatically uploads data to ThingSpeak every **15 seconds**:

| Field | Data Type | Description |
|-------|-----------|-------------|
| Field 1 | Integer (cm) | Distance to nearest obstacle |
| Field 2 | Binary (0/1) | Obstacle detected (1) or clear (0) |

### Viewing Live Data

1. Log in to your ThingSpeak account
2. Navigate to **Channels → My Channels → [Your Channel]**
3. View real-time graphs and data

### API Response Codes

| Code | Status |
|------|--------|
| 200 | Update successful |
| 404 | Channel not found |
| 400 | Bad request (check API key) |

## Operation Modes

### 1. Manual Mode (Default)

**Features:**

- Full keyboard control via Serial Monitor
- Safety override for obstacle detection
- Real-time status feedback on LCD
- LED indicators for motor directions

**Use Case**: Testing, debugging, precise navigation

### 2. Auto Line Following Mode

**Features:**

- Autonomous path following using 5 IR sensors
- Automatic obstacle detection and avoidance
- Evasive maneuver sequence:
  1. **Detect** → Stop and alert (1 second)
  2. **Reverse** → Back up (0.8 seconds)
  3. **Turn** → Turn right (0.6 seconds)
  4. **Resume** → Continue line following

**Algorithm Logic:**

```
IF center_sensor = BLACK LINE
    → Move Forward
ELSE IF left_sensor = BLACK LINE
    → Turn Left
ELSE IF right_sensor = BLACK LINE
    → Turn Right
ELSE
    → Stop (line lost)
```

**Use Case**: Autonomous warehouse navigation, delivery systems

## Safety Features

### Multi-Layer Protection

1. **Proximity Detection**: 20cm warning zone
2. **Automatic Braking**: Immediate motor shutdown
3. **Audio Alerts**: 1000Hz buzzer activation
4. **Visual Warnings**: LCD obstacle notification
5. **Manual Override Prevention**: Forward movement blocking
6. **Autonomous Evasion**: Smart obstacle avoidance in auto mode

### Safety Response Times

| Event | Response Time |
|-------|--------------|
| Obstacle Detection | < 100ms |
| Motor Shutdown | Immediate |
| Buzzer Activation | < 50ms |
| LCD Update | < 200ms |

## Troubleshooting

### Common Issues

#### WiFi Connection Failed

**Symptoms**: Serial Monitor shows continuous dots without "WiFi Connected"

**Solutions**:

- Verify SSID and password in code
- For Wokwi: Use `Wokwi-GUEST` with empty password
- Check WiFi network availability
- Reset and try again

#### ThingSpeak Update Errors

**Error Code 404**:

- Verify Channel ID is correct
- Check channel exists and is active

**Error Code 400**:

- Confirm Write API Key is accurate
- Ensure no extra spaces in API key string

#### LCD Not Displaying

**Solutions**:

- Check I2C address (default: 0x27)
- Verify SDA/SCL connections (GPIO 21/22)
- Test with I2C scanner sketch
- Check power supply (5V)

#### Motors Not Responding

**Solutions**:

- Verify pin connections match code
- Check motor power supply
- Test individual pins with digitalWrite
- Ensure motor driver is functional

#### Obstacle Detection Inconsistent

**Solutions**:

- Verify ultrasonic sensor connections
- Check clear line of sight
- Adjust detection threshold (currently 20cm)
- Test sensor with standalone code

#### Line Following Not Working

**Solutions**:

- Calibrate IR sensors
- Ensure sufficient contrast (black line/white surface)
- Check sensor positioning and height
- Verify GPIO pin assignments

## Contributing

Contributions are welcome! Please follow these guidelines:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit changes (`git commit -m 'Add AmazingFeature'`)
4. Push to branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

### Code Style

- Follow Arduino coding standards
- Comment complex logic
- Use descriptive variable names
- Keep functions focused and modular

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- **ESP32 Community** - For extensive documentation and support
- **Wokwi Team** - For providing an excellent simulation platform
- **ThingSpeak** - For free IoT cloud platform
- **Arduino** - For the development framework

## Contact & Support

For questions, issues, or suggestions:

- **GitHub Issues**: [Open an issue](https://github.com/MohammedMoota/autonomous-navigation-system/issues)

---

<div align="center">

**If you found this project helpful, please consider giving it a star!**

Made with  for IoT Innovation

</div>
