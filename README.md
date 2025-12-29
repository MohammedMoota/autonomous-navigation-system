# Autonomous Navigation & Intelligent Safety Systems

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![Platform](https://img.shields.io/badge/platform-ESP32-blue.svg)](https://www.espressif.com/en/products/socs/esp32)
[![Wokwi](https://img.shields.io/badge/Simulate-Wokwi-green.svg)](https://wokwi.com)

An IoT-based autonomous robot system with intelligent obstacle avoidance, line-following capabilities, and real-time cloud monitoring via ThingSpeak.

## Features

- **Dual Operation Modes**: Auto line-following and manual keyboard control
- **Obstacle Detection**: HC-SR04 ultrasonic sensor (20cm range)
- **Autonomous Avoidance**: Automatic evasive maneuvers
- **Cloud Monitoring**: Real-time data to ThingSpeak
- **Safety Features**: Automatic braking and audio alerts

## Hardware Components

| Component | Type | Qty |
|-----------|------|-----|
| Microcontroller | ESP32 DevKit C v4 | 1 |
| Display | LCD 16x2 I2C (0x27) | 1 |
| Distance Sensor | HC-SR04 Ultrasonic | 1 |
| Line Sensors | IR Sensors | 5 |
| Servo Motor | SG90 | 1 |
| Buzzer | Active Buzzer | 1 |
| Motors | DC Motors | 2 |

## Quick Start

### 1. Clone Repository

```bash
git clone https://github.com/MohammedMoota/autonomous-navigation-system.git
```

### 2. Setup Arduino IDE

- Install [Arduino IDE](https://www.arduino.cc/en/software)
- Add ESP32 board support via Board Manager
- Install libraries: `LiquidCrystal I2C`, `ESP32Servo`, `ThingSpeak`

### 3. Configure ThingSpeak

1. Create free account at [ThingSpeak.com](https://thingspeak.com)
2. Create channel with 2 fields: Distance (cm) and Obstacle Status
3. Update `sketch.ino` lines 36-37 with your Channel ID and API Key

### 4. Upload

- Connect ESP32 via USB
- Select board: ESP32 Dev Module
- Upload code

### 5. Simulate (Optional)

- Visit [Wokwi.com](https://wokwi.com) and create ESP32 project
- Copy `sketch.ino`, `diagram.json`, and `libraries.txt`

## Controls

| Key | Action |
|-----|--------|
| W/F | Forward |
| S/B | Backward |
| A/L | Turn Left |
| D/R | Turn Right |
| X | Stop |
| 1 | Toggle Auto/Manual |

**Baud Rate**: 115200

## Pin Configuration

**Motors**: GPIO 26, 27 (Left), GPIO 12, 14 (Right)  
**Ultrasonic**: GPIO 5 (TRIG), GPIO 18 (ECHO)  
**IR Sensors**: GPIO 15, 4, 16, 17, 19  
**Servo**: GPIO 23  
**Buzzer**: GPIO 13  
**LCD I2C**: GPIO 21 (SDA), GPIO 22 (SCL)

## Operation Modes

### Manual Mode (Default)

Full keyboard control with safety override for obstacles.

### Auto Mode

- Follows black line using 5 IR sensors
- Detects obstacles and performs evasive maneuvers:
  1. Stop and alert (1s)
  2. Reverse (0.8s)
  3. Turn right (0.6s)
  4. Resume

## Troubleshooting

**WiFi not connecting**: For Wokwi use SSID: `Wokwi-GUEST`, password: (empty)  
**ThingSpeak Error 404**: Check Channel ID  
**ThingSpeak Error 400**: Verify API Key  
**LCD blank**: Check I2C address (0x27 or 0x3F)

## License

MIT License - see [LICENSE](LICENSE) file

## Acknowledgments

Built with ESP32, Arduino, and ThingSpeak

---

**Author**: Mohammed Moota  
**For questions**: [Open an issue](https://github.com/MohammedMoota/autonomous-navigation-system/issues)
