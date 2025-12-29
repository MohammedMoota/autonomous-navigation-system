# Hardware Setup Guide

Complete assembly instructions for the Autonomous Navigation & Intelligent Safety System.

## 📦 Required Components

### Electronics

| Qty | Component | Specifications |
|-----|-----------|----------------|
| 1 | ESP32 DevKit C v4 | 30-pin development board |
| 1 | LCD Display | 16x2 with I2C module (0x27) |
| 1 | HC-SR04 | Ultrasonic distance sensor |
| 5 | IR Sensors | Infrared line detection modules |
| 1 | Servo Motor | SG90 or equivalent (0-180°) |
| 1 | Active Buzzer | 5V piezo buzzer |
| 2 | DC Motors | 3-6V gear motors |
| 1 | Motor Driver | L298N or equivalent H-bridge |
| 4 | LEDs | 2x Green, 2x Red (5mm) |
| 4 | Resistors | 220Ω for LEDs |

### Power Supply

| Component | Voltage | Current |
|-----------|---------|---------|
| ESP32 | 5V | 500mA (USB) or 3.3V regulated |
| Motors | 5-6V | 1A (via motor driver) |
| Servo | 5V | 500mA peak |
| Total | 5V | 2-3A recommended |

### Mechanical Parts

- Robot chassis (acrylic or 3D printed)
- Wheels (2x drive wheels + 1x caster wheel)
- Mounting hardware (screws, standoffs)
- Breadboard or custom PCB
- Jumper wires (M-M, M-F)

## 🔧 Assembly Instructions

### Step 1: Prepare the Chassis

1. Assemble robot base platform
2. Mount DC motors to chassis
3. Attach wheels to motor shafts
4. Install caster wheel at rear

### Step 2: Mount Electronics

#### ESP32 Placement

- Position at center of chassis
- Ensure USB port is accessible
- Secure with standoffs or double-sided tape

#### LCD Display

- Mount on front of robot (visible position)
- Keep I2C connections accessible
- Distance: ~10cm from ESP32

#### Sensor Array

- **IR Sensors**: Front bottom edge, equally spaced
  - Spacing: ~2-3cm apart
  - Height: 5-10mm above ground
  - Angle: Facing downward at 45°
  
- **Ultrasonic Sensor**: Front center
  - Height: 5-10cm above ground
  - Clear field of view (no obstructions)
  - Mount on servo for scanning capability

#### Motor Driver

- Place near motors
- Ensure good ventilation
- Secure to avoid vibration issues

### Step 3: Wiring Connections

#### Power Distribution

```
Power Supply (5V) ──┬─→ ESP32 (VIN or USB)
                    ├─→ Motor Driver (VCC)
                    ├─→ Servo Motor (V+)
                    └─→ LCD Display (VCC)

Common Ground ──────┬─→ ESP32 (GND)
                    ├─→ Motor Driver (GND)
                    ├─→ All Sensors (GND)
                    ├─→ LCD Display (GND)
                    └─→ Servo Motor (GND)
```

#### ESP32 to LCD (I2C)

| ESP32 Pin | LCD Pin | Wire Color Suggestion |
|-----------|---------|----------------------|
| GPIO 21 | SDA | Blue |
| GPIO 22 | SCL | Yellow |
| 5V | VCC | Red |
| GND | GND | Black |

#### ESP32 to HC-SR04

| ESP32 Pin | Sensor Pin | Wire Color |
|-----------|------------|------------|
| GPIO 5 | TRIG | Purple |
| GPIO 18 | ECHO | Orange |
| 5V | VCC | Red |
| GND | GND | Black |

#### ESP32 to Servo

| ESP32 Pin | Servo Wire |
|-----------|------------|
| GPIO 23 | Signal (Orange/Yellow) |
| 5V | Power (Red) |
| GND | Ground (Brown/Black) |

#### ESP32 to Motor Driver

**Left Motor:**

| ESP32 Pin | Driver Pin | Function |
|-----------|------------|----------|
| GPIO 26 | IN1 | Forward |
| GPIO 27 | IN2 | Backward |

**Right Motor:**

| ESP32 Pin | Driver Pin | Function |
|-----------|------------|----------|
| GPIO 12 | IN3 | Forward |
| GPIO 14 | IN4 | Backward |

**Motor Driver to Motors:**

| Driver | Motor |
|--------|-------|
| OUT1, OUT2 | Left Motor |
| OUT3, OUT4 | Right Motor |

#### ESP32 to IR Sensor Array

| ESP32 Pin | Sensor Position | Wire Color |
|-----------|----------------|------------|
| GPIO 15 | Far Left (IR1) | Gray |
| GPIO 4 | Left (IR2) | Gray |
| GPIO 16 | Center (IR3) | Gray |
| GPIO 17 | Right (IR4) | Gray |
| GPIO 19 | Far Right (IR5) | Gray |

**Note**: Connect VCC to 3.3V and GND for each sensor

#### ESP32 to Buzzer

| ESP32 Pin | Buzzer Pin |
|-----------|------------|
| GPIO 13 | Positive (+) |
| GND | Negative (-) |

#### ESP32 to LED Indicators

| ESP32 Pin | LED | Resistor | Function |
|-----------|-----|----------|----------|
| GPIO 26 | Green LED | 220Ω | Left Forward |
| GPIO 27 | Red LED | 220Ω | Left Backward |
| GPIO 12 | Green LED | 220Ω | Right Forward |
| GPIO 14 | Red LED | 220Ω | Right Backward |

**Connection**: ESP32 → Resistor → LED Anode (+) → LED Cathode (-) → GND

## 🔍 Testing Individual Components

### Test 1: LCD Display

```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.print("LCD Test OK!");
}

void loop() {}
```

**Expected Result**: "LCD Test OK!" appears on screen

### Test 2: Ultrasonic Sensor

```cpp
void setup() {
  Serial.begin(115200);
  pinMode(5, OUTPUT);  // TRIG
  pinMode(18, INPUT);  // ECHO
}

void loop() {
  digitalWrite(5, LOW);
  delayMicroseconds(2);
  digitalWrite(5, HIGH);
  delayMicroseconds(10);
  digitalWrite(5, LOW);
  
  long duration = pulseIn(18, HIGH);
  int distance = duration * 0.034 / 2;
  
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(500);
}
```

**Expected Result**: Distance readings in Serial Monitor

### Test 3: Motors

```cpp
void setup() {
  pinMode(26, OUTPUT); // Left Forward
  pinMode(27, OUTPUT); // Left Back
  pinMode(12, OUTPUT); // Right Forward
  pinMode(14, OUTPUT); // Right Back
}

void loop() {
  // Forward
  digitalWrite(26, HIGH);
  digitalWrite(12, HIGH);
  delay(2000);
  
  // Stop
  digitalWrite(26, LOW);
  digitalWrite(12, LOW);
  delay(1000);
}
```

**Expected Result**: Both motors run forward for 2 seconds, then stop

### Test 4: IR Sensors

```cpp
void setup() {
  Serial.begin(115200);
  for(int i = 0; i < 5; i++) {
    pinMode(ir[i], INPUT);
  }
}

void loop() {
  for(int i = 0; i < 5; i++) {
    Serial.print(digitalRead(ir[i]));
    Serial.print(" ");
  }
  Serial.println();
  delay(200);
}
```

**Expected Result**:

- `1` when over white surface
- `0` when over black line

## ⚡ Power Supply Options

### Option 1: Dual Power (Recommended)

- **ESP32**: USB power bank (5V 2A)
- **Motors**: Separate 6V battery pack (4x AA)
- **Advantage**: Stable ESP32 operation, isolated noise

### Option 2: Single Battery

- **All Components**: 7.4V LiPo battery with voltage regulators
- **5V Regulator**: For ESP32, sensors
- **Motor Driver**: Direct connection or 6V regulator
- **Advantage**: Compact, wireless operation

### Option 3: Development/Testing

- **ESP32**: USB cable from computer
- **Motors**: External 5V power supply
- **Advantage**: Easy debugging, unlimited runtime

## 📏 Calibration

### IR Sensor Calibration

1. Place robot on white surface
2. Adjust sensor potentiometer until LED turns OFF
3. Move to black line
4. Fine-tune until LED turns ON
5. Repeat for all 5 sensors

### Motor Speed Calibration

If robot doesn't move straight:

1. Test each motor individually
2. Adjust PWM values (currently digital HIGH/LOW)
3. Consider adding PWM control for speed matching

### Ultrasonic Sensor Verification

1. Place object at known distance (e.g., 10cm)
2. Read sensor value via Serial Monitor
3. Compare with actual distance
4. Verify accuracy within ±1cm

## 🛡️ Safety Checklist

- [ ] All connections are secure and insulated
- [ ] No exposed wires or short circuits
- [ ] Power supply voltage is correct (5V for ESP32)
- [ ] Motors cannot exceed power supply current rating
- [ ] Battery is properly secured to chassis
- [ ] Emergency stop accessible (press 'X' in Serial Monitor)
- [ ] Ultrasonic sensor has clear field of view
- [ ] IR sensors are at correct height (5-10mm)
- [ ] Robot operates in safe testing environment

## 🎯 Final Integration Test

1. Power on system
2. Verify LCD displays "SYSTEM READY"
3. Check WiFi connection (Serial Monitor)
4. Test manual controls (W, S, A, D, X)
5. Switch to auto mode (press '1')
6. Place on black line track
7. Verify line following behavior
8. Test obstacle detection (place object in path)
9. Confirm ThingSpeak data upload

---

✅ **Assembly Complete!** Your robot is ready for autonomous operation.

## 📸 Reference Images

*(For actual implementation, add photos of your assembled robot here)*

- `images/top_view.jpg` - Complete assembly
- `images/wiring_diagram.jpg` - Detailed connections
- `images/sensor_placement.jpg` - Sensor positioning
- `images/power_setup.jpg` - Power distribution

## 🔗 Additional Resources

- [ESP32 Pinout Reference](https://randomnerdtutorials.com/esp32-pinout-reference-gpios/)
- [HC-SR04 Datasheet](https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf)
- [L298N Motor Driver Guide](https://www.instructables.com/L298N-Motor-Driver-Tutorial/)
