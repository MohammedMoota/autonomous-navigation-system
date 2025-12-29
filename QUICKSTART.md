# Quick Start Guide

Get your Autonomous Navigation System running in under 10 minutes!

## 🚀 Fast Track Setup

### For Wokwi Simulation (Fastest - No Hardware Required)

1. **Visit Wokwi**
   - Go to [wokwi.com](https://wokwi.com)
   - Sign in (free account)

2. **Create Project**
   - Click "New Project" → "ESP32"
   - Replace `sketch.ino` with project code
   - Upload `diagram.json` (via diagram editor)
   - Add to `libraries.txt`:

     ```
     LiquidCrystal I2C
     ESP32Servo
     ThingSpeak
     ```

3. **Configure ThingSpeak**
   - Create account at [thingspeak.com](https://thingspeak.com)
   - Create new channel with 2 fields:
     - Field 1: Distance (cm)
     - Field 2: Obstacle Status
   - Copy Channel ID and Write API Key
   - Update lines 36-37 in sketch.ino

4. **Run Simulation**
   - Click green "Start Simulation" button
   - Open Serial Monitor
   - Use keyboard controls: W=Forward, S=Back, A=Left, D=Right
   - Press '1' to toggle Auto/Manual mode

**Total Time**: ⏱️ ~5 minutes

---

### For Physical Hardware

1. **Install Arduino IDE**

   ```
   Download from: https://www.arduino.cc/en/software
   ```

2. **Add ESP32 Support**
   - File → Preferences → Additional Board Manager URLs:

     ```
     https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
     ```

   - Tools → Board Manager → Search "ESP32" → Install

3. **Install Libraries**
   - Tools → Manage Libraries
   - Search and install:
     - LiquidCrystal I2C
     - ESP32Servo
     - ThingSpeak

4. **Configure Code**
   - Open `sketch.ino`
   - Update WiFi credentials (lines 31-32)
   - Add ThingSpeak credentials (lines 36-37)

5. **Upload**
   - Connect ESP32 via USB
   - Tools → Board → "ESP32 Dev Module"
   - Tools → Port → Select your COM port
   - Click Upload ⬆️

6. **Test**
   - Open Serial Monitor (115200 baud)
   - Wait for "SYSTEM READY"
   - Send commands: W, S, A, D, X, 1

**Total Time**: ⏱️ ~15 minutes (first time)

---

## 📱 Control Cheat Sheet

| Key | Action |
|-----|--------|
| `W` or `F` | ⬆️ Forward |
| `S` or `B` | ⬇️ Backward |
| `A` or `L` | ⬅️ Turn Left |
| `D` or `R` | ➡️ Turn Right |
| `X` | 🛑 Stop |
| `1` | 🔄 Switch Mode |

## 🎯 Testing Checklist

- [ ] LCD displays "SYSTEM READY"
- [ ] WiFi connects successfully
- [ ] Forward movement works (W)
- [ ] Backward movement works (S)
- [ ] Left turn works (A)
- [ ] Right turn works (D)
- [ ] Emergency stop works (X)
- [ ] Mode switch works (1)
- [ ] Auto mode follows line (if using line track)
- [ ] Obstacle detection triggers at ~20cm
- [ ] Buzzer sounds when obstacle detected
- [ ] ThingSpeak receives data (check channel)

## ⚠️ Common Issues

### "WiFi not connecting"

**Fix**: For Wokwi, use SSID: `Wokwi-GUEST`, password: (empty)

### "ThingSpeak Error 404"

**Fix**: Double-check Channel ID is correct

### "LCD shows nothing"

**Fix**: Check I2C address (try 0x27 or 0x3F)

### "Motors don't move"

**Fix**: Verify motor driver connections and power supply

## 📚 Full Documentation

For detailed information, see:

- [README.md](README.md) - Complete project documentation
- [HARDWARE_SETUP.md](HARDWARE_SETUP.md) - Wiring and assembly
- [THINGSPEAK_SETUP.md](THINGSPEAK_SETUP.md) - Cloud setup details

## 🆘 Need Help?

Open an issue on GitHub or check the troubleshooting section in README.md

---

**Ready to go!** 🎉 Start with manual mode, then switch to auto mode once comfortable!
