# Contributing to Autonomous Navigation System

First off, thank you for considering contributing to this project! 🎉

## Code of Conduct

By participating in this project, you agree to maintain a respectful and inclusive environment for everyone.

## How Can I Contribute?

### 🐛 Reporting Bugs

Before creating bug reports, please check existing issues to avoid duplicates.

**Bug Report Format:**

- **Description**: Clear description of the bug
- **Steps to Reproduce**: Detailed steps to reproduce the issue
- **Expected Behavior**: What you expected to happen
- **Actual Behavior**: What actually happened
- **Environment**:
  - ESP32 board version
  - Arduino IDE version
  - Operating system
- **Additional Context**: Screenshots, serial monitor output, etc.

### 💡 Suggesting Enhancements

Enhancement suggestions are tracked as GitHub issues.

**Enhancement Format:**

- **Feature Description**: Clear and concise feature description
- **Use Case**: Explain why this would be useful
- **Proposed Implementation**: If you have ideas on how to implement
- **Alternatives**: Any alternative solutions considered

### 🔧 Pull Requests

#### Process

1. **Fork the Repository**

   ```bash
   git clone https://github.com/yourusername/autonomous-navigation-system.git
   ```

2. **Create a Branch**

   ```bash
   git checkout -b feature/your-feature-name
   ```

   Branch naming conventions:
   - `feature/` - New features
   - `bugfix/` - Bug fixes
   - `docs/` - Documentation updates
   - `refactor/` - Code refactoring
   - `test/` - Test improvements

3. **Make Your Changes**
   - Follow the coding standards below
   - Test your changes thoroughly
   - Update documentation if needed

4. **Commit Your Changes**

   ```bash
   git commit -m "Add: Brief description of changes"
   ```

   Commit message conventions:
   - `Add:` - New features
   - `Fix:` - Bug fixes
   - `Update:` - Updates to existing features
   - `Refactor:` - Code refactoring
   - `Docs:` - Documentation changes
   - `Test:` - Test additions/updates

5. **Push to Your Fork**

   ```bash
   git push origin feature/your-feature-name
   ```

6. **Open a Pull Request**
   - Provide clear description of changes
   - Reference related issues
   - Include test results if applicable

## Coding Standards

### Arduino/C++ Style Guide

#### Naming Conventions

```cpp
// Constants: UPPER_CASE
const int BUZZER_PIN = 13;
const int MAX_DISTANCE = 400;

// Variables: camelCase
int currentDistance = 0;
bool isObstacleDetected = false;

// Functions: camelCase
void moveFwd() { }
void handleKeyboard() { }

// Classes: PascalCase
class RobotController { };
```

#### Code Formatting

```cpp
// Indentation: 2 spaces (no tabs)
void setup() {
  if (condition) {
    doSomething();
  } else {
    doSomethingElse();
  }
}

// Braces on same line for functions
void moveFwd() {
  digitalWrite(mL_fwd, HIGH);
  digitalWrite(mR_fwd, HIGH);
}

// Single line if statements - use braces
if (distance < 20) {
  stopBot();
}

// NOT: if (distance < 20) stopBot();
```

#### Comments

```cpp
// Use single-line comments for brief explanations
int distance = getDistance(); // Distance in centimeters

/* Use multi-line comments for longer explanations
   or to temporarily disable code blocks during debugging */

// Function documentation
/**
 * Moves robot forward by activating both motors
 * Sets forward pins HIGH and backward pins LOW
 */
void moveFwd() {
  digitalWrite(mL_fwd, HIGH);
  digitalWrite(mR_fwd, HIGH);
  digitalWrite(mL_back, LOW);
  digitalWrite(mR_back, LOW);
}
```

#### Best Practices

1. **Keep Functions Small**: Each function should do one thing well
2. **Avoid Magic Numbers**: Use named constants

   ```cpp
   // Good
   const int OBSTACLE_THRESHOLD = 20;
   if (distance < OBSTACLE_THRESHOLD) { }
   
   // Bad
   if (distance < 20) { }
   ```

3. **Use Descriptive Names**: Variables should explain their purpose

   ```cpp
   // Good
   int obstacleDistance = 0;
   bool isLineDetected = false;
   
   // Bad
   int d = 0;
   bool flag = false;
   ```

4. **Error Handling**: Check return values and handle errors

   ```cpp
   int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
   if (x == 200) {
     Serial.println("Success");
   } else {
     Serial.println("Error: " + String(x));
   }
   ```

5. **Memory Management**: Be mindful of RAM usage on ESP32
   - Use `F()` macro for string constants: `Serial.print(F("Text"));`
   - Avoid unnecessary String objects
   - Prefer char arrays for fixed strings

## Testing Guidelines

### Before Submitting PR

- [ ] Code compiles without errors
- [ ] Code compiles without warnings
- [ ] Tested on ESP32 hardware (or Wokwi simulator)
- [ ] All existing features still work
- [ ] New features work as expected
- [ ] Serial Monitor output is clean and informative
- [ ] No memory leaks or crashes
- [ ] Documentation updated if needed

### Testing Checklist

**Manual Mode:**

- [ ] Forward movement (W/F)
- [ ] Backward movement (S/B)
- [ ] Left turn (A/L)
- [ ] Right turn (D/R)
- [ ] Emergency stop (X)
- [ ] Mode switch (1)

**Auto Mode:**

- [ ] Line following functionality
- [ ] Obstacle detection
- [ ] Automatic avoidance maneuver
- [ ] Resume after avoidance

**IoT Features:**

- [ ] WiFi connectivity
- [ ] ThingSpeak data upload
- [ ] Data accuracy

**Display & Alerts:**

- [ ] LCD shows correct status
- [ ] Buzzer activates on obstacle
- [ ] LED indicators work properly

## Documentation Standards

### README Updates

When adding features, update:

- Feature list
- Hardware requirements (if applicable)
- Pin configuration (if changed)
- Usage instructions
- New dependencies

### Code Documentation

```cpp
/**
 * @brief Brief description of function
 * @param paramName Description of parameter
 * @return Description of return value
 */
int functionName(int paramName) {
  // Implementation
}
```

### Markdown Style

- Use headers hierarchically (H1 → H2 → H3)
- Include code blocks with language specification
- Add tables for structured data
- Use emoji sparingly for visual appeal (✅❌⚠️)

## Project Structure

```
autonomous-navigation-system/
├── sketch.ino              # Main Arduino code
├── diagram.json            # Wokwi circuit diagram
├── libraries.txt           # Required libraries
├── wokwi-project.txt       # Project metadata
├── README.md               # Main documentation
├── LICENSE                 # MIT License
├── CONTRIBUTING.md         # This file
├── HARDWARE_SETUP.md       # Assembly instructions
├── THINGSPEAK_SETUP.md     # Cloud setup guide
└── .gitignore             # Git ignore rules
```

## Questions?

Feel free to open an issue with the `question` label if you have any questions about contributing.

## Recognition

Contributors will be recognized in the project README. Thank you for making this project better! 🙌

---

**Happy Coding!** 🚀
